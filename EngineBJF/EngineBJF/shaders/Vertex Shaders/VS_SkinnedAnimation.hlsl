cbuffer ModelViewProjectConstantBuffer : register(b2)
{
	matrix model;
	matrix view;
	matrix projection;
}

struct VertexShaderInput
{
	float4 pos : POSITION;
	float4 color : COLOR;
	float4 uvs : UVS;
	float4 normal : NORMALS;
	float4 joint : JOINT;
	float4 weight : WEIGHT;
};

struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float4 uvs : UVS;
	float4 normal : NORMALS;
	float4 joint : JOINT;
	float4 weight : WEIGHT;
};

PixelShaderInput main(VertexShaderInput input)
{
	PixelShaderInput output;
	float4 pos = input.pos;
	pos.w = 1.f;
	pos = mul(pos, model);
	pos = mul(pos, view);
	pos = mul(pos, projection);
	float3 normal = float3(input.normal.x, input.normal.y, input.normal.z);
	output.normal = float4(mul(normal, (float3x3)model), 1.f);
	output.pos = pos;
	output.color = input.color;
	output.uvs = input.uvs;
	output.joint = input.joint;
	output.weight = input.weight;
	return output;
}