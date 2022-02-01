#pragma once

class TankScene : public Scene
{
private:
	TileMap* tileMap;

	Tank* tank;

	AStar* aStar;

public:
	TankScene();
	~TankScene();

	virtual void Update() override;
	virtual void Render() override;
};