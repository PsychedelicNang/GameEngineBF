cbuffer ParticleSystemPropertiesConstantBuffer : register(b0)
{
	matrix model;
	float particleDeviationX, particleDeviationY, particleDeviationZ;
	float particleVelocity, particleVelocityVariation;
	float particleSize, particlesPerSecond;
	float deltaTime;
	uint maxParticles;
}

struct SimpleParticle
{
	float3 initialPosition  : INITIALPOS;
	float3 initialVelocity  : INITIALVEL;
	float2 size			    : SIZE;
	float age				: AGE;
	uint type				: TYPE;
};

RWStructuredBuffer<SimpleParticle> results : register(u0);

[numthreads(10, 10, 1)] // Launch 900 threads per group ( 30 * 30 * 1) == 900 ... must be <= 1024
void main( uint3 DTid : SV_DispatchThreadID )
{
	// SV_DispatchThreadID tells us which particle we are

	// compute physics on particle

	// store the information
}