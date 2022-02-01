#pragma once

class Knight : public AnimObject
{
protected:
	wstring name;

	enum ActionType
	{
		IDLE, RUN, ATTACK, HURT, DIE
	}actionType;

	float speed;
	float hp;

	Vector2 velocity;
	Vector2 destPos;

	bool isMove;
	bool isAttack;

	Collider* bodyCollider;
	Collider* attackCollider;

	Knight* target;

	Bar* hpBar;

public:
	Knight();
	~Knight();

	void Update();
	void Render();
	void PostRender();

	void Damage(float damage);

	Collider* GetBodyCollider() { return bodyCollider; }
	void SetTarget(Knight* target) { this->target = target; }

protected:
	void Move();
	void StartAttack();
	void EndAttack();
	void Die();

	void SetClip(ActionType type);

	void LoadClip(string path, string file, Clip::Type type, float delayTime = 0.1f);
};