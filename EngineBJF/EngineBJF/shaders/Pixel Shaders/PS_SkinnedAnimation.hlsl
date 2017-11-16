texture2D diffuse : register(t0);
//texture2D emissive : register(t1);
//texture2D specular : register(t2);
Texture2DArray tex : register(t3);
SamplerState envFilter : register(s0);

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
    float4 diffuseColor = diffuse.Sample(envFilter, input.uvs.xy);
    //float4 emissiveColor = emissive.Sample(envFilter, input.uvs.xy);
    //float4 specularColor = specular.Sample(envFilter, input.uvs.xy);
	float3 normal = float3(input.normal.x, input.normal.y, input.normal.z);
	float3 lightDir01 = float3(-5.f, 0.f, 0.f);
	float3 lightDir02 = float3(0.f, -5.f, 0.f);
	float3 lightDir = lightDir01 - lightDir02;
	float lightRatio = saturate(dot(normalize(lightDir), normal));
	//float4 result = lightRatio * float4(.5f, 1.f, 1.f, 1.f);
    float4 result = diffuseColor * lightRatio;
	return result;


 //   float shininess = 6.311791f;
	////float4 diffuseColor = tex[1].Sample(envFilter, input.uvs.xy);
	////float4 emissiveColor = tex[0].Sample(envFilter, input.uvs.xy);
	////float4 specularColor = tex[2].Sample(envFilter, input.uvs.xy);
 //   float4 diffuseColor = diffuse.Sample(envFilter, input.uvs.xy);
 //   float4 emissiveColor = emissive.Sample(envFilter, input.uvs.xy);
 //   float4 specularColor = specular.Sample(envFilter, input.uvs.xy);
 //   float3 lightDir01 = float3(-5.f, 0.f, 0.f);
 //   float3 lightDir02 = float3(0.f, -5.f, 0.f);
 //   float3 lightDir = lightDir01 - lightDir02;
 //   float diffuse = max(dot(normalize(input.normal), normalize(lightDir)), 0.f);
 //   float4 viewDirResult = normalize(input.cameraPos - input.pos);
 //   float3 viewDir = float3(viewDirResult.x, viewDirResult.y, viewDirResult.z);
 //   float3 halfDir = normalize(normalize(lightDir) + viewDir);
 //   float specular = pow(max(dot(halfDir, normalize(input.normal)), 0.f), shininess);

 //   float4 color = diffuseColor * diffuse + emissiveColor + specularColor * specular;
	////float4 color = diffuseColor + emissiveColor + specularColor * specular;
	////float4 color = float4(coolar);
 //   return color;

	//return float4(.5f, 1.f, 1.f, 1.f);
	//return input.color;
}