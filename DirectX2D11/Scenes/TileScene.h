#pragma once

class TileScene : public Scene
{
private:
	GameMap* gameMap;

public:
	TileScene();
	~TileScene();

	virtual void Update() override;
	virtual void Render() override;
};