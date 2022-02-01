#include "Framework.h"

Item::Item(ItemData data)
	: data(data), isSelected(false), count(0), state(STORE)
{
	wstring file;
	file.assign(data.imageFile.begin(), data.imageFile.end());
	button = new Button(file);
	button->SetParent(this);

	selected = new Quad(L"Textures/Item/selected.png");
	selected->scale *= 0.5f;
	selected->SetParent(this);
}

Item::~Item()
{
	delete button;
	delete selected;
}

void Item::Update()
{
	button->Update();
	selected->UpdateWorld();

	UpdateWorld();
}

void Item::Render()
{
	button->Render();

	if (isSelected)
		selected->Render();

	if (data.type == 1 && state == INVENTORY)
	{
		Vector2 pos = GlobalPos();
		pos += 20.0f;
		FONT->RenderText(to_wstring(count), "default", pos);
	}
}
