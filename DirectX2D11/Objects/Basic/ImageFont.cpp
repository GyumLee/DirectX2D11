#include "Framework.h"

ImageFont::ImageFont(vector<Texture*> images, Vector2 size)
	: images(images), interval(10)
{
	for (UINT i = 0; i < LENGTH; i++)
	{
		Quad* quad = new Quad(size);
		quad->position.x = i * -size.x - interval * i;
		quad->isActive = false;
		quad->SetParent(this);
		quads.push_back(quad);
	}
}

ImageFont::~ImageFont()
{
	for (Quad* quad : quads)
		delete quad;
}

void ImageFont::Update()
{
	string str = to_string(value);

	for (UINT i = 0; i < str.size(); i++)
	{
		int num = str[i] - '0';
		int quadIndex = str.size() - i - 1;
		quads[quadIndex]->SetTexture(images[num]);
		quads[quadIndex]->isActive = true;
	}

	for (UINT i = str.size(); i < quads.size(); i++)
	{
		quads[i]->isActive = false;
	}

	for (Quad* quad : quads)
		quad->UpdateWorld();

	UpdateWorld();
}

void ImageFont::Render()
{
	for (Quad* quad : quads)
		quad->Render();
}
