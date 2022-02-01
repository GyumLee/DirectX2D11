#pragma once

class AnimObject : public Transform
{
protected:
	VertexShader* vertexShader;
	PixelShader* pixelShader;

	vector<Clip*> clips;
	Clip* curClip;

	MatrixBuffer* worldBuffer;
	ColorBuffer* colorBuffer;

public:
	AnimObject();
	~AnimObject();

	void Update();
	void Render();
};