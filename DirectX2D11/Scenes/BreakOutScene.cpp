#include "Framework.h"
#include "BreakOutScene.h"

BreakOutScene::BreakOutScene()
{
	stick = new Stick();
	stick->position.x = CENTER_X;
	stick->position.y = WIN_HEIGHT * 0.9f;

	ball = new Ball();
	ball->SetStick(stick);

	brickManager = new BrickManager();

	ball->SetBrick(brickManager);
}

BreakOutScene::~BreakOutScene()
{
	delete stick;
	delete ball;
	delete brickManager;
}

void BreakOutScene::Update()
{
	stick->Update();
	ball->Update();
	brickManager->Update();
}

void BreakOutScene::Render()
{
	stick->Render();
	ball->Render();
	brickManager->Render();
}
