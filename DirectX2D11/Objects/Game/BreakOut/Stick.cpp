#include "Framework.h"

Stick::Stick() : Quad(L"Textures/BreakOut/Stick.png"), speed(400)
{
	collider = new RectCollider(Size());
	collider->SetParent(&world);
	collider->scale *= 0.85f;
	collider->position.x -= 8;
	collider->position.y -= 10;
}

Stick::~Stick()
{
	delete collider;
}

void Stick::Update()
{
	if (KEY_PRESS('D'))
	{
		if (collider->R() < WIN_WIDTH)
		{
			position.x += speed * DELTA;
		}
	}

	if (KEY_PRESS('A'))
	{
		if (collider->L() > 0)
		{
			position.x -= speed * DELTA;
		}
	}

	UpdateWorld();
	collider->UpdateWorld();
}

void Stick::Render()
{
	Quad::Render();

	collider->Render();
}
