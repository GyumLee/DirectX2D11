#pragma once

class Quad : public Transform
{
protected:
	wstring textureFile;

	VertexShader* vertexShader;
	PixelShader* pixelShader;

	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;

	vector<Vertex> vertices;
	vector<UINT> indices;

	MatrixBuffer* worldBuffer;
	ColorBuffer* colorBuffer;

	Texture* texture;

	Vector2 size;

public:
	Quad(wstring textureFile,
		Vector2 cutStart = Vector2(0, 0), Vector2 cutEnd = Vector2(1, 1));
	Quad(Vector2 size);
	~Quad();

	void Render();

	void SetRender();

	void SetPixelShader(wstring file);
	void SetVertexShader(wstring file);

	void SetTexture(wstring file);
	void SetTexture(Texture* texture) { this->texture = texture; }

	Vector2 Size() { return size; }
	ColorBuffer* GetColorBuffer() { return colorBuffer; }

	wstring GetTextureFile() { return textureFile; }
};