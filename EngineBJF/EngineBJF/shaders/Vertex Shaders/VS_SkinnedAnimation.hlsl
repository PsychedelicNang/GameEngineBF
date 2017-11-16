cbuffer ModelViewProjectConstantBuffer : register(b0)
{
	matrix model;
	matrix view;
	matrix projection;
}

cbuffer SkinnedTransforms : register(b1)
{
	matrix transforms[37];
}

struct VertexShaderInput
{
	float4 pos : POSITION;
	float4 color : COLOR;
	float2 uvs : UVS;
    float2 padding : PADDING;
	float4 normal : NORMALS;
    float4 weight : WEIGHT;
	int4 joint : JOINT;
};

struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float2 uvs : UVS;
    float2 padding : PADDING;
	float4 normal : NORMALS;
};

PixelShaderInput main(VertexShaderInput input)
{
	PixelShaderInput output;
    output.padding.x = 0.f;
    output.padding.y = 0.f;

	float4 pos = input.pos;
	float4 skinnedPos = float4(0.f, 0.f, 0.f, 1.f);
	pos.w = 1.f;
    skinnedPos += mul(transforms[input.joint.x], pos) * input.weight.x;
    skinnedPos += mul(transforms[input.joint.y], pos) * input.weight.y;
    skinnedPos += mul(transforms[input.joint.z], pos) * input.weight.z;
    skinnedPos += mul(transforms[input.joint.w], pos) * input.weight.w;
    skinnedPos = mul(skinnedPos, model);
    skinnedPos = mul(skinnedPos, view);
    skinnedPos = mul(skinnedPos, projection);

    float4 skinnedNormals = float4(0.f, 0.f, 0.f, 0.f);
    skinnedNormals += mul(transforms[input.joint.x], input.normal) * input.weight.x;
    skinnedNormals += mul(transforms[input.joint.y], input.normal) * input.weight.y;
    skinnedNormals += mul(transforms[input.joint.z], input.normal) * input.weight.z;
    //skinnedNormals += mul(transforms[input.joint.w], input.normal) * input.weight.w;
    float3 normal = float3(skinnedNormals.x, skinnedNormals.y, skinnedNormals.z);
    output.normal = float4(mul(normal, (float3x3) model), 1.f);
    output.pos = skinnedPos;
	output.color = input.color;
	output.uvs = input.uvs;
	return output;
}