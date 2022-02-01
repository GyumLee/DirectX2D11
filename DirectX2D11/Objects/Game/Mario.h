#pragma once

class Mario : public AnimObject
{
private:
	enum ActionType
	{
		IDLE, RUN, JUMP_UP, JUMP_DOWN, ATTACK
	}actionType;

	float speed;
	float maxSpeed;
	float accel;

	Vector2 velocity;
	float jumpPower;

	bool isJump;
	bool isAttack;

	Vector2 size;

	LineCollider* landLine;
	LineCollider* headLine;

	float landHeight;

public:
	Mario();
	~Mario();

	void Update();
	void Render();

private:
	void Move();
	void Jump();
	void Attack();

	void SetAction();

	void SetAnimation();
	void SetClip(ActionType type);

	void EndAttack();

	void SetLandHeight();
};