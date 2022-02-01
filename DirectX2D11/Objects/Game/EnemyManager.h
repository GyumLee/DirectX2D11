#pragma once

class EnemyManager
{
private:
	const float SPAWN_DELAY = 2.0f;

	vector<Enemy*> enemies;

	float spawnTime;

public:
	EnemyManager(wstring imageFile, UINT poolCount);
	~EnemyManager();

	void Update();
	void Render();

	void SetPlayerBullet(BulletManager* value);
	void SetTarget(Plane* transform);
	
private:
	void SpawnEnemy();
};