cbuffer ModelConstantBuffer : register(b0)
{
	matrix model;
}

struct VertexShaderInput
{
	float4 vPos : POSITION;
};

struct GSInput
{
	float4 pos : SV_POSITION;
};

GSInput main(VertexShaderInput input)
{
	GSInput output;
	float4 pos = input.vPos;

	pos = mul(pos, model);
	output.pos = pos;

	return output;
}