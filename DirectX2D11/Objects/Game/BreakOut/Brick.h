#pragma once

class Brick : public Quad
{
private:
	UINT hp;

	RectCollider* collider;

public:
	Brick(UINT hp = 1);
	~Brick();

	void Update();
	void Render();

	UINT GetHp() { return hp; }
	RectCollider* GetCollider() { return collider; }

	Direction Collision(class Ball* ball);
};