struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float2 uvs : UVS;
    float2 padding : PADDING;
	float4 normal : NORMALS;
};

float4 main(PixelShaderInput input) : SV_TARGET
{
	float3 normal = float3(input.normal.x, input.normal.y, input.normal.z);
	float3 lightDir01 = float3(-5.f, 0.f, 0.f);
	float3 lightDir02 = float3(0.f, -5.f, 0.f);
	float3 lightDir = lightDir01 - lightDir02;
	float lightRatio = saturate(dot(normalize(lightDir), normal));
	float4 result = lightRatio * float4(.5f, 1.f, 1.f, 1.f);
	return result;

	//return float4(.5f, 1.f, 1.f, 1.f);
	//return input.color;
}