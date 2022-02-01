#pragma once

class Inventory : public UIPanel
{
private:
	UINT gold;
	vector<Item*> items;

	Item* selectItem;

public:
	Inventory();
	~Inventory();

	void Update();
	void Render();

	void BuyItem(ItemData itemData);
	void SellItem();

	Item* GetItem(UINT key);

	Item* GetSelectItem() { return selectItem; }

private:
	void SelectItem(void* item);
	void SetItemPos();
	void Sort();

	static int CompareItem(Item* item1, Item* item2);
};