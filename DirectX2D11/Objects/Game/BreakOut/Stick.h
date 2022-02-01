#pragma once


class Stick : public Quad
{
private:
	float speed;

	RectCollider* collider;

public:
	Stick();
	~Stick();

	void Update();
	void Render();

	RectCollider* GetCollider() { return collider; }
};