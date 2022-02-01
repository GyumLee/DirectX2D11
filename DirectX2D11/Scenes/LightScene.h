#pragma once

class LightScene : public Scene
{
private:
	Quad* bg;

	KnightPlayer* player;
	vector<knightMonster*> monsters;

	Vector2 halfSize;

	RenderTarget* renderTarget;
	Quad* targetTexture;

	IntBuffer* selectBuffer;
	ValueBuffer* sizeBuffer;

public:
	LightScene();
	~LightScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;

	virtual void Start() override;
	virtual void End() override;
};