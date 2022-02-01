#include "Framework.h"

UIPanel::UIPanel(wstring textureFile)
	: isDrag(false)
{
	panel = new Quad(textureFile);
	panel->SetParent(this);

	collider = new RectCollider(panel->Size());
	collider->SetParent(this);
}

UIPanel::~UIPanel()
{
	delete panel;
	delete collider;
}

void UIPanel::Update()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		if (collider->IsPointCollision(mousePos))
		{
			offset = mousePos - position;
			isDrag = true;
		}
		else
		{
			isDrag = false;
		}
	}

	if (isDrag && KEY_PRESS(VK_LBUTTON))
	{
		position = mousePos - offset;
	}

	panel->UpdateWorld();
	collider->UpdateWorld();

	UpdateWorld();
}

void UIPanel::Render()
{
	panel->Render();
	collider->Render();
}
