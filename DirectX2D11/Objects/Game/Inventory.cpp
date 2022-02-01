#include "Framework.h"

Inventory::Inventory()
	: UIPanel(L"Textures/Item/panel.png"), gold(10000),
	selectItem(nullptr)
{
}

Inventory::~Inventory()
{
	for (Item* item : items)
		delete item;
}

void Inventory::Update()
{
	UIPanel::Update();

	for (Item* item : items)
		item->Update();
}

void Inventory::Render()
{
	UIPanel::Render();

	for (Item* item : items)
		item->Render();

	wstring str = L"GOLD : " + to_wstring(gold);
	Vector2 pos = GlobalPos();
	pos.y += 200;
	FONT->RenderText(str, "default", pos);
}

void Inventory::BuyItem(ItemData itemData)
{
	if (gold < itemData.price)
		return;

	gold -= itemData.price;

	if (itemData.type == 1)
	{
		Item* item = GetItem(itemData.key);
		if (item != nullptr)
		{
			item->IncreaseCount();
			return;
		}
	}

	Item* item = new Item(itemData);
	item->SetState(Item::INVENTORY);
	item->IncreaseCount();

	item->GetButton()->SetVoidEvent(
		bind(&Inventory::SelectItem, this, placeholders::_1));
	item->GetButton()->SetVoidParam(item);

	item->scale *= 2.0f;
	item->SetParent(this);

	items.push_back(item);

	Sort();
	SetItemPos();
}

void Inventory::SellItem()
{
	/*for (UINT i = 0; i < items.size(); i++)
	{
		if (items[i] == selectItem)
		{
			if (selectItem->GetCount() > 1)
			{
				selectItem->DecreaseCount();
			}
			else
			{
				items.erase(items.begin() + i);
			}
			gold += selectItem->GetData().price;
			return;
		}
	}*/

	vector<Item*>::iterator iter = items.begin();

	for (; iter < items.end(); iter++)
	{
		if ((*iter) == selectItem)
		{
			if (selectItem->GetCount() > 1)
			{
				selectItem->DecreaseCount();
			}
			else
			{
				items.erase(iter);
			}
			gold += selectItem->GetData().price;
			break;
		}
	}

	Sort();
	SetItemPos();
}

Item* Inventory::GetItem(UINT key)
{
	for (Item* item : items)
	{
		if (item->GetData().key == key)
		{
			return item;
		}
	}

	return nullptr;
}

void Inventory::SelectItem(void* item)
{
	selectItem = (Item*)item;

	for (Item* i : items)
	{
		if (selectItem == i)
			i->SetSelected(true);
		else
			i->SetSelected(false);
	}
}

void Inventory::SetItemPos()
{
	Vector2 startOffset(-150, -120);
	UINT colCount = 3;

	Vector2 size(100, 100);

	for (UINT i = 0; i < items.size(); i++)
	{
		items[i]->position.x = startOffset.x + size.x * (i % colCount);
		items[i]->position.y = startOffset.y + size.y * (i / colCount);
	}
}

void Inventory::Sort()
{
	sort(items.begin(), items.end(), Inventory::CompareItem);
}

int Inventory::CompareItem(Item* item1, Item* item2)
{
	return item1->GetData().key < item2->GetData().key;
}
