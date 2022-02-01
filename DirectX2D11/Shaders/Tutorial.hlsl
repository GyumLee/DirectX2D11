//hlsl : High Level Shading Language
//Semantic : purpose of using variable
//SV : System Value - RS, OM

struct VertexInput
{
	float4 pos : POSITION;
	float4 color : COLOR;
};

struct PixelInput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
};

PixelInput VS( VertexInput input )
{
	PixelInput output;
	output.pos = input.pos;
	output.color = input.color;
	
	return output;
}

float4 PS( PixelInput input ) : SV_TARGET // TARGET==backbuffer
{
	return input.color;
}