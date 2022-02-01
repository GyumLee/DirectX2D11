#pragma once

class BreakOutScene : public Scene
{
private:
	Stick* stick;
	Ball* ball;
	BrickManager* brickManager;

public:
	BreakOutScene();
	~BreakOutScene();

	virtual void Update() override;
	virtual void Render() override;
};