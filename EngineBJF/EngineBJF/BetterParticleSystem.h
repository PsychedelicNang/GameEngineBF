#pragma once
/***************************
* Filename: BetterParticleSystem.h
***************************/
#ifndef _BETTERPARTICLESYSTEM_H_
#define _BETTERPARTICLESYSTEM_H_

/***************************
* INCLUDES
***************************/
#include "IncludesBJF.h"
#include "WICTextureLoader.h"

class BetterParticleSystem {
public:
	BetterParticleSystem();
	~BetterParticleSystem();

	struct SimpleParticle
	{
		XMFLOAT3 m_position;
		XMFLOAT3 m_velocity;
		XMFLOAT4 m_color;
		XMFLOAT2 m_size;
		float m_age;
		float m_speed;
	};

	SimpleParticle* m_simpleParticles;

	struct RandomNumbers
	{
		RandomNumbers();
		XMFLOAT4* m_randomColors;
		XMFLOAT3* m_randomPositions;
		float*	  m_randomSpeed;
	};

	RandomNumbers* m_randomNumbers;
	unsigned numberOfRandomNumbers;

	bool Initialize(ComPtr<ID3D11Device>& _device, WCHAR* _fileName);
	bool LoadTexture(ComPtr<ID3D11Device>& _device, WCHAR*);
	bool InitializeParticleSystem();
	bool InitializeBuffers(ComPtr<ID3D11Device>& _device);

	/*Particle System Properties*/
	float m_particleDeviationX, m_particleDeviationY, m_particleDeviationZ;
	float m_particleVelocity, m_particleVelocityVariation;
	float m_particleSize, m_particlesPerSecond;
	int m_maxParticles;
	/*Particle System Properties*/

	int m_currentParticleCount;
	float m_accumulatedTime;
public:
	ComPtr<ID3D11ShaderResourceView> m_texture;
	ComPtr<ID3D11UnorderedAccessView> m_UAV;
	SimpleParticle* m_particleList;

	ComPtr<ID3D11Buffer>	m_particleSystemPropertiesConstantBuffer;

	struct ParticleSystemProperties {
		XMFLOAT3 m_initialPosition;
		XMFLOAT3 m_initialVelocity;
		float m_particleDeviationX, m_particleDeviationY, m_particleDeviationZ;
		float m_particleVelocity, m_particleVelocityVariation;
		float m_particleSize, m_particlesPerSecond;
		unsigned m_maxParticles;
		XMFLOAT2 padding;
	};
	ParticleSystemProperties m_particleSystemProperiesStruct;

	struct ParticleSystemDynamicProperties {
		XMFLOAT4X4 m_model;
		float m_deltaTime;
		XMFLOAT3 padding;
	};

	ParticleSystemDynamicProperties m_particleSystemDynamicProperties;
	ComPtr<ID3D11Buffer>	m_particleSystemDynamicPropertiesConstantBuffer;

	unsigned m_particleCount;
	ComPtr<ID3D11Buffer> m_structuredBuffer;
	ComPtr<ID3D11Buffer> m_indexBuffer;
	ComPtr<ID3D11Buffer> m_randomNumbersConstantBuffer;
};

#endif // !_BETTERPARTICLESYSTEM_H_