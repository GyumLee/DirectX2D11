#include "Framework.h"

BulletManager::BulletManager(wstring imageFile, UINT poolCount)
{
	bullets.resize(poolCount);

	for (Bullet*& bullet : bullets)
	{
		bullet = new Bullet(imageFile);
		bullet->isActive = false;
	}
}

BulletManager::~BulletManager()
{
	for (Bullet* bullet : bullets)
	{
		delete bullet;
	}
}

void BulletManager::Update()
{
	for (Bullet* bullet : bullets)
	{
		bullet->Update();
	}
}

void BulletManager::Render()
{
	for (Bullet* bullet : bullets)
	{
		bullet->Render();
	}
}

void BulletManager::Fire(Vector2 pos, float angle)
{
	for (Bullet* bullet : bullets)
	{
		if (!bullet->isActive)
		{
			bullet->Fire(pos, angle);
			break;
		}
	}
}

bool BulletManager::Collision(Collider* collider)
{
	for (Bullet* bullet : bullets)
	{
		if (bullet->Collision(collider))
			return true;
	}

	return false;
}
