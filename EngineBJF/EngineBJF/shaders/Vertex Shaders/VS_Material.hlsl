cbuffer ModelViewProjectConstantBuffer : register(b0)
{
	matrix model;
	matrix view;
	matrix projection;
}

struct VertexShaderInput 
{
	float4 pos : POSITION;
	float4 color : COLOR;
	float2 uvs : UVS;
    float2 padding : PADDING;
	float4 normal : NORMALS;
};

struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float2 uvs : UVS;
    float2 padding : PADDING;
	float4 cameraPos : CAMERAPOSITION;
	float3 normal : NORMALS;
};

PixelShaderInput main(VertexShaderInput input)
{
	PixelShaderInput output;
    output.padding.x = 0;
    output.padding.y = 0;
	float4 pos = input.pos;
	pos.w = 1.f;
	pos = mul(pos, model);
	pos = mul(pos, view);
	pos = mul(pos, projection);
	float3 normal = float3(input.normal.x, input.normal.y, input.normal.z);
	output.normal = mul(normal, (float3x3)model);
	output.pos = pos;
	output.color = input.color;
	output.uvs = input.uvs;
	output.cameraPos = view[3];
	return output;
}