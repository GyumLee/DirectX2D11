#pragma once

class GameMap : public Transform
{
private:
	UINT width, height;

	Vector2 tileSize;

	vector<Tile*> bgTiles;
	vector<Tile*> objTiles;

	RenderTarget* renderTarget;
	Quad* targetTexture;

public:
	GameMap(string file);
	~GameMap();

	void Update();
	void Render();

	UINT GetWidth() { return width; }

private:
	void Load(string file);

	void CreateTile();
	void DeleteAllTile();

	void DrawTile();
};