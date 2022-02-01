#pragma once

class PixelShaderScene : public Scene
{
private:
	Quad* quad;

	Float3 color;

	IntBuffer* selectBuffer;
	ValueBuffer* sizeBuffer;

	Texture* secondMap;

public:
	PixelShaderScene();
	~PixelShaderScene();

	virtual void Update() override;
	virtual void Render() override;
};