#pragma once

class TextureScene : public Scene
{
private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;

	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;

	vector<Vertex> vertices;
	vector<UINT> indices;

	MatrixBuffer* worldBuffer;
	ColorBuffer* colorBuffer;

	ID3D11ShaderResourceView* srv;
	ID3D11SamplerState* samplerState;

	Transform* transform;

	float speed = 200;

public:
	TextureScene();
	~TextureScene();

	virtual void Update() override;
	virtual void Render() override;
};