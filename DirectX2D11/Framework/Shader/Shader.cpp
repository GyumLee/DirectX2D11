#include "Framework.h"

map<wstring, Shader*> Shader::shaders;

Shader::~Shader()
{
	blob->Release();
}

VertexShader* Shader::AddVS(wstring file)
{
	if (shaders.count(file) > 0)
		return (VertexShader*)shaders[file];

	VertexShader* shader = new VertexShader(file);
	shaders[file] = shader;

	return shader;
}

PixelShader* Shader::AddPS(wstring file)
{
	if (shaders.count(file) > 0)
		return (PixelShader*)shaders[file];

	PixelShader* shader = new PixelShader(file);
	shaders[file] = shader;

	return shader;
}

void Shader::Delete()
{
	for (auto Shader : shaders)
		delete Shader.second;
}
