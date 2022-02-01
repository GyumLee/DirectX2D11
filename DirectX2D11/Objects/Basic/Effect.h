#pragma once

class Effect : public Quad
{
private:
	FrameBuffer* frameBuffer;

	Vector2 maxFrame;

	float delayTime;
	float time;

	UINT curFrameNum;
	UINT maxFrameNum;

	bool isAdditive;

public:
	Effect(wstring textureFile, Vector2 maxFrame, float delayTime, bool isAdditive);
	~Effect();
	
	void Update();
	void Render();

	void Play(Vector2 pos);
	void End();
};