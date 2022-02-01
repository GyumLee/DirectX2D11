#pragma once

class TestCircle
{
private:
	const UINT N = 30;

	VertexShader* vertexShader;
	PixelShader* pixelShader;

	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;

	vector<Vertex> vertices;
	vector<UINT> indices;

public:
	TestCircle(Float2 pos, float radius);
	~TestCircle();

	void Render();
};