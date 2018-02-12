cbuffer ViewProjectConstantBuffer : register(b0)
{
	matrix view;
	matrix projection;
}

struct GSInput
{
	float4 pos : SV_POSITION;
};

struct GSOutput
{
	float4 color : COLOR;
	float4 pos : SV_POSITION;
};

[maxvertexcount(3)]
void main(
	triangle GSInput input[3],
	inout TriangleStream< GSOutput > output
)
{
	GSOutput verts[3] =
	{
		float4(1, 0, 0, 1), float4(0.3f, 0.f, 0.3f, 1.f),
		float4(1, 0, 0, 1), float4(0.6f, 0.f, 0.6f, 1.f),
		float4(1, 0, 0, 1), float4(1.f, 0.f, 1.f, 1.f)
	};
	verts[0].pos = input[0].pos;
	verts[0].pos.x -= 5;

	verts[1].pos = input[1].pos;
	verts[1].pos.x += 10;

	verts[2].pos = input[2].pos;

	for (uint i = 0; i < 3; i++)
	{
		verts[i].pos = mul(verts[i].pos, view);
		verts[i].pos = mul(verts[i].pos, projection);
	}

	output.Append(verts[0]);
	output.Append(verts[1]);
	output.Append(verts[2]);
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