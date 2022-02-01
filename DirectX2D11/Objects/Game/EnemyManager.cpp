#include "Framework.h"

EnemyManager::EnemyManager(wstring imageFile, UINT poolCount)
	: spawnTime(0.0f)
{
	for (UINT i = 0; i < poolCount; i++)
	{
		Enemy* enemy = new Enemy(imageFile);
		enemy->isActive = false;

		enemies.push_back(enemy);
	}
}

EnemyManager::~EnemyManager()
{
	for (Enemy* enemy : enemies)
		delete enemy;
}

void EnemyManager::Update()
{
	spawnTime += DELTA;

	if (spawnTime > SPAWN_DELAY)
	{
		SpawnEnemy();
		spawnTime = 0;
	}

	for (Enemy* enemy : enemies)
		enemy->Update();
}

void EnemyManager::Render()
{
	for (Enemy* enemy : enemies)
		enemy->Render();
}

void EnemyManager::SetPlayerBullet(BulletManager* value)
{
	for (Enemy* enemy : enemies)
	{
		enemy->SetPlayerBullet(value);
	}
}

void EnemyManager::SetTarget(Plane* transform)
{
	for (Enemy* enemy : enemies)
	{
		enemy->SetTarget(transform);
	}
}

void EnemyManager::SpawnEnemy()
{
	for (Enemy* enemy : enemies)
	{
		if (!enemy->isActive)
		{
			enemy->isActive = true;

			enemy->position.x = Random(0.0f, (float)WIN_WIDTH);
			enemy->position.y = Random(0.0f, (float)WIN_HEIGHT);
			return;
		}
	}
}
