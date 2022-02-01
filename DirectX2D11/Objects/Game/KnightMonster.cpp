#include "Framework.h"

knightMonster::knightMonster()
	: state(State::IDLE), traceRange(300.0f), attackRange(150.0f)
{
	colorBuffer->Set(1, 1, 0);
	name = L"Monster";
}

knightMonster::~knightMonster()
{
}

void knightMonster::Update()
{
	SetState();

	switch (state)
	{
	case knightMonster::State::IDLE:
		Idle();
		break;
	case knightMonster::State::TRACE:
		Trace();
		break;
	case knightMonster::State::ATTACK:
		Attack();
		break;
	default:
		break;
	}

	Knight::Update();
}

void knightMonster::SetState()
{
	if (target->isActive == false)
	{
		state = State::IDLE;
		return;
	}

	float distance = (position - target->position).Length();

	if (distance < attackRange)
		state = State::ATTACK;
	else if (distance < traceRange)
		state = State::TRACE;
	else
		state = State::IDLE;
}

void knightMonster::Idle()
{
	SetClip(IDLE);
	isMove = false;
}

void knightMonster::Trace()
{
	if (isAttack) return;

	isMove = true;
	destPos = target->position;
}

void knightMonster::Attack()
{
	isMove = false;

	StartAttack();

	if (attackCollider->IsCollision(target->GetBodyCollider()))
	{
		target->Damage(10.0f);
		attackCollider->isActive = false;
	}
}
