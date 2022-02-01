#include "Framework.h"
#include "PixelShaderScene.h"

PixelShaderScene::PixelShaderScene() : color(1, 1, 1)
{
	quad = new Quad(L"Textures/airplane.png");
	quad->position = { CENTER_X, CENTER_Y };
	quad->UpdateWorld();

	//quad->SetPixelShader(L"Shaders/PixelGrayscale.hlsl");
	//quad->SetPixelShader(L"Shaders/PixelMulti.hlsl");
	//quad->SetPixelShader(L"Shaders/PixelFilter.hlsl");
	//quad->SetPixelShader(L"Shaders/PixelOutline.hlsl");
	quad->SetPixelShader(L"Shaders/PixelLight.hlsl");

	selectBuffer = new IntBuffer();
	sizeBuffer = new ValueBuffer();
	sizeBuffer->data.values[0] = quad->Size().x;
	sizeBuffer->data.values[1] = quad->Size().y;
	sizeBuffer->data.values[2] = quad->Size().x * 0.5f;
	sizeBuffer->data.values[3] = quad->Size().y * 0.5f;

	secondMap = Texture::Add(L"Textures/sun.png");
}

PixelShaderScene::~PixelShaderScene()
{
	delete quad;
	delete selectBuffer;
	delete sizeBuffer;
}

void PixelShaderScene::Update()
{
}

void PixelShaderScene::Render()
{
	selectBuffer->SetPS(1);
	sizeBuffer->SetPS(2);
	secondMap->Set(1);

	quad->Render();

	ImGui::ColorEdit3("Color", (float*)&color);
	quad->GetColorBuffer()->Set(color.x, color.y, color.z);

	ImGui::InputInt("SelectNum", &selectBuffer->data.values[0]);
	ImGui::InputInt("Scale", &selectBuffer->data.values[1]);
	//ImGui::InputInt("Scale1", &selectBuffer->data.values[2]);
	//ImGui::InputInt("Scale2", &selectBuffer->data.values[3]);
	ImGui::SliderFloat("PosX", &sizeBuffer->data.values[2], 0, quad->Size().x);
	ImGui::SliderFloat("PosY", &sizeBuffer->data.values[3], 0, quad->Size().y);
}
