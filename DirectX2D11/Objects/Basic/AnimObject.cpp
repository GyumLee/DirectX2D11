#include "Framework.h"

AnimObject::AnimObject() : curClip(nullptr)
{
	vertexShader = Shader::AddVS(L"Shaders/VertexUV.hlsl");
	pixelShader = Shader::AddPS(L"Shaders/PixelUV.hlsl");

	worldBuffer = new MatrixBuffer();
	colorBuffer = new ColorBuffer();
}

AnimObject::~AnimObject()
{
	for (Clip* clip : clips)
	{
		delete clip;
	}

	delete worldBuffer;
	delete colorBuffer;
}

void AnimObject::Update()
{
	if (curClip == nullptr) return;

	curClip->Update();
	UpdateWorld();
	worldBuffer->Set(world);
}

void AnimObject::Render()
{
	if (curClip == nullptr) return;

	vertexShader->Set();
	pixelShader->Set();

	worldBuffer->SetVS(0);
	colorBuffer->SetPS(0);

	curClip->Render();
}
