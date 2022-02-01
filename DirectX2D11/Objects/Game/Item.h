#pragma once

class Item : public Transform
{
public:
	enum State
	{
		STORE, INVENTORY, EQUIP
	};

private:
	State state;

	ItemData data;

	Button* button;
	Quad* selected;

	bool isSelected;

	UINT count;

public:
	Item(ItemData data);
	~Item();

	void Update();
	void Render();

	void SetSelected(bool value) { isSelected = value; }
	void SetState(State state) { this->state = state; }
	void IncreaseCount() { count++; }
	void DecreaseCount() { count--; }

	Button* GetButton() { return button; }
	ItemData GetData() { return data; }

	UINT GetCount() { return count; }
};