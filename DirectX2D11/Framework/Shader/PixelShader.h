#pragma once

class PixelShader : public Shader
{
private:
	friend class Shader;

	ID3D11PixelShader* shader;

	PixelShader(wstring file);
	~PixelShader();

public:
	void Set() override;
};