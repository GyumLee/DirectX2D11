#pragma once

class Frame
{
protected:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;

	vector<Vertex> vertices;
	vector<UINT> indices;

	Texture* texture;

	Vector2 size;

public:
	Frame(wstring textureFile,
		Vector2 cutStart = Vector2(0, 0), Vector2 cutEnd = Vector2(1, 1));
	Frame(wstring textureFile, float x, float y, float w, float h);
	~Frame();

	void Render();

	Vector2 Size() { return size; }
};