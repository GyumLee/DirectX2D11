#include "Framework.h"
#include "BackgroundScene.h"

BackgroundScene::BackgroundScene() : speed(1000)
{
	backgrounds[0] = new Quad(L"Textures/background.png", Vector2(0, 0), Vector2(2, 1));
	backgrounds[1] = new Quad(L"Textures/background.png", Vector2(0, 0), Vector2(2, 1));

	backgrounds[0]->scale.x = WIN_WIDTH / backgrounds[0]->Size().x;
	backgrounds[0]->scale.y = WIN_HEIGHT / backgrounds[0]->Size().y;
	backgrounds[1]->scale.x = WIN_WIDTH / backgrounds[1]->Size().x;
	backgrounds[1]->scale.y = WIN_HEIGHT / backgrounds[1]->Size().y;

	backgrounds[0]->position = { CENTER_X, CENTER_Y };
	backgrounds[1]->position = { CENTER_X + WIN_WIDTH, CENTER_Y };

	mario = new Mario();
	mario->position = { CENTER_X, CENTER_Y };
}

BackgroundScene::~BackgroundScene()
{
	delete mario;
}

void BackgroundScene::Update()
{
	for (Quad* background : backgrounds)
	{
		background->position.x -= speed * DELTA;

		if (background->position.x <= -CENTER_X)
		{
			background->position.x += WIN_WIDTH * 2.0f;
		}

		background->UpdateWorld();
	}

	mario->Update();
}

void BackgroundScene::Render()
{
	for (Quad* background : backgrounds)
	{
		background->Render();
	}

	mario->Render();
}
