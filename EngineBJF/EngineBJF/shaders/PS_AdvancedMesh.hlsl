struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float4 uvs : UVS;
	float3 normal : NORMALS;
};

float4 main(PixelShaderInput input) : SV_TARGET
{
	float3 lightDir01 = float3(-5.f, 0.f, 0.f);
	float3 lightDir02 = float3(0.f, -5.f, 0.f);
	float3 lightDir = lightDir01 - lightDir02;
	float lightRatio = saturate(dot(normalize(lightDir), input.normal));
	float4 result = lightRatio * float4(.5f, 1.f, 1.f, 1.f);
	return result;
	
	//return float4(.5f, 1.f, 1.f, 1.f);
	//return input.color;
}