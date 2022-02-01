#pragma once

class Tile : public Quad
{
public:
	enum Type
	{
		BG, OBJ
	};

	struct Data
	{
		wstring textureFile;
		Vector2 pos;
		Type type;
	};

private:
	Data data;
	Collider* collider;

public:
	Tile(Data data);
	~Tile();

	void Update();
	void Render();

	void SetTile(wstring textureFile);

	Data GetData() { return data; }
	Collider* GetCollider() { return collider; }
};