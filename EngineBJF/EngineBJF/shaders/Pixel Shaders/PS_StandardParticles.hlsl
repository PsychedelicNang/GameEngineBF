texture2D shaderTexture : register(t0);
SamplerState envFilter : register(s0);

struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float2 uvs	 : UVS;
};

float4 main(PixelShaderInput input) : SV_TARGET
{
	float4 textureColor = shaderTexture.Sample(envFilter, input.uvs.xy);

	float4 finalColor = textureColor * input.color;

	return finalColor;
}