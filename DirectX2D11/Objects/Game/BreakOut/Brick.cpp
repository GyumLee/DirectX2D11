#include "Framework.h"

Brick::Brick(UINT hp)
	: Quad(L"Textures/BreakOut/Brick.png"), hp(hp)
{
	collider = new RectCollider(Size());
	collider->SetParent(&world);
}

Brick::~Brick()
{
	delete collider;
}

void Brick::Update()
{
	if (hp <= 0) return;

	switch (hp)
	{
	case 1:
		colorBuffer->Set(1, 1, 1);
		break;
	case 2:
		colorBuffer->Set(1, 1, 0);
		break;
	case 3:
		colorBuffer->Set(1, 0, 0);
		break;
	}

	UpdateWorld();
	collider->UpdateWorld();
}

void Brick::Render()
{
	if (hp <= 0) return;

	Quad::Render();
	collider->Render();
}

Direction Brick::Collision(Ball* ball)
{
	if (hp <= 0) return Direction::NONE;

	ball->GetCollider()->UpdateWorld();
	if (!collider->IsCollision(ball->GetCollider())) return Direction::NONE;

	hp--;

	Vector2 C = ball->position - position;

	Vector2 rightTop(collider->R(), collider->T());
	Vector2 rightBottom(collider->R(), collider->B());

	Vector2 A = rightTop - position;
	Vector2 B = rightBottom - position;

	if (Vector2::Cross(A, C) * Vector2::Cross(B, C) < 0) // 좌우충돌
	{
		if (ball->position.x > position.x)
		{
			ball->position.x = collider->R() + ball->Radius() + 1;
			return Direction::RIGHT;
		}
		else
		{
			ball->position.x = collider->L() - ball->Radius() - 1;
			return Direction::LEFT;
		}
	}
	else // 상하
	{
		if (ball->position.y > position.y)
		{
			ball->position.y = collider->B() + ball->Radius() + 1;
			return Direction::DOWN;
		}
		else
		{
			ball->position.y = collider->T() - ball->Radius() - 1;
			return Direction::UP;
		}
	}
}
