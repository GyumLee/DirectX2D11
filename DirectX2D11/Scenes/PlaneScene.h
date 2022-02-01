#pragma once

class PlaneScene : public Scene
{
private:
	Plane* plane;

	Quad* bg;

	EnemyManager* enemyManager;

public:
	PlaneScene();
	~PlaneScene();

	virtual void Update() override;
	virtual void Render() override;
};