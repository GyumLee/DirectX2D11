#pragma once

class BulletManager
{
private:
	vector<Bullet*> bullets;

public:
	BulletManager(wstring imageFile, UINT poolCount = 30);
	~BulletManager();

	void Update();
	void Render();

	void Fire(Vector2 pos, float angle);

	bool Collision(Collider* collider);
};