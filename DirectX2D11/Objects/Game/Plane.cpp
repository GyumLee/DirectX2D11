#include "Framework.h"

Plane::Plane() : Quad(L"Textures/player.png"), speed(100)
{
	bulletManager = new BulletManager(L"Textures/playerBullet.png");

	collider = new RectCollider(Size());
	collider->SetParent(&world);

	weapon = new Quad(L"Textures/location.png");
	weapon->SetParent(&world);
	weapon->position.y = -70;
}

Plane::~Plane()
{
	delete bulletManager;
	delete collider;
	delete weapon;
}

void Plane::Update()
{
	KeyboardMove();
	//MouseMove();

	if (KEY_DOWN(VK_LBUTTON))
	{
		bulletManager->Fire(weapon->GlobalPos(), weapon->Up().Angle());
	}

	UpdateWorld();

	bulletManager->Update();

	collider->UpdateWorld();

	Vector2 temp = mousePos - weapon->GlobalPos();
	weapon->rotation.z = temp.Angle() - rotation.z;

	weapon->UpdateWorld();
}

void Plane::Render()
{
	bulletManager->Render();

	Quad::Render();
	collider->Render();
	weapon->Render();
}

void Plane::KeyboardMove()
{
	if (KEY_PRESS('W'))
	{
		//position.x += cos(rotation.z - XM_PI * 0.5f) * speed * DELTA;
		//position.y += sin(rotation.z - XM_PI * 0.5f) * speed * DELTA;
		position -= Up() * speed * DELTA;
	}
	if (KEY_PRESS('S'))
	{
		//position.x -= cos(rotation.z - XM_PI * 0.5f) * speed * DELTA;
		//position.y -= sin(rotation.z - XM_PI * 0.5f) * speed * DELTA;
		position += Up() * speed * DELTA;
	}
	if (KEY_PRESS('A'))
		rotation.z -= DELTA;
	if (KEY_PRESS('D'))
		rotation.z += DELTA;
}

void Plane::MouseMove()
{
	if (KEY_PRESS('W'))
		position.y -= speed * DELTA;
	if (KEY_PRESS('S'))
		position.y += speed * DELTA;
	if (KEY_PRESS('A'))
		position.x -= speed * DELTA;
	if (KEY_PRESS('D'))
		position.x += speed * DELTA;

	Vector2 temp = mousePos - position;

	float angle = atan2(temp.y, temp.x) + XM_PI * 0.5f;

	rotation.z = angle;
}
