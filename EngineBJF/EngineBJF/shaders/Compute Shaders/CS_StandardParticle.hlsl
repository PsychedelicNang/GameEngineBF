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

[numthreads(10, 10, 1)] // Launch 100 threads per group ( 10 * 10 * 1) == 100 ... must be <= 1024
void main( uint3 DTid : SV_DispatchThreadID,  uint groupIndex : SV_GroupIndex )
{
	// SV_DispatchThreadID tells us which particle we are
	uint particleIndex = (DTid.x * DTid.y * DTid.z) + groupIndex;
	//uint particleIndex = groupIndex;

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

	//particles[particleIndex].position.x = randomPositionsAndSpeed[groupIndex].x;
	//particles[particleIndex].position.z = randomPositionsAndSpeed[groupIndex].z;

	//particles[particleIndex].position.y -= (particleVelocity * deltaTime);

	//particles[particleIndex].position = mul(particles[particleIndex].position, model);
}