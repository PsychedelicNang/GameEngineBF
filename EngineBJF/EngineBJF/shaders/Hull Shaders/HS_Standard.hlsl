cbuffer HullShaderConstantBuffer : register (b1)
{
	//matrix model;
	//float4 cameraPos : CAMPOS;
	float tessellationAmount;
	float3 padding;
}

// Input control point
struct VS_CONTROL_POINT_OUTPUT
{
	//float3 vPosition : WORLDPOS;
	// TODO: change/add other stuff
	float4 position : POSITION;
	float4 color	: COLOR;
};

// Output control point
struct HS_CONTROL_POINT_OUTPUT
{
	//float3 vPosition : WORLDPOS; 
	float4 position : POSITION;
	float4 color	: COLOR;

	//float4 color : COLOR;
};

// Output patch constant data.
struct HS_CONSTANT_DATA_OUTPUT
{
	//float EdgeTessFactor[3]			: SV_TessFactor; // e.g. would be [4] for a quad domain
	//float InsideTessFactor			: SV_InsideTessFactor; // e.g. would be Inside[2] for a quad domain
	// EdgeTessFactor and InsideTessFactor is between 0-64
	
	// Can choose the level of division for sides and interior

	// TODO: change/add other stuff
	float EdgeTessFactor[3]		: SV_TessFactor; // e.g. would be [4] for a quad domain
	float InsideTessFactor		: SV_InsideTessFactor; // e.g. would be Inside[2] for a quad domain
};

//#define NUM_CONTROL_POINTS 4

// Patch Constant Function
//HS_CONSTANT_DATA_OUTPUT CalcHSPatchConstants( InputPatch<VS_CONTROL_POINT_OUTPUT, NUM_CONTROL_POINTS> ip, uint PatchID : SV_PrimitiveID)
HS_CONSTANT_DATA_OUTPUT CalcHSPatchConstants(InputPatch<VS_CONTROL_POINT_OUTPUT, 3> patch, uint PatchID : SV_PrimitiveID)
{
	HS_CONSTANT_DATA_OUTPUT Output;

	// Find the center of the patch in world space
	//float3 centerP = 0.25f * (patch[0].position + patch[1].position + patch[2].position + patch[3].position);
	//float3 centerWorld = mul(float4(centerP, 1.f), model).xyz;
	//
	//float dist = distance(centerWorld, cameraPos);
	//
	//const float d0 = 20.f;
	//const float d1 = 100.f;
	//float tess = 64.f * saturate((d1 - dist) / (d1 - d0));

	// Insert code to compute Output here
	Output.EdgeTessFactor[0] = tessellationAmount;
	Output.EdgeTessFactor[1] = tessellationAmount;
	Output.EdgeTessFactor[2] = tessellationAmount;

	Output.InsideTessFactor = tessellationAmount; // e.g. could calculate dynamic tessellation factors instead
	//InsideTessFactor is the number of partitions
	//Output.color = patch[0].color;

	return Output;
}

[domain("tri")]		// tessellator builds triangles
[partitioning("integer")] // type of division
[outputtopology("triangle_cw")] // tolpoloy output
[outputcontrolpoints(3)]		// number of control points sent to the Domain Shader
[patchconstantfunc("CalcHSPatchConstants")]	// points to HLSL function which computes
HS_CONTROL_POINT_OUTPUT main(
	InputPatch<VS_CONTROL_POINT_OUTPUT, 3> p,
	uint i : SV_OutputControlPointID,
	uint PatchID : SV_PrimitiveID)
{
	HS_CONTROL_POINT_OUTPUT Output;

	// Insert code to compute Output here
	Output.position = p[i].position;
	Output.color = p[i].color;

	return Output;
}

//[domain("tri")]		// tessellator builds triangles
//[partitioning("fractional_odd")] // type of division
//[outputtopology("triangle_cw")] // tolpoloy output
//[outputcontrolpoints(3)]		// number of control points sent to the Domain Shader
//[patchconstantfunc("CalcHSPatchConstants")]	// points to HLSL function which computes
//HS_CONTROL_POINT_OUTPUT main( 
//	InputPatch<VS_CONTROL_POINT_OUTPUT, NUM_CONTROL_POINTS> ip, 
//	uint i : SV_OutputControlPointID,
//	uint PatchID : SV_PrimitiveID )
//{
//	HS_CONTROL_POINT_OUTPUT Output;
//
//	// Insert code to compute Output here
//	Output.vPosition = ip[i].vPosition;
//
//	return Output;
//}


// ALL of this runs ONCE PER PATCH, not control point