#pragma once

class Bullet : public Quad
{
private:
	float speed;

	Collider* collider;

public:
	Bullet(wstring textureFile);
	~Bullet();

	void Update();
	void Render();

	void Fire(Vector2 pos, float angle);

	bool Collision(Collider* collider);
};