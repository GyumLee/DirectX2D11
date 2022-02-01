#include "Framework.h"

Store::Store() : UIPanel(L"Textures/Item/panel.png")
{
	LoadItems();

	buyButton = new Button(L"Textures/Item/btn.png");
	buyButton->SetText(L"Buy");
	buyButton->SetParent(this);
	buyButton->position = { -150, 300 };
	buyButton->SetEvent(bind(&Store::BuyItem, this));

	sellButton = new Button(L"Textures/Item/btn.png");
	sellButton->SetText(L"Sell");
	sellButton->SetParent(this);
	sellButton->position = { 150, 300 };
	sellButton->SetEvent(bind(&Store::SellItem, this));
}

Store::~Store()
{
	for (Item* item : items)
		delete item;

	delete buyButton;
	delete sellButton;
}

void Store::Update()
{
	UIPanel::Update();

	for (Item* item : items)
		item->Update();

	buyButton->Update();
	sellButton->Update();
}

void Store::Render()
{
	UIPanel::Render();

	for (Item* item : items)
		item->Render();

	Vector2 infoPos = GlobalPos();
	infoPos.y += 200;

	//wstring str;
	//str.assign(itemInfoText.begin(), itemInfoText.end());
	wstring str = FONT->ToWString(itemInfoText);
	FONT->RenderText(str, "default", infoPos);

	buyButton->Render();
	sellButton->Render();
}

void Store::LoadItems()
{
	Vector2 startOffset(-150, -120);

	UINT colCount = 3;

	for (pair<UINT, ItemData> data: DataManager::Get()->GetItemData())
	{
		Item* item = new Item(data.second);
		item->scale *= 2.0f;
		item->SetParent(this);

		Vector2 size(100, 100);

		item->position.x = startOffset.x + size.x * (items.size() % colCount);
		item->position.y = startOffset.y + size.y * (items.size() / colCount);

		item->GetButton()->SetVoidEvent(bind(&Store::SelectItem, this, placeholders::_1));
		item->GetButton()->SetVoidParam(item);

		items.push_back(item);
	}
}

void Store::SelectItem(void* item)
{
	selectItem = (Item*)item;

	for (Item* item : items)
	{
		if (selectItem == item)
			item->SetSelected(true);
		else
			item->SetSelected(false);
	}

	ItemData data = selectItem->GetData();
	itemInfoText = "";
	itemInfoText += data.name + " : " + "ATK->" +
		to_string(data.attack) + "\n";
	itemInfoText += "Price->" + to_string(data.price);
}

void Store::BuyItem()
{
	if (selectItem == nullptr) return;

	inventory->BuyItem(selectItem->GetData());
}

void Store::SellItem()
{
	Item* sellItem = inventory->GetSelectItem();

	if (sellItem == nullptr) return;

	inventory->SellItem();
}
