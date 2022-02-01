#include "Framework.h"

TileMap::TileMap(UINT width, UINT height)
	:width(width), height(height)
{
	CreateTile();
}

TileMap::TileMap(string file)
{
	Load(file);
}

TileMap::~TileMap()
{
	for (Tile* tile : bgTiles)
		delete tile;

	for (Tile* tile : objTiles)
		delete tile;
}

void TileMap::Update()
{
	UpdateWorld();

	for (Tile* tile : bgTiles)
		tile->Update();

	for (Tile* tile : objTiles)
		tile->Update();
}

void TileMap::Render()
{
	for (Tile* tile : bgTiles)
		tile->Render();

	for (Tile* tile : objTiles)
		tile->Render();
}

void TileMap::ClickTile(wstring textureFile, Tile::Type type)
{
	switch (type)
	{
	case Tile::BG:
		SetBgTile(textureFile);
		break;
	case Tile::OBJ:
		SetObjTile(textureFile);
		break;
	default:
		break;
	}
}

void TileMap::DeleteObjTile(Vector2 pos)
{
	vector<Tile*>::iterator iter = objTiles.begin();

	for (; iter != objTiles.end(); )
	{
		if ((*iter)->GetCollider()->IsPointCollision(pos))
		{
			delete* iter;
			iter = objTiles.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void TileMap::Save(string file)
{
	BinaryWriter writer(file);

	writer.UInt(width);
	writer.UInt(height);

	writer.UInt(bgTiles.size());

	for (Tile* tile : bgTiles)
	{
		Tile::Data data = tile->GetData();

		writer.WString(data.textureFile);
		writer.Float(data.pos.x);
		writer.Float(data.pos.y);
		writer.Int(data.type);
	}

	writer.UInt(objTiles.size());

	for (Tile* tile : objTiles)
	{
		Tile::Data data = tile->GetData();

		writer.WString(data.textureFile);
		writer.Float(data.pos.x);
		writer.Float(data.pos.y);
		writer.Int(data.type);
	}
}

void TileMap::Load(string file)
{
	DeleteAllTile();

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
		tile->UpdateWorld();
		objTiles.push_back(tile);
	}
}

void TileMap::PushCollider(Tank* tank)
{
	RectCollider* collider = (RectCollider*)tank->GetCollider();

	for (Tile* tile : objTiles)
	{
		Vector2 overlap;
		if (collider->IsRectCollision((RectCollider*)tile->GetCollider(), &overlap))
		{
			if (overlap.x > overlap.y)//상하충돌
			{
				if (tank->GlobalPos().y > tile->GlobalPos().y)
				{
					tank->position.y += overlap.y;
				}
				else
				{
					tank->position.y -= overlap.y;
				}
			}
			else
			{
				if (tank->GlobalPos().x > tile->GlobalPos().x)
				{
					tank->position.x += overlap.x;
				}
				else
				{
					tank->position.x -= overlap.x;
				}
			}
		}
	}
}

vector<Node*> TileMap::GetNodes()
{
	vector<Node*> nodes;

	for (Tile* tile : bgTiles)
	{
		Vector2 tilePos = tile->GlobalPos();
		Node* node = new Node(tilePos, nodes.size());

		for (Tile* obj : objTiles)
		{
			Vector2 objPos = obj->GlobalPos();
			if (tilePos.x == objPos.x && tilePos.y == objPos.y)
			{
				node->SetState(Node::OBSTACLE);
			}
		}

		nodes.push_back(node);
	}

	return nodes;
}

void TileMap::CreateTile()
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
			data.pos = Vector2(tileSize.x * x, tileSize.y * y);

			Tile* tile = new Tile(data);
			tile->SetParent(this);
			tile->UpdateWorld();
			bgTiles.push_back(tile);
		}
	}
}

void TileMap::SetBgTile(wstring textureFile)
{
	for (Tile* tile : bgTiles)
	{
		if (tile->GetCollider()->IsPointCollision(CAM->ScreenToWorld(mousePos)))
		{
			tile->SetTile(textureFile);
		}
	}
}

void TileMap::SetObjTile(wstring textureFile)
{
	Tile::Data data;

	for (Tile* tile : bgTiles)
	{
		if (tile->GetCollider()->IsPointCollision(CAM->ScreenToWorld(mousePos)))
		{
			data = tile->GetData();
			data.textureFile = textureFile;
			data.type = Tile::OBJ;
			break;
		}
	}

	if (data.textureFile.size() == 0) return;

	Tile* tile = new Tile(data);
	tile->SetParent(this);
	tile->UpdateWorld();

	DeleteObjTile(tile->GlobalPos());

	objTiles.push_back(tile);
}

void TileMap::DeleteAllTile()
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
