#include "Framework.h"
#include "SelectScene.h"

SelectScene::SelectScene()
{
	plane = new Button(L"Textures/airplane.png");
	plane->SetPixelShader(L"Shaders/PixelOutline.hlsl");
	plane->position = { CENTER_X, CENTER_Y };
	plane->GetColorBuffer()->Set(1, 0, 0);

	plane->SetEvent(bind(&SelectScene::ClickPlane, this));

	selectBuffer = new IntBuffer();
	selectBuffer->data.values[1] = 2;
	sizeBuffer = new ValueBuffer();
	sizeBuffer->data.values[0] = plane->Size().x;
	sizeBuffer->data.values[1] = plane->Size().y;
	
	colorBuffer = new ColorBuffer();
	colorBuffer->Set(1, 0, 0);
}

SelectScene::~SelectScene()
{
	delete plane;
	
	delete selectBuffer;
	delete sizeBuffer;
	delete colorBuffer;
}

void SelectScene::Update()
{
	plane->Update();
}

void SelectScene::Render()
{
	selectBuffer->SetPS(1);
	sizeBuffer->SetPS(2);
	colorBuffer->SetPS(3);

	plane->Render();
}

void SelectScene::ClickPlane()
{
	if (selectBuffer->data.values[0])
		selectBuffer->data.values[0] = 0;
	else
		selectBuffer->data.values[0] = 1;
}
