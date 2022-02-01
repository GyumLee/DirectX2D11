#include "Framework.h"

BrickManager::BrickManager()
{
	CreateStage();
}

BrickManager::~BrickManager()
{
	ClearStage();
}

void BrickManager::Update()
{
	for (Brick* brick : bricks)
		brick->Update();
}

void BrickManager::Render()
{
	for (Brick* brick : bricks)
		brick->Render();
}

void BrickManager::CreateStage()
{
	int width = 10;
	int height = 3;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Brick* brick = new Brick(y + 1);

			Vector2 pos;
			pos.x = brick->Size().x * 0.5f + brick->Size().x * x;
			pos.y = brick->Size().y * 0.5f + brick->Size().y * y;

			brick->position = pos;

			bricks.push_back(brick);
		}
	}
}

void BrickManager::ClearStage()
{
	for (Brick* brick : bricks)
		delete brick;

	bricks.clear();
}

Direction BrickManager::Collision(Ball* ball)
{
	for (Brick* brick : bricks)
	{
		Direction dir = brick->Collision(ball);
		if (dir != Direction::NONE)
			return dir;
	}

	return Direction::NONE;
}
