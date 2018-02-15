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

cbuffer RandomNumbersConstantBuffer : register(b1)
{
	//[#] must == numberOfRandomNumbers
	float4 randomColors[100];
	float3 randomPositions[100];
	float  randomSpeed[100];
}

cbuffer ParticleSystemDyamicPropertiesConstantBuffer : register(b2)
{
	matrix model;
	float deltaTime;
	float paddingAgain;
}

struct SimpleParticle
{
	float3 position  : POSITION;
	float3 velocity  : VELOCITY;
	float4 color	 : COLOR; 
	float2 size		 : SIZE;
	float age		 : AGE;
	float speed : SPEED;
};

RWStructuredBuffer<SimpleParticle> particles : register(u0);

[numthreads(10, 10, 1)] // Launch 100 threads per group ( 10 * 10 * 1) == 100 ... must be <= 1024
void main( uint3 DTid : SV_DispatchThreadID,  uint groupIndex : SV_GroupIndex )
{
	// SV_DispatchThreadID tells us which particle we are
	uint particleIndex = (DTid.x * DTid.y * DTid.z) + groupIndex;

	particles[particleIndex].age += deltaTime;

	// If the particles is older than 10 seconds, reset the particle
	if (particles[particleIndex].age > 10.f)
	{
		particles[particleIndex].age = 0.0f;
		particles[particleIndex].position = initialPosition + randomPositions[groupIndex];
		particles[particleIndex].velocity = initialVelocity * randomSpeed[groupIndex];
		particles[particleIndex].color = randomColors[groupIndex];
		particles[particleIndex].size = particleSize;
	}

	particles[particleIndex].position.y -= (particleVelocity * deltaTime * 0.1f);
}