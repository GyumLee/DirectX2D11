#include "Framework.h"

GameMap::GameMap(string file)
{
	Load(file);

	UINT mapWidth = (UINT)tileSize.x * width;
	UINT mapHeight = (UINT)tileSize.y * height;

	renderTarget = new RenderTarget(mapWidth, mapHeight);
	targetTexture = new Quad(Vector2(mapWidth, mapHeight));

	Texture* texture = Texture::Add(L"GameMap", renderTarget->GetSRV());
	targetTexture->SetTexture(texture);
	targetTexture->SetParent(this);
	targetTexture->position = { mapWidth * 0.5f, mapHeight * 0.5f };

	DrawTile();
}

GameMap::~GameMap()
{
	DeleteAllTile();

	delete renderTarget;
	delete targetTexture;
}

void GameMap::Update()
{
	UpdateWorld();

	for (Tile* tile : objTiles)
		tile->Update();

	targetTexture->UpdateWorld();
}

void GameMap::Render()
{
	targetTexture->Render();

	for (Tile* tile : objTiles)
		tile->Render();
}

void GameMap::Load(string file)
{
	BinaryReader reader(file);

	width = reader.UInt();
	height = reader.UInt();

	CreateTile();

	UINT size = reader.UInt();

	for (UINT i = 0; i < size; i++)
	{
		Tile::Data data;
		data.textureFile = reader.WString();
		data.pos.x = reader.Float();
		data.pos.y = reader.Float();
		data.type = (Tile::Type)reader.Int();

		bgTiles[i]->SetTile(data.textureFile);
	}

	size = reader.UInt();

	for (UINT i = 0; i < size; i++)
	{
		Tile::Data data;
		data.textureFile = reader.WString();
		data.pos.x = reader.Float();
		data.pos.y = reader.Float();
		data.type = (Tile::Type)reader.Int();

		Tile* tile = new Tile(data);
		tile->SetParent(this);
		tile->position += tileSize * 0.5f;
		tile->UpdateWorld();
		objTiles.push_back(tile);
	}
}

void GameMap::CreateTile()
{
	wstring baseFile = L"Textures/TileMap/tileGrass1.png";
	Texture* baseImage = Texture::Add(baseFile);
	tileSize = baseImage->GetSize();

	for (UINT y = 0; y < height; y++)
	{
		for (UINT x = 0; x < width; x++)
		{
			Tile::Data data;
			data.textureFile = baseFile;
			data.type = Tile::BG;
			data.pos = Vector2(tileSize.x * x, tileSize.y * y) + tileSize * 0.5f;

			Tile* tile = new Tile(data);
			tile->SetParent(this);
			tile->UpdateWorld();
			bgTiles.push_back(tile);
		}
	}
}

void GameMap::DeleteAllTile()
{
	for (Tile* tile : bgTiles)
	{
		delete tile;
	}

	bgTiles.clear();

	for (Tile* tile : objTiles)
	{
		delete tile;
	}

	objTiles.clear();
}

void GameMap::DrawTile()
{
	renderTarget->Set();

	for (Tile* tile : bgTiles)
	{
		tile->Update();
		tile->Render();
	}
}
