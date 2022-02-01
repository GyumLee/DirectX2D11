struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

cbuffer ColorBuffer : register(b0)
{
	float4 color;
}

cbuffer FrameBuffer : register(b1)
{
	float2 maxFrame;
	float2 curFrame;
}

Texture2D map : register(t0);
SamplerState samp : register(s0);

float4 PS(PixelInput input) : SV_TARGET
{
	float2 uv = input.uv + (curFrame / maxFrame);
	
	return map.Sample(samp, uv) * color;
}