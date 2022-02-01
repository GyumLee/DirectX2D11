#include "Framework.h"
#include "FontScene.h"

FontScene::FontScene() : time(0)
{
	FONT->Add("hanna", L"Comic Sans MS", Float3(1, 1, 0), 50);

	vector<Texture*> images;
	for (int i = 0; i < 10; i++)
	{
		wstring str = L"Textures/Font/num1_" + to_wstring(i) + L".png";
		images.push_back(Texture::Add(str));
	}

	imageFont = new ImageFont(images);
	imageFont->position = { CENTER_X, 100 };
}

FontScene::~FontScene()
{
	delete imageFont;
}

void FontScene::Update()
{
	time += DELTA * 100;
	imageFont->SetValue((UINT)time);

	imageFont->Update();
}

void FontScene::Render()
{
	////FONT->RenderText(L"Çï·Î¿ì World", "hanna", Vector2(500, 300), Vector2(500, 200));
	//FONT->RenderText(L"Çï·Î¿ì World", "hanna", Vector2(500, 300));
	//
	//wstring str = to_wstring((int)time);
	//FONT->RenderText(str, "hanna", Vector2(CENTER_X, 50));

	imageFont->Render();
}
