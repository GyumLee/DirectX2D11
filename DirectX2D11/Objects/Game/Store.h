#pragma once

class Store : public UIPanel
{
private:
	vector<Item*> items;

	Item* selectItem;

	string itemInfoText;

	Button* buyButton;
	Button* sellButton;

	Inventory* inventory;

public:
	Store();
	~Store();

	void Update();
	void Render();

	void SetInventory(Inventory* inventory) { this->inventory = inventory; }

private:
	void LoadItems();

	void SelectItem(void* item);

	void BuyItem();
	void SellItem();
};