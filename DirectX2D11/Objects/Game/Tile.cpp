#include "Framework.h"

Tile::Tile(Data data)
	: Quad(data.textureFile), data(data)
{
	position = data.pos;
	collider = new RectCollider(size);
	collider->SetParent(this);
}

Tile::~Tile()
{
	delete collider;
}

void Tile::Update()
{
	collider->UpdateWorld();
	UpdateWorld();
}

void Tile::Render()
{
	Quad::Render();

	if (data.type == OBJ)
		collider->Render();
}

void Tile::SetTile(wstring textureFile)
{
	texture = Texture::Add(textureFile);
	data.textureFile = textureFile;
}
