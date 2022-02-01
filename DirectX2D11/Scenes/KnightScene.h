#pragma once

class KnightScene : public Scene
{
private:
	Quad* bg;

	KnightPlayer* player;
	knightMonster* monster;

	float time;
	bool isStop;

	Inventory* inventory;

public:
	KnightScene();
	~KnightScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	virtual void Start() override;
	virtual void End() override;
};