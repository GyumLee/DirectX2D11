#include "Framework.h"

KnightPlayer::KnightPlayer()
{
	speed = 400.0f;
	name = L"Player";
}

KnightPlayer::~KnightPlayer()
{
}

void KnightPlayer::Update()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		destPos = CAM->ScreenToWorld(mousePos);
		isMove = true;
	}

	if (KEY_DOWN(VK_RBUTTON))
	{
		StartAttack();
	}

	if (target != nullptr && attackCollider->IsCollision(target->GetBodyCollider()))
	{
		target->Damage(30.0f);
		attackCollider->isActive = false;
	}

	Knight::Update();
}
