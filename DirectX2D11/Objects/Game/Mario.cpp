#include "Framework.h"
#include "Mario.h"

Mario::Mario()
	//: Quad(L"Textures/mario.png", Vector2(2.0f/8, 0), Vector2(3.0f/8, 1.0f/4)), //아틀라스 나누기
	:speed(2000.0f), jumpPower(-500.0f), actionType(IDLE),
	isJump(true), isAttack(false), accel(5.0f), maxSpeed(300.0f), landHeight(WIN_HEIGHT)
{
	SetAnimation();

	landLine = new LineCollider({ 0, WIN_HEIGHT }, { WIN_WIDTH, CENTER_Y });
	headLine = new LineCollider({ 0, 0 }, { 0, WIN_HEIGHT });
	headLine->SetParent(this);
}

Mario::~Mario()
{
	delete landLine;
	delete headLine;
}

void Mario::Update()
{
	Move();
	Jump();
	Attack();

	SetAction();
	
	position += velocity * DELTA;

	AnimObject::Update();

	landLine->UpdateWorld();
	headLine->UpdateWorld();

	SetLandHeight();
}

void Mario::Render()
{
	AnimObject::Render();

	landLine->Render();
	headLine->Render();
}

void Mario::Move()
{
	if (isAttack) return;

	if (KEY_PRESS('A'))
	{
		velocity.x -= speed * DELTA;

		if (velocity.x < -maxSpeed)
			velocity.x = -maxSpeed;

		scale.x = -1;
		//rotation.y = XM_PI;
	}
	if (KEY_PRESS('D'))
	{
		velocity.x += speed * DELTA;

		if (velocity.x > maxSpeed)
			velocity.x = maxSpeed;

		scale.x = 1;
		//rotation.y = 0;
	}

	if (abs(velocity.x) > 0.0f)
	{
		velocity.x = LERP(velocity.x, 0.0f, accel * DELTA);
	}
}

void Mario::Jump()
{
	if (!isJump && KEY_DOWN('W'))
	{
		velocity.y = jumpPower;
		isJump = true;
		Audio::Get()->Play("jump", 0.2f);
	}

	//if (!isJump) return;

	velocity.y += GRAVITY * DELTA;

	if (position.y > landHeight - size.y * 0.5f)
	{
		velocity.y = 0.0f;
		position.y = landHeight - size.y * 0.5f;
		isJump = false;
	}
}

void Mario::Attack()
{
	if (isAttack) return;

	if (KEY_DOWN(VK_LBUTTON))
	{
		SetClip(ATTACK);
		isAttack = true;

		if (!isJump)
		{
			velocity.x = 0.0f;
		}

		Audio::Get()->Play("attack", 0.2f);
	}
}

void Mario::SetAction()
{
	if (isAttack) return;

	if (velocity.y > 0.0f)
		SetClip(JUMP_DOWN);
	else if (velocity.y < 0.0f)
		SetClip(JUMP_UP);
	else
	{
		if (abs(velocity.x) > 5.0f)
			SetClip(RUN);
		else
			SetClip(IDLE);
	}
}

void Mario::SetAnimation()
{
	wstring file = L"Textures/mario.png";
	Texture* texture = Texture::Add(file);

	size = texture->GetSize() / Vector2(8.0f, 4.0f);

	//Idle
	vector<Frame*> frames;
	frames.push_back(new Frame(file, size.x * 0, size.y * 3, size.x, size.y));
	frames.push_back(new Frame(file, size.x * 1, size.y * 3, size.x, size.y));
	frames.push_back(new Frame(file, size.x * 2, size.y * 3, size.x, size.y));
	frames.push_back(new Frame(file, size.x * 3, size.y * 3, size.x, size.y));
	frames.push_back(new Frame(file, size.x * 4, size.y * 3, size.x, size.y));
	frames.push_back(new Frame(file, size.x * 5, size.y * 3, size.x, size.y));
	frames.push_back(new Frame(file, size.x * 6, size.y * 3, size.x, size.y));
	clips.push_back(new Clip(frames, Clip::LOOP, 0.3f));

	//Run
	frames.clear();
	frames.push_back(new Frame(file, size.x * 0, size.y * 0, size.x, size.y));
	frames.push_back(new Frame(file, size.x * 1, size.y * 0, size.x, size.y));
	clips.push_back(new Clip(frames));

	//JumpUp
	frames.clear();
	frames.push_back(new Frame(file, size.x * 2, size.y * 0, size.x, size.y));
	clips.push_back(new Clip(frames));

	//JumpDown
	frames.clear();
	frames.push_back(new Frame(file, size.x * 3, size.y * 0, size.x, size.y));
	clips.push_back(new Clip(frames));

	//Attack
	frames.clear();
	frames.push_back(new Frame(file, size.x * 0, size.y * 2, size.x, size.y));
	frames.push_back(new Frame(file, size.x * 1, size.y * 2, size.x, size.y));
	frames.push_back(new Frame(file, size.x * 2, size.y * 2, size.x, size.y));
	frames.push_back(new Frame(file, size.x * 3, size.y * 2, size.x, size.y));
	clips.push_back(new Clip(frames, Clip::END));

	clips[ATTACK]->SetEndEvent(bind(&Mario::EndAttack, this));

	curClip = clips.front();
}

void Mario::SetClip(ActionType type)
{
	if (actionType != type)
	{
		actionType = type;
		curClip = clips[type];
		curClip->Play();
	}
}

void Mario::EndAttack()
{
	SetClip(IDLE);
	isAttack = false;
}

void Mario::SetLandHeight()
{
	Vector2 point;

	if (landLine->IsCollision(headLine, point))
	{
		landHeight = point.y;
	}
}
