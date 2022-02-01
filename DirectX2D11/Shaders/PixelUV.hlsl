struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

cbuffer ColorBuffer : register(b0)
{
	float4 color;
}

Texture2D map : register(t0);
SamplerState samp : register(s0);

float4 PS(PixelInput input) : SV_TARGET
{
	return map.Sample(samp, input.uv) * color;
}