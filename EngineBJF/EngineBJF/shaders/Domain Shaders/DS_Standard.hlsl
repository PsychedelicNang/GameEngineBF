cbuffer ModelViewProjectConstantBuffer : register(b2)
{
	matrix model;
	matrix view;
	matrix projection;
}

struct DS_OUTPUT
{
	float4 position  : SV_POSITION;
	float4 color	: COLOR;

	// TODO: change/add other stuff
};

// Output control point
struct HS_CONTROL_POINT_OUTPUT
{
	float4 position : POSITION;
	float4 color	: COLOR;

};

// Output patch constant data.
struct HS_CONSTANT_DATA_OUTPUT
{
	float EdgeTessFactor[3]		: SV_TessFactor; // e.g. would be [4] for a quad domain
	float InsideTessFactor		: SV_InsideTessFactor; // e.g. would be Inside[2] for a quad domain
	// TODO: change/add other stuff
};

//#define NUM_CONTROL_POINTS 3

[domain("tri")]		// must match Hull Shader domain
DS_OUTPUT main(
	HS_CONSTANT_DATA_OUTPUT input,
	float3 domain : SV_DomainLocation,
	const OutputPatch<HS_CONTROL_POINT_OUTPUT, 3> patch)
{
	DS_OUTPUT Output;
	
	// domain location used to manually interpolate newly created geometry across overall triangle

	//float4 v1 = lerp(quad[0].vPosition, quad[1].vPosition, 1 - uv.y);
	//float4 v2 = lerp(quad[3].vPosition, quad[1].vPosition, 1 - uv.y);
	//float3 position = lerp(v1, v2, uv.x);
	Output.position = patch[0].position * domain.x + patch[1].position * domain.y + patch[2].position * domain.z;
	//Output.position = domain.x * patch[0].position + domain.y * patch[1].position + domain.z * patch[2].position;

	float4 pos = Output.position;

	pos = mul(pos, model);
	pos = mul(pos, view);
	pos = mul(pos, projection);

	Output.position = pos;
	Output.color = patch[0].color;
	//Ountput.vPosition = mul(Output.vPosition, worldViewProj);
	return Output;
}
