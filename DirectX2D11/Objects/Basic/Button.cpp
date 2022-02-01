#include "Framework.h"

Button::Button(wstring textureFile)
	: Quad(textureFile), state(NONE), Event(nullptr), VoidEvent(nullptr)
{
	collider = new RectCollider(size);
	collider->SetParent(this);

	noneColor = Float4(1, 1, 1, 1);
	downColor = Float4(0.5f, 0.5f, 0.5f, 1);
	overColor = Float4(0.9f, 0.9f, 0.9f, 1);
}

Button::~Button()
{
	delete collider;
}

void Button::Update()
{
	if (collider->IsPointCollision(CAM->ScreenToWorld(mousePos)))
	{
		if (KEY_DOWN(VK_LBUTTON))
			isDownCheck = true;

		if (KEY_PRESS(VK_LBUTTON))
			state = DOWN;
		else
			state = OVER;

		if (isDownCheck && KEY_UP(VK_LBUTTON))
		{
			if (Event != nullptr)
				Event();

			if (VoidEvent != nullptr)
				VoidEvent(voidParam);

			isDownCheck = false;
		}
	}
	else
	{
		state = NONE;

		if (KEY_UP(VK_LBUTTON))
			isDownCheck = false;
	}

	switch (state)
	{
	case Button::NONE:
		colorBuffer->Set(noneColor);
		break;
	case Button::DOWN:
		colorBuffer->Set(downColor);
		break;
	case Button::OVER:
		colorBuffer->Set(overColor);
		break;
	default:
		break;
	}

	collider->UpdateWorld();
	UpdateWorld();
}

void Button::Render()
{
	Quad::Render();
	collider->Render();
	FONT->RenderText(text, "default", GlobalPos(), Size());
}
