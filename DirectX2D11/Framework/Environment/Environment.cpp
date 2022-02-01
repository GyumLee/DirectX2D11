#include "Framework.h"

Environment::Environment()
{
	CreateProjection();
	CreateSamplerState();
	CreateBlendState();
	CreateRasterizerState();

	mainCamera = new Camera();

	SetAlphaBlend();
}

Environment::~Environment()
{
	delete projection;
	delete mainCamera;

	samplerState->Release();
	alphaBlendState->Release();
	additiveBlendState->Release();
	rasterizerState->Release();
}

void Environment::SetAlphaBlend()
{
	float blendFactor[] = { 0, 0, 0, 0 };
	DC->OMSetBlendState(alphaBlendState, blendFactor, 0xffffffff);
}

void Environment::SetAdditiveBlend()
{
	float blendFactor[] = { 0, 0, 0, 0 };
	DC->OMSetBlendState(additiveBlendState, blendFactor, 0xffffffff);
}

void Environment::SetViewport(UINT width, UINT height)
{
	D3D11_VIEWPORT vp;
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;

	DC->RSSetViewports(1, &vp);
}

void Environment::SetOrthographic(UINT width, UINT height)
{
	Matrix orthographic = XMMatrixOrthographicOffCenterLH(
		0.0f, width, height, 0, -1.0f, 1.0f);

	projection->Set(orthographic);
	projection->SetVS(2);
}

void Environment::CreateProjection()
{
	projection = new MatrixBuffer();

	Matrix orthographic = XMMatrixOrthographicOffCenterLH(
		0.0f, WIN_WIDTH, WIN_HEIGHT, 0, -1.0f, 1.0f);

	projection->Set(orthographic);
	projection->SetVS(2);
}

void Environment::CreateSamplerState()
{
	D3D11_SAMPLER_DESC desc = {};
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	desc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	desc.MinLOD = 0;
	desc.MaxLOD = D3D11_FLOAT32_MAX;

	DEVICE->CreateSamplerState(&desc, &samplerState);
	DC->PSSetSamplers(0, 1, &samplerState);
}

void Environment::CreateBlendState()
{
	D3D11_BLEND_DESC desc = {};
	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	DEVICE->CreateBlendState(&desc, &alphaBlendState);

	desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;

	DEVICE->CreateBlendState(&desc, &additiveBlendState);

	//desc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
}

void Environment::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC desc = {};
	desc.CullMode = D3D11_CULL_NONE; // none = 양쪽 그리기
	desc.FillMode = D3D11_FILL_SOLID;

	DEVICE->CreateRasterizerState(&desc, &rasterizerState);
	DC->RSSetState(rasterizerState);
}
