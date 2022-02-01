#pragma once

class BrickManager
{
private:
	vector<Brick*> bricks;

public:
	BrickManager();
	~BrickManager();

	void Update();
	void Render();

	void CreateStage();
	void ClearStage();

	Direction Collision(class Ball* ball);
};