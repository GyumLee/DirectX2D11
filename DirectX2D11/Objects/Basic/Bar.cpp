#include "Framework.h"

Bar::Bar(wstring frontImage, wstring backImage, float maxValue)
	: maxValue(maxValue), curValue(maxValue)
{
	frontBar = new Quad(frontImage);
	frontBar->SetPixelShader(L"Shaders/PixelBar.hlsl");
	backBar = new Quad(backImage);

	//frontBar->SetPivot(frontBar->Size().x * -0.5f, 0);

	frontBar->SetParent(this);
	backBar->SetParent(this);

	valueBuffer = new ValueBuffer();
}

Bar::~Bar()
{
	delete frontBar;
	delete backBar;

	delete valueBuffer;
}

void Bar::Update()
{
	//frontBar->scale.x = curValue / maxValue;
	valueBuffer->data.values[0] = maxValue;
	valueBuffer->data.values[1] = curValue;

	frontBar->UpdateWorld();
	backBar->UpdateWorld();

	UpdateWorld();
}

void Bar::Render()
{
	backBar->Render();

	valueBuffer->SetPS(1);
	frontBar->Render();
}
