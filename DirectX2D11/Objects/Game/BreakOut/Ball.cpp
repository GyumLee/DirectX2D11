#include "Framework.h"

Ball::Ball()
	: Quad(L"Textures/BreakOut/Ball.png"), speed(400), stick(nullptr),
	isPlay(false), dir(1, -1)
{
	dir.Normalize();

	collider = new CircleCollider(Size().x * 0.5f);
	collider->SetParent(&world);
	collider->scale *= 0.5f;
}

Ball::~Ball()
{
	delete collider;
}

void Ball::Update()
{
	if (KEY_DOWN(VK_SPACE))
		isPlay = true;

	if (!isPlay)
	{
		position.x = (stick->GetCollider()->L() + stick->GetCollider()->R()) / 2;
		position.y = stick->GetCollider()->T() - collider->Radius() - 1;
	}
	else
	{
		position += dir * speed * DELTA;

		CollisionBorder();
		CollisionStick();
		CollisionBrick();
	}

	UpdateWorld();
	collider->UpdateWorld();
}

void Ball::Render()
{
	Quad::Render();
	collider->Render();
}

void Ball::CollisionBorder()
{
	if (position.x + collider->Radius() > WIN_WIDTH)
	{
		dir.x *= -1;
		position.x = WIN_WIDTH - collider->Radius();
	}
	if (position.x - collider->Radius() < 0)
	{
		dir.x *= -1;
		position.x = collider->Radius();
	}
	if (position.y - collider->Radius() < 0)
	{
		dir.y *= -1;
		position.y = collider->Radius();
	}
	if (position.y > WIN_HEIGHT)
	{
		isPlay = false;

		MessageBox(hWnd, L"GameOver!", L"GG", MB_OK);

		dir = { 1, -1 };
		dir.Normalize();
	}
}

void Ball::CollisionStick()
{
	if (!isPlay) return;

	if (collider->IsCollision(stick->GetCollider()))
	{
		Vector2 bottomCenter;
		bottomCenter.x = (stick->GetCollider()->L() + stick->GetCollider()->R()) / 2;
		bottomCenter.y = stick->GetCollider()->B();

		dir = (position - bottomCenter).Normalized();
	}
}

void Ball::CollisionBrick()
{
	Direction direction = brickManager->Collision(this);

	switch (direction)
	{
	case GameMath::Direction::UP:
	case GameMath::Direction::DOWN:
		dir.y *= -1.0f;
		break;
	case GameMath::Direction::RIGHT:
	case GameMath::Direction::LEFT:
		dir.x *= -1.0f;
		break;
	}
}
