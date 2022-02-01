#pragma once

class TileMap : public Transform
{
private:
	UINT width, height;

	Vector2 tileSize;

	vector<Tile*> bgTiles;
	vector<Tile*> objTiles;

public:
	TileMap(UINT width, UINT height);
	TileMap(string file);
	~TileMap();

	void Update();
	void Render();

	void ClickTile(wstring textureFile, Tile::Type type);
	void DeleteObjTile(Vector2 pos);

	void Save(string file);
	void Load(string file);

	void PushCollider(class Tank* tank);

	vector<Node*> GetNodes();

	UINT GetWidth() { return width; }

private:
	void CreateTile();

	void SetBgTile(wstring textureFile);
	void SetObjTile(wstring textureFile);

	void DeleteAllTile();
};