struct SimpleParticle
{
	float4 position;
	float4 color;
};

StructuredBuffer<SimpleParticle> particles : register(t0);

cbuffer ViewProjectConstantBuffer : register(b0)
{
	matrix model;
	matrix view;
	matrix projection;
}

struct GSInput
{
    float4 pos : POSITION;
    float4 color : COLOR;
    float2 uvs : UVS;
};

struct GSOutput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float2 uvs	 : UVS;
};

[maxvertexcount(6)]
void main(
	point GSInput input[1],
	inout TriangleStream<GSOutput> output, 
    uint primitiveId : SV_PrimitiveID
)
{
	float2 topLeft = float2(0.0f, 0.0f);
	float2 topRight = float2(1.0f, 0.0f);
	float2 bottomLeft = float2(0.0f, 1.0f);
	float2 bottomRight = float2(1.0f, 1.0f);

	//GSOutput verts[6] =
	//{
	//	{ particles[primitiveId].position, particles[primitiveId].color, bottomLeft },
	//	{ particles[primitiveId].position, particles[primitiveId].color, topLeft },
	//	{ particles[primitiveId].position, particles[primitiveId].color, topRight },
	//	{ particles[primitiveId].position, particles[primitiveId].color, topRight },
	//	{ particles[primitiveId].position, particles[primitiveId].color, bottomRight },
	//	{ particles[primitiveId].position, particles[primitiveId].color, bottomLeft }
	//};

	GSOutput verts[6] =
	{
		{ particles[primitiveId].position, float4(0.3f, 0.f, 0.3f, 1.f) , bottomLeft },
		{ particles[primitiveId].position, float4(0.6f, 0.f, 0.6f, 1.f) , topLeft },
		{ particles[primitiveId].position, float4(1.f, 0.f, 1.f, 1.f)   , topRight },
		{ particles[primitiveId].position, float4(0.3f, 0.f, 0.3f, 1.f) , topRight },
		{ particles[primitiveId].position, float4(0.6f, 0.f, 0.6f, 1.f) , bottomRight },
		{ particles[primitiveId].position, float4(1.f, 0.f, 1.f, 1.f)   , bottomLeft }
	};

	verts[1].pos.y += 1;
	verts[2].pos.x += 1;
	verts[2].pos.y += 1;
	verts[3].pos.x += 1;
	verts[3].pos.y += 1;
	verts[4].pos.x += 1;

	for (uint i = 0; i < 6; i++)
	{
		verts[i].pos = mul(verts[i].pos, model);
		verts[i].pos = mul(verts[i].pos, view);
		verts[i].pos = mul(verts[i].pos, projection);
	}

	output.Append(verts[0]);
	output.Append(verts[1]);
	output.Append(verts[2]);
	output.Append(verts[3]);
	output.Append(verts[4]);
	output.Append(verts[5]);
}


//[maxvertexcount(3)]
//void main(
//	line GSInput input[2],
//	inout TriangleStream< GSOutput > output
//)
//{
//	GSOutput verts[3] =
//	{
//		float4(1, 0, 0, 1), float4(0.3f, 0.f, 0.3f, 1.f),
//		float4(1, 0, 0, 1), float4(0.6f, 0.f, 0.6f, 1.f),
//		float4(1, 0, 0, 1), float4(1.f, 0.f, 1.f, 1.f)
//	};
//	verts[0].pos = input[0].pos;
//	verts[0].pos.x -= 5;
//
//	verts[1].pos = input[0].pos;
//	verts[1].pos.x += 10;
//
//	verts[2].pos = input[0].pos;
//
//	for (uint i = 0; i < 3; i++)
//	{
//		verts[i].pos = mul(verts[i].pos, view);
//		verts[i].pos = mul(verts[i].pos, projection);
//	}
//
//	output.Append(verts[0]);
//	output.Append(verts[1]);
//	output.Append(verts[2]);
//}