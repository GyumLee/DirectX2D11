struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

cbuffer ColorBuffer : register(b0)
{
	float4 color;
}

cbuffer SelectBuffer : register(b1)
{
	int selectNum;
}

Texture2D map : register(t0);
Texture2D secondMap : register(t1);

SamplerState samp : register(s0);

float4 Modulate(float2 uv)
{
	float4 tex1 = map.Sample(samp, uv);
	float4 tex2 = secondMap.Sample(samp, uv);

	return tex1 * tex2;
}

float4 Modulate2X(float2 uv)
{
	float4 tex1 = map.Sample(samp, uv);
	float4 tex2 = secondMap.Sample(samp, uv);

	return tex1 * tex2 * 2.0f;
}

float4 Add(float2 uv)
{
	float4 tex1 = map.Sample(samp, uv);
	float4 tex2 = secondMap.Sample(samp, uv);

	return tex1 + tex2;
}

float4 AddSmooth(float2 uv)
{
	float4 tex1 = map.Sample(samp, uv);
	float4 tex2 = secondMap.Sample(samp, uv);

	return tex1 + tex2 - tex1 * tex2;
}

float4 AddSigned(float2 uv)
{
	float4 tex1 = map.Sample(samp, uv);
	float4 tex2 = secondMap.Sample(samp, uv);

	return tex1 + tex2 - 0.5f;
}

float4 AddSigned2X(float2 uv)
{
	float4 tex1 = map.Sample(samp, uv);
	float4 tex2 = secondMap.Sample(samp, uv);

	return (tex1 + tex2 - 0.5f) * 2.0f;
}

float4 Negative(float2 uv)
{
	float4 tex1 = map.Sample(samp, uv);
	
	float3 rgb = 1.0f - tex1.rgb;
	
	return float4(rgb, 1.0f);
}

float4 Subtract(float2 uv)
{
	float4 tex1 = map.Sample(samp, uv);
	float4 tex2 = secondMap.Sample(samp, uv);

	return float4(tex1.rgb - tex2.rgb, 1.0f);
}

float4 RevSubtract(float2 uv)
{
	float4 tex1 = map.Sample(samp, uv);
	float4 tex2 = secondMap.Sample(samp, uv);

	return float4(tex2.rgb - tex1.rgb, 1.0f);
}

float4 PS(PixelInput input) : SV_TARGET
{
	if (selectNum == 1)
		return Modulate(input.uv) * color;
	else if (selectNum == 2)
		return Modulate2X(input.uv) * color;
	else if (selectNum == 3)
		return Add(input.uv) * color;
	else if (selectNum == 4)
		return AddSmooth(input.uv) * color;
	else if (selectNum == 5)
		return AddSigned(input.uv) * color;
	else if (selectNum == 6)
		return AddSigned2X(input.uv) * color;
	else if (selectNum == 7)
		return Negative(input.uv) * color;
	else if (selectNum == 8)
		return Subtract(input.uv) * color;
	else if (selectNum == 9)
		return RevSubtract(input.uv) * color;
	
	return map.Sample(samp, input.uv) * color;
}