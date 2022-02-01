#include "Framework.h"
#include "TileScene.h"

TileScene::TileScene()
{
	gameMap = new GameMap("TextData/TestMap.map");
	gameMap->position = { 50, 50 };
}

TileScene::~TileScene()
{
	delete gameMap;
}

void TileScene::Update()
{
	gameMap->Update();
}

void TileScene::Render()
{
	gameMap->Render();
}
