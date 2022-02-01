#include "Framework.h"

Tank::Tank() : speed(200)
{
	wstring file = L"Textures/tank.png";
	Texture* texture = Texture::Add(file);

	Vector2 cutSize = texture->GetSize() / Vector2(8, 4);

	vector<Frame*> frames;
	for (UINT i = 0; i < 8; i++)
		frames.push_back(new Frame(file, cutSize.x * i, cutSize.y * 2, cutSize.x, cutSize.y));
	clips.push_back(new Clip(frames));

	curClip = clips.front();
	curClip->Stop();

	collider = new RectCollider(cutSize);
	collider->SetParent(this);

	LoadPos();
}

Tank::~Tank()
{
	delete collider;

	SavePos();
}

void Tank::Update()
{
	//KeyboardMove();
	/*if (KEY_DOWN(VK_LBUTTON))
	{
		curClip->Play();
		path.insert(path.begin(), mousePos);
	}*/

	AutoMove();

	AnimObject::Update();
	collider->UpdateWorld();
}

void Tank::Render()
{
	AnimObject::Render();
	collider->Render();
}

void Tank::SetPath(vector<Vector2> path)
{
	curClip->Play();
	this->path = path;
}

void Tank::KeyboardMove()
{
	if (KEY_DOWN(VK_UP) || KEY_DOWN(VK_DOWN) || KEY_DOWN(VK_LEFT) || KEY_DOWN(VK_RIGHT))
		curClip->Play();


	if (KEY_PRESS(VK_UP))
	{
		position.y -= speed * DELTA;
		rotation.z = -XM_PIDIV2;
	}
	else if (KEY_PRESS(VK_DOWN))
	{
		position.y += speed * DELTA;
		rotation.z = +XM_PIDIV2;
	}
	else if (KEY_PRESS(VK_LEFT))
	{
		position.x -= speed * DELTA;
		rotation.z = XM_PI;
	}
	else if (KEY_PRESS(VK_RIGHT))
	{
		position.x += speed * DELTA;
		rotation.z = 0;
	}

	if (KEY_UP(VK_UP) || KEY_UP(VK_DOWN) || KEY_UP(VK_LEFT) || KEY_UP(VK_RIGHT))
		curClip->Stop();
}

void Tank::AutoMove()
{
	if (path.size() == 0)
	{
		curClip->Stop();
		return;
	}

	Vector2 direction = path.back() - position;
	rotation.z = direction.Angle();

	position += Right() * speed * DELTA;

	float distance = direction.Length();

	if (distance < 5.0f)
		path.pop_back();
}

void Tank::SavePos()
{
	BinaryWriter writer("TextData/Tank.info");
	writer.Float(position.x);
	writer.Float(position.y);
	writer.Float(rotation.z);
}

void Tank::LoadPos()
{
	BinaryReader reader("TextData/Tank.info");

	if (!reader.IsSuccess()) return;

	position.x = reader.Float();
	position.y = reader.Float();
	rotation.z = reader.Float();
}
