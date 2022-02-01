#include "Framework.h"

Enemy::Enemy(wstring imageFile)
	: Quad(imageFile), speed(100), target(nullptr)
{
	collider = new CircleCollider(Size().x * 0.5f);
	collider->SetParent(&world);
}

Enemy::~Enemy()
{
	delete collider;
}

void Enemy::Update()
{
	if (!isActive) return;

	if (playerbullet->Collision(collider))
		isActive = false;

	if (target != nullptr)
	{
		Vector2 dir = target->position - position;

		position += dir.Normalized() * speed * DELTA;

		if (collider->IsCollision(target->GetCollider()))
		{
			if (MessageBox(hWnd, L"GameOver", L"GG", MB_OK))
				DestroyWindow(hWnd);
		}
	}

	UpdateWorld();
	collider->UpdateWorld();
}

void Enemy::Render()
{
	if (!isActive) return;

	Quad::Render();
	collider->Render();
}
