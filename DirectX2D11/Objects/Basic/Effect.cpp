#include "Framework.h"

Effect::Effect(wstring textureFile, Vector2 maxFrame, float delayTime, bool isAdditive)
	: Quad(textureFile, Vector2(0, 0), Vector2(1 / maxFrame.x, 1 / maxFrame.y)),
	delayTime(delayTime), curFrameNum(0), maxFrame(maxFrame), isAdditive(isAdditive)
{
	isActive = false;

	pixelShader = Shader::AddPS(L"Shaders/PixelEffect.hlsl");

	frameBuffer = new FrameBuffer();
	frameBuffer->SetMaxFrame(maxFrame.x, maxFrame.y);

	maxFrameNum = (UINT)(maxFrame.x * maxFrame.y);
}

Effect::~Effect()
{
	delete frameBuffer;
}

void Effect::Update()
{
	if (!isActive) return;

	time += DELTA;

	if (time > delayTime)
	{
		time -= delayTime;

		UINT x = curFrameNum % (UINT)maxFrame.x;
		UINT y = curFrameNum / (UINT)maxFrame.x;

		frameBuffer->SetCurFrame(x, y);

		curFrameNum++;

		if (curFrameNum >= maxFrameNum)
			End();
	}

	Quad::UpdateWorld();
}

void Effect::Render()
{
	if (!isActive) return;

	frameBuffer->SetPS(1);

	if (isAdditive)
		Environment::Get()->SetAdditiveBlend();

	Quad::Render();

	if (isAdditive)
		Environment::Get()->SetAlphaBlend();
}

void Effect::Play(Vector2 pos)
{
	isActive = true;
	position = pos;

	time = 0.0f;
	curFrameNum = 0;
}

void Effect::End()
{
	isActive = false;
}
