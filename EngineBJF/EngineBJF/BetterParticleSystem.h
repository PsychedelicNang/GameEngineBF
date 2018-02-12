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
		XMFLOAT3 m_initialPosition;
		XMFLOAT3 m_initialVelocity;
		XMFLOAT2 m_size;
		float m_age;
		unsigned int m_type;
	};

	SimpleParticle* m_simpleParticles;

	bool Initialize(ComPtr<ID3D11Device>& _device, WCHAR* _fileName);
	bool LoadTexture(ComPtr<ID3D11Device>& _device, WCHAR*);
	bool InitializeParticleSystem();
	bool InitializeBuffers(ComPtr<ID3D11Device>& _device);
	bool InitializeUAV(ComPtr<ID3D11Device>& _device);


	/*Particle System Properties*/
	float m_particleDeviationX, m_particleDeviationY, m_particleDeviationZ;
	float m_particleVelocity, m_particleVelocityVariation;
	float m_particleSize, m_particlesPerSecond;
	int m_maxParticles;
	/*Particle System Properties*/

	int m_currentParticleCount;
	float m_accumulatedTime;

	ComPtr<ID3D11ShaderResourceView> m_texture;
	ComPtr<ID3D11UnorderedAccessView> m_UAV;
	SimpleParticle* m_particleList;

	unsigned m_particleCount;
	ComPtr<ID3D11Buffer> m_structuredBuffer;
	ComPtr<ID3D11Buffer> m_indexBuffer;
};

#endif // !_BETTERPARTICLESYSTEM_H_