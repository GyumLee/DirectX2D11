#pragma once

//class VertexShader;

class Shader
{
protected:
	ID3DBlob* blob;

	static map<wstring, Shader*> shaders;

public:
	virtual ~Shader();

	//static VertexShader* AddVS(wstring file);
	static class VertexShader* AddVS(wstring file);
	static class PixelShader* AddPS(wstring file);
	static void Delete();

	virtual void Set() = 0;
};