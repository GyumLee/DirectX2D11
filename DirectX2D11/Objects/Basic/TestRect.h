#pragma once

class TestRect : public Transform
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
public:
	TestRect(Float2 pos, Float2 size);
	~TestRect();

	void Render();
	
	void SetColor(float r, float g, float b) { colorBuffer->Set(r, g, b); }
};