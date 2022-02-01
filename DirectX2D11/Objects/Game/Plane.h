#pragma once

class Plane : public Quad
{
private:
	float speed;

	Collider* collider;

	Quad* weapon;

	BulletManager* bulletManager;

public:
	Plane();
	~Plane();

	void Update();
	void Render();

	BulletManager* GetBullet() { return bulletManager; }
	Collider* GetCollider() { return collider; }

private:
	void KeyboardMove();
	void MouseMove();
};