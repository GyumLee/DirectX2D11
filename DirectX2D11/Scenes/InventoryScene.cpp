#include "Framework.h"
#include "InventoryScene.h"

InventoryScene::InventoryScene()
{
	DataManager::Get();

	store = new Store();
	store->position = { 300, CENTER_Y };

	inventory = new Inventory();
	inventory->position = { WIN_WIDTH - 300, CENTER_Y };

	store->SetInventory(inventory);
}

InventoryScene::~InventoryScene()
{
	DataManager::Delete();

	delete store;
	delete inventory;
}

void InventoryScene::Update()
{
	store->Update();
	inventory->Update();
}

void InventoryScene::Render()
{
	store->Render();
	inventory->Render();
}
