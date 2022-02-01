#pragma once

class knightMonster : public Knight
{
private:
	enum class State
	{
		IDLE, TRACE, ATTACK
	}state;

	float traceRange;
	float attackRange;

public:
	knightMonster();
	~knightMonster();

	void Update();
	
private:
	void SetState();

	void Idle();
	void Trace();
	void Attack();
};