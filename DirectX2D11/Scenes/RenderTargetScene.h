#pragma once

class RenderTargetScene : public Scene
{
private:
	Quad* bg;
	Quad* plane;
	KnightPlayer* player;

	RenderTarget* renderTarget;

	Quad* targetTexture[2];

	IntBuffer* selectBuffer;

public:
	RenderTargetScene();
	~RenderTargetScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
};