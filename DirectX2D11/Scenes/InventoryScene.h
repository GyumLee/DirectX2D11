#pragma once

class InventoryScene : public Scene
{
private:
	Store* store;
	Inventory* inventory;

public:
	InventoryScene();
	~InventoryScene();

	virtual void Update() override;
	virtual void Render() override;
};