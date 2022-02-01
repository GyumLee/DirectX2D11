#include "Framework.h"
#include "KnightScene.h"

KnightScene::KnightScene() : isStop(false), time(0.0f)
{
	bg = new Quad(L"Textures/background.png");
	bg->scale *= 3.0f;

	Vector2 halfSize = bg->Size() * 3.0f * 0.5f;

	CAM->SetLeftTop(-halfSize.x, -halfSize.y);
	CAM->SetRightBottom(+halfSize.x, +halfSize.y);

	player = new KnightPlayer();
	monster = new knightMonster();
	monster->position = { CENTER_X, CENTER_Y };

	player->SetTarget(monster);
	monster->SetTarget(player);

	CAM->SetTarget(player);

	EffectManager::Get()->Add("exp", 10, L"Textures/Effect/explosion.png",
		Vector2(5, 3));
	EffectManager::Get()->Add("fire", 10, L"Textures/Effect/fire_8x2.png",
		Vector2(8, 2), 0.05f, true);

	inventory = new Inventory();
	inventory->position = { 600, 300 };
}

KnightScene::~KnightScene()
{
	delete bg;
	delete inventory;
}

void KnightScene::Update()
{
	if (KEY_DOWN(VK_F1))
	{
		SceneManager::Get()->Change("Start");
		return;
	}

	if (KEY_DOWN(VK_F2))
	{
		Timer::Get()->SetScale(0.0f);
		isStop = true;
		time = 0.0f;
	}
	if (isStop)
	{
		time += Timer::Get()->GetElapsed();

		if (time > 1.0f)
		{
			Timer::Get()->SetScale(1.0f);
		}
	}

	if (KEY_DOWN(VK_RBUTTON))
	{
		EffectManager::Get()->Play("fire", CAM->ScreenToWorld(mousePos));
	}

	bg->UpdateWorld();

	monster->Update();
	player->Update();

	inventory->Update();
}

void KnightScene::Render()
{
	bg->Render();

	monster->Render();
	player->Render();
}

void KnightScene::PostRender()
{
	inventory->Render();
}

void KnightScene::Start()
{
	player = new KnightPlayer();
	monster = new knightMonster();
	monster->position = { CENTER_X, CENTER_Y };

	player->SetTarget(monster);
	monster->SetTarget(player);

	CAM->SetTarget(player);
}

void KnightScene::End()
{
	delete monster;
	delete player;
}
