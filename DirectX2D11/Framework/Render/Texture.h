#pragma once

class Texture
{
private:
	ScratchImage image;

	ID3D11ShaderResourceView* srv;

	static unordered_map<wstring, Texture*> textures;

	Texture(ID3D11ShaderResourceView* srv, ScratchImage& image);
	~Texture();

public:
	static Texture* Add(wstring file);
	static Texture* Add(wstring key, ID3D11ShaderResourceView* srv);
	static void Delete();

	void Set(UINT slot = 0);

	Vector2 GetSize();
};