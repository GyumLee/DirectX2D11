#include "Framework.h"
#include "TankScene.h"

TankScene::TankScene()
{
	tileMap = new TileMap("TextData/TestMap.map");
	tileMap->position = { 50, 50 };
	tileMap->Update();

	tank = new Tank();

	aStar = new AStar(tileMap->GetNodes(), tileMap->GetWidth());
}

TankScene::~TankScene()
{
	delete tileMap;
	delete tank;

	delete aStar;
}

void TankScene::Update()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		int start = aStar->FindCloseNode(tank->position);
		int end = aStar->FindCloseNode(mousePos);

		aStar->Reset();
		tank->SetPath(aStar->GetPath(start, end));
	}

	tileMap->Update();
	tank->Update();

	aStar->Update();
	//tileMap->PushCollider(tank);
}

void TankScene::Render()
{
	tileMap->Render();
	tank->Render();

	aStar->Render();
}
