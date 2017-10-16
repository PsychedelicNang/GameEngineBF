texture2D diffuse : register(t0);
texture2D emissive : register(t1);
texture2D specular : register(t2);
Texture2DArray tex : register(t3);
SamplerState envFilter : register(s0);

struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float4 uvs : UVS;
	float4 cameraPos : CAMERAPOSITION;
	float3 normal : NORMALS;
};

float4 main(PixelShaderInput input) : SV_TARGET
{
	/*Random stuff I tried*/

	//float4 c01 = tex.Sample(envFilter, float3(input.uvs.x, input.uvs.y, 0));
	//float4 c02 = tex.Sample(envFilter, float3(input.uvs.x, input.uvs.y, 1));
	//float4 c03 = tex.Sample(envFilter, float3(input.uvs.x, input.uvs.y, 2));
	//result = env.Sample(envFilter, float3(input.uvs.x, input.uvs.y, 0));
	//result += env.Sample(envFilter, float3(input.uvs.x, input.uvs.y, 1));
	//result += env.Sample(envFilter, float3(input.uvs.x, input.uvs.y, 2));
	//result = env.Sample(envFilter, input.uvs.xyz);
	//float4 surfaceColor = env.Sample(envFilter, input.uvs.xy);
	//return color01 * (color02 + color03);
	//return emissiveColor + diffuseColor + specularColor;
	//return diffuseColor * (emissiveColor + specularColor);
	//texture * (light amount + ambient)
	//float3 viewDir = normalize(cameraPos - modelPos);
	//float3 lightDir = float3(0.f, 5.f, 0.f);
	//float3 halfVector = normalize((-lightDir) + viewDir);
	//float intensity = pow(clamp(dot(normal, halfVector)), specularPower);
	/****************************************/

	///*These calculations aren't it.. idk why*/
	//float4 diffuseColor = diffuse.Sample(envFilter, input.uvs.xy);
	//float4 emissiveColor = emissive.Sample(envFilter, input.uvs.xy);
	//float4 specularColor = specular.Sample(envFilter, input.uvs.xy);
	//
	//float shininess = 6.311791f;
	//float3 lightDir = float3(0.f, 5.f, 0.f);
	//float lambertian = max(dot(lightDir, input.normal), 0.0);
	//float3 viewDir = normalize(input.cameraPos - input.pos);
	//float3 halfDir = normalize(lightDir + viewDir);
	//float specAngle = max(dot(halfDir, input.normal), 0.f);
	//float specular = pow(specAngle, shininess);

	//float3 colorLinear = emissiveColor + 0.8f * diffuseColor + specularColor * specular;
	//return float4(colorLinear, 0.f);
	///*************************************/

	/*These calculations might be it*/
	float shininess = 6.311791f;
	float4 diffuseColor = diffuse.Sample(envFilter, input.uvs.xy);
	float4 emissiveColor = emissive.Sample(envFilter, input.uvs.xy);
	float4 specularColor = specular.Sample(envFilter, input.uvs.xy);
	float3 lightDir01 = float3(-5.f, 0.f, 0.f);
	float3 lightDir02 = float3(0.f, -5.f, 0.f);
	float3 lightDir = lightDir01 - lightDir02;
	float diffuse = max(dot(normalize(input.normal), normalize(lightDir)), 0.f);
	float3 viewDir = normalize(input.cameraPos - input.pos);
	float3 halfDir = normalize(normalize(lightDir) + viewDir);
	float specular = pow(max(dot(halfDir, normalize(input.normal)), 0.f), shininess);

	float3 coolar = diffuseColor * diffuse + emissiveColor + specularColor * specular;
	float4 color = float4(coolar, 1.f);
	return color;
	/*************************************/

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