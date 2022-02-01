#pragma once

class Environment : public Singleton<Environment>
{
private:
	friend class Singleton;

	MatrixBuffer* projection;

	ID3D11SamplerState* samplerState;
	ID3D11BlendState* alphaBlendState;
	ID3D11BlendState* additiveBlendState;
	ID3D11RasterizerState* rasterizerState;

	Camera* mainCamera;

	Environment();
	~Environment();

public:
	Camera* GetMainCamera() { return mainCamera; }

	void SetAlphaBlend();
	void SetAdditiveBlend();

	void SetViewport(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);
	void SetOrthographic(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);

private:
	void CreateProjection();
	void CreateSamplerState();
	void CreateBlendState();
	void CreateRasterizerState();
};