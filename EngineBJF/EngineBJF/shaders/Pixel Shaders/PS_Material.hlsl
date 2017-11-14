texture2D diffuse : register(t0);
texture2D emissive : register(t1);
texture2D specular : register(t2);
Texture2DArray tex : register(t3);
SamplerState envFilter : register(s0);

struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float2 uvs : UVS;
    float2 padding : PADDING;
	float4 cameraPos : CAMERAPOSITION;
	float3 normal : NORMALS;
};

float4 main(PixelShaderInput input) : SV_TARGET
{
	float shininess = 6.311791f;
	//float4 diffuseColor = tex[1].Sample(envFilter, input.uvs.xy);
	//float4 emissiveColor = tex[0].Sample(envFilter, input.uvs.xy);
	//float4 specularColor = tex[2].Sample(envFilter, input.uvs.xy);
	float4 diffuseColor = diffuse.Sample(envFilter, input.uvs.xy);
	float4 emissiveColor = emissive.Sample(envFilter, input.uvs.xy);
	float4 specularColor = specular.Sample(envFilter, input.uvs.xy);
	float3 lightDir01 = float3(-5.f, 0.f, 0.f);
	float3 lightDir02 = float3(0.f, -5.f, 0.f);
	float3 lightDir = lightDir01 - lightDir02;
	float diffuse = max(dot(normalize(input.normal), normalize(lightDir)), 0.f);
	float4 viewDirResult = normalize(input.cameraPos - input.pos);
	float3 viewDir = float3(viewDirResult.x, viewDirResult.y, viewDirResult.z);
	float3 halfDir = normalize(normalize(lightDir) + viewDir);
	float specular = pow(max(dot(halfDir, normalize(input.normal)), 0.f), shininess);

	float4 color = diffuseColor * diffuse + emissiveColor + specularColor * specular;
	//float4 color = diffuseColor + emissiveColor + specularColor * specular;
	//float4 color = float4(coolar);
	return color;

	//float screenGamma = 2.2;
	//float3 idk = 1.0 / screenGamma;
	//float3 colorGammaCorrected = pow(colorLinear, idk);
	//float4 gl_FragColor = float4(colorGammaCorrected, 1.0);
	//return gl_FragColor;

	
	//emissive (.5, .5, .5, 1)
	//ambient (0, 0, 0, 1)
	//diffuse (1, 1, 1, .8)
	//normal (0, 0, 0)
	//specular (.5, .5, .5, 1)
	//shininess (6.311791)
	//reflection (.5)


	//VIEWDIR =
	//	NORMALIZE(CAMWORLDPOS – SURFACEPOS)
	//	HALFVECTOR =
	//	NORMALIZE((-LIGHTDIR) + VIEWDIR)
	//	INTENSITY = MAX(CLAMP(DOT(NORMAL, HALFVECTOR))SPECULARPOWER, 0)
	//	REFLECTEDLIGHT = LIGHTCOLOR * SPECULARINTENSITY * INTENSITY

	//LIGHTRATIO =
	//	CLAMP(LIGHTRATIO +
	//		AMBIENTTERM)

	//VIEWDIR = NORMALIZE(CAMWORLDPOS – SURFACEPOS)
	//HALFVECTOR = NORMALIZE((-LIGHTDIR) + VIEWDIR)
	//INTENSITY = MAX(CLAMP(DOT(NORMAL, HALFVECTOR))SPECULARPOWER , 0)
	//REFLECTEDLIGHT = LIGHTCOLOR * SPECULARINTENSITY * INTENSITY
	//^...Multiply these together...v
	//ATTENUATION = 1.0 – CLAMP(MAGNITUDE(LIGHTPOS – SURFACEPOS) / LIGHTRADIUS)
}