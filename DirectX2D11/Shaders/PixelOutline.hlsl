struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

Texture2D map : register(t0);
SamplerState samp : register(s0);

cbuffer ColorBuffer : register(b0)
{
	float4 color;
}

cbuffer SelectBuffer : register(b1)
{
	int selectNum;
	int scale;
}

cbuffer SizeBuffer : register(b2)
{
	float2 imageSize;
}

cbuffer OutlineColor : register(b3)
{
	float4 outlineColor;
}

float4 Outline(float2 uv)
{
	float4 albedo = map.Sample(samp, uv);
	
	//if (albedo.a > 0)
	//	return albedo;
	
	float sum = 0;

	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			float2 offset = (float2(x, y) / imageSize) * scale;
			albedo = map.Sample(samp, uv + offset);
			
			sum += albedo.a;
		}
	}
	
	if (sum > 0.0f && sum < 9.0f)
		return outlineColor;
		
	return map.Sample(samp, uv) * color;
}
	
float4 PS(PixelInput input) : SV_TARGET
{
	if(selectNum == 1)
		return Outline(input.uv);
	
	return map.Sample(samp, input.uv) * color;
}