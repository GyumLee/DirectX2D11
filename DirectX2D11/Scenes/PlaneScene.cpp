#include "Framework.h"
#include "PlaneScene.h"

PlaneScene::PlaneScene()
{
	bg = new Quad(L"Textures/rectEnemy.png");
	bg->scale.x = WIN_WIDTH / bg->Size().x;
	bg->scale.y = WIN_HEIGHT / bg->Size().y;
	bg->position = { CENTER_X, CENTER_Y };

	plane = new Plane();
	plane->position = { CENTER_X, CENTER_Y };

	enemyManager = new EnemyManager(L"Textures/rectEnemy.png", 30);

	enemyManager->SetPlayerBullet(plane->GetBullet());
	enemyManager->SetTarget(plane);
}

PlaneScene::~PlaneScene()
{
	delete bg;
	delete plane;
	delete enemyManager;
}

void PlaneScene::Update()
{
	plane->Update();
	bg->UpdateWorld();
	enemyManager->Update();
}

void PlaneScene::Render()
{
	bg->Render();
	plane->Render();
	enemyManager->Render();
}
