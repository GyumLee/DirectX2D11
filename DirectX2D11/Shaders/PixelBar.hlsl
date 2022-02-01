struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

cbuffer ColorBuffer : register(b0)
{
	float4 color;
}

cbuffer ValueBuffer : register(b1)
{
	float maxValue;
	float curValue;
}

Texture2D map : register(t0);
SamplerState samp : register(s0);

float4 PS(PixelInput input) : SV_TARGET
{
	if (input.uv.x < curValue / maxValue)
		return map.Sample(samp, input.uv) * color;
	
	return float4(0, 0, 0, 0);
}