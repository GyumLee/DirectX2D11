#pragma once

class Ball : public Quad
{
private:
	float speed;
	Vector2 dir;

	bool isPlay;

	CircleCollider* collider;

	Stick* stick;
	BrickManager* brickManager;

public:
	Ball();
	~Ball();

	void Update();
	void Render();

	void SetStick(Stick* stick) { this->stick = stick; }
	void SetBrick(BrickManager* brick) { brickManager = brick; }

	float Radius() { return collider->Radius(); }
	CircleCollider* GetCollider() { return collider; }

private:
	void CollisionBorder();
	void CollisionStick();
	void CollisionBrick();
};