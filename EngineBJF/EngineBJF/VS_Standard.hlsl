cbuffer ModelViewProjectConstantBuffer : register(b0)
{
	matrix model;
	matrix view;
	matrix projection;
}

struct VertexShaderInput
{
	float4 vPos : POSITION;
	float4 vColor : COLOR;
};

struct PixelShaderInput
{
	float4 pPos : SV_POSITION;
	float4 pColor : COLOR;
};

PixelShaderInput main( VertexShaderInput input )
{
	PixelShaderInput output;
	float4 pos = input.vPos;

	pos = mul(pos, model);
	pos = mul(pos, view);
	pos = mul(pos, projection);
	output.pPos = pos;
	output.pColor = input.vColor;

	return output;
}