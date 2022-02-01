#include "Framework.h"

Knight::Knight()
	: actionType(IDLE), speed(200), hp(100), isMove(false), isAttack(false),
	target(nullptr)
{
	string path = "Textures/Knight/";

	LoadClip(path, "Knight_Idle.xml", Clip::LOOP);
	LoadClip(path, "Knight_Walk.xml", Clip::LOOP);
	LoadClip(path, "Knight_Attack.xml", Clip::END);
	LoadClip(path, "Knight_Hurt.xml", Clip::END);
	LoadClip(path, "Knight_Die.xml", Clip::END);

	clips[ATTACK]->SetEndEvent(bind(&Knight::EndAttack, this));
	clips[HURT]->SetEndEvent(bind(&Knight::EndAttack, this));
	clips[DIE]->SetEndEvent(bind(&Knight::Die, this));

	curClip = clips.front();

	bodyCollider = new RectCollider(Vector2(100, 150));
	bodyCollider->position.y = 50;
	bodyCollider->SetParent(this);

	attackCollider = new RectCollider(Vector2(120, 100));
	attackCollider->position.x = 100;
	attackCollider->position.y = 50;
	attackCollider->SetParent(this);
	attackCollider->isActive = false;

	wstring front = L"Textures/enemy_hp.png";
	wstring back = L"Textures/enemy_hp_BG.png";
	hpBar = new Bar(front, back);
	//hpBar->SetParent(this);
	//hpBar->position.y = -50;
}

Knight::~Knight()
{
	delete attackCollider;
	delete bodyCollider;
	delete hpBar;
}

void Knight::Update()
{
	if (!isActive) return;

	Vector2 offset(0, -50);
	hpBar->position = GlobalPos() + offset;

	Move();

	AnimObject::Update();

	bodyCollider->UpdateWorld();
	attackCollider->UpdateWorld();

	hpBar->Update();
}

void Knight::Render()
{
	if (!isActive) return;

	AnimObject::Render();

	bodyCollider->Render();
	attackCollider->Render();

	hpBar->Render();
}

void Knight::PostRender()
{
	Vector2 pos = CAM->WorldToScreen(position);
	pos.y -= 50;
	FONT->RenderText(name, "default", pos);
}

void Knight::Damage(float damage)
{
	isMove = false;
	hp -= damage;

	hpBar->SetValue((float)hp);

	if (hp <= 0)
		SetClip(DIE);
	else
		SetClip(HURT);

	EffectManager::Get()->Play("exp", GlobalPos());
}

void Knight::Move()
{
	if (isAttack) return;
	if (!isMove) return;

	Vector2 direction = destPos - position;
	float distance = direction.Length();

	if (distance < 1.0f)
	{
		isMove = false;
		SetClip(IDLE);
		return;
	}

	SetClip(RUN);

	velocity = direction.Normalized();

	position += velocity * speed * DELTA;

	if (velocity.x > 0)
		scale.x = 1.0f;
	else if (velocity.x < 0)
		scale.x = -1.0f;
}

void Knight::StartAttack()
{
	if (isAttack) return;

	SetClip(ATTACK);
	isAttack = true;

	attackCollider->isActive = true;
}

void Knight::EndAttack()
{
	SetClip(IDLE);
	isAttack = false;

	attackCollider->isActive = false;
}

void Knight::Die()
{
	isActive = false;
}

void Knight::SetClip(ActionType type)
{
	if (actionType != type)
	{
		actionType = type;
		curClip = clips[type];
		curClip->Play();
	}
}

void Knight::LoadClip(string path, string file, Clip::Type type, float delayTime)
{
	XmlDocument* document = new XmlDocument();
	document->LoadFile((path + file).c_str());

	XmlElement* atlas = document->FirstChildElement();
	string fileName = path + atlas->Attribute("imagePath");

	wstring imagePath;
	imagePath.assign(fileName.begin(), fileName.end());

	vector<Frame*> frames;

	XmlElement* sprite = atlas->FirstChildElement();

	while (sprite != nullptr)
	{
		float x, y, w, h;
		x = sprite->FloatAttribute("x");
		y = sprite->FloatAttribute("y");
		w = sprite->FloatAttribute("w");
		h = sprite->FloatAttribute("h");

		frames.push_back(new Frame(imagePath, x, y, w, h));

		sprite = sprite->NextSiblingElement();
	}

	clips.push_back(new Clip(frames, type, delayTime));

	delete document;
}
