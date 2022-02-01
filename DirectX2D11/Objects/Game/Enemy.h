#pragma once

class Enemy : public Quad
{
private:
	float speed;

	Collider* collider;

	BulletManager* playerbullet;
	Plane* target;

public:
	Enemy(wstring imageFile);
	~Enemy();

	void Update();
	void Render();

	Collider* GetCollider() { return collider; }

	void SetPlayerBullet(BulletManager* value) { playerbullet = value; }
	void SetTarget(Plane* transform) { target = transform; }
};