cbuffer ParticleSystemPropertiesConstantBuffer : register(b0)
{
	float3 initialPosition;
	float3 initialVelocity;
	float particleDeviationX, particleDeviationY, particleDeviationZ;
	float particleVelocity, particleVelocityVariation;
	float particleSize, particlesPerSecond;
	uint maxParticles;
	float2 padding;
}

//cbuffer RandomNumbersConstantBuffer : register(b1)
//{
//	//[#] must == numberOfRandomNumbers
//	float4 randomColors[100];
//	float4 randomPositionsAndSpeed[100];	//xyz == position, w == speed
//}

cbuffer ParticleSystemDyamicPropertiesConstantBuffer : register(b2)
{
	matrix model;
	float deltaTime;
	float paddingAgain;
}

struct SimpleParticle
{
	float4 position;
	float4 color;
};

RWStructuredBuffer<SimpleParticle> particles : register(u0);

[numthreads(100, 1, 1)]
void main( uint3 dispatchThreadID : SV_DispatchThreadID,  uint groupIndex : SV_GroupIndex, uint3 groupThreadID : SV_GroupThreadID )
{
	//(_y * _RSWidth) + _x;

	uint particleIndex = (dispatchThreadID.y * 100) + groupIndex;

	//particles[particleIndex].age += deltaTime;

	//// If the particles is older than 10 seconds, reset the particle
	//if (particles[particleIndex].age > 10.f)
	//{
	//	particles[particleIndex].age = 0.0f;
	//	particles[particleIndex].position = initialPosition + randomPositionsAndSpeed[groupIndex].xyz;
	//	particles[particleIndex].velocity = initialVelocity * randomPositionsAndSpeed[groupIndex].w;
	//	particles[particleIndex].color = randomColors[groupIndex];
	//	particles[particleIndex].size = particleSize;
	//}

  //  particles[particleIndex].position.x -= 5.0f * deltaTime;
	//particles[particleIndex].position.z = randomPositionsAndSpeed[groupIndex].z;

	particles[particleIndex].position.y -= (particleVelocity * deltaTime);

	//particles[particleIndex].position = mul(particles[particleIndex].position, model);
}