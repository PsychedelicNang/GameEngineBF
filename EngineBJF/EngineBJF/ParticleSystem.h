#pragma once
/***************************
* Filename: ParticleSystem.h
***************************/
#ifndef _PARTICLESYSTEM_H_
#define _PARTICLESYSTEM_H_

/***************************
* INCLUDES
***************************/
#include "IncludesBJF.h"
#include "WICTextureLoader.h"

class ParticleSystem {
public:
	ParticleSystem();
	~ParticleSystem();

private:
	struct Particle{
		float positionX, positionY, positionZ;
		float red, green, blue;
		float velocity;
		bool active;
	};

	struct VertexParticle {
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 uv;
		DirectX::XMFLOAT4 color;
	};

public:
	bool Initialize(ComPtr<ID3D11Device>& _device, WCHAR* _fileName);
	void Shutdown();
	bool UpdateFrame(float _deltaTime, ComPtr<ID3D11DeviceContext>& _deviceContext);
	void Render(ComPtr<ID3D11DeviceContext>& _deviceContext);

	ComPtr<ID3D11ShaderResourceView>& GetTexture();
	int GetIndexCount();

private:
	bool LoadTexture(ComPtr<ID3D11Device>& _device, WCHAR*);
	void ReleaseTexture();

	bool InitializeParticleSystem();
	void ShutdownParticleSystem();

	bool InitializeBuffers(ComPtr<ID3D11Device>& _device);
	void ShutdownBuffers();

	void EmitParticles(float _deltaTime);
	void UpdateParticles(float _deltaTime);
	void DestroyParticles();

	bool UpdateBuffers(ComPtr<ID3D11DeviceContext>& _deviceContext);

	void RenderBuffers(ComPtr<ID3D11DeviceContext>& _deviceContext);

	/*Particle System Properties*/
	float m_particleDeviationX, m_particleDeviationY, m_particleDeviationZ;
	float m_particleVelocity, m_particleVelocityVariation;
	float m_particleSize, m_particlesPerSecond;
	int m_maxParticles;
	/*Particle System Properties*/

	int m_currentParticleCount;
	float m_accumulatedTime;

	ComPtr<ID3D11ShaderResourceView> m_texture;
	Particle* m_particleList;

	int m_vertexCount, m_indexCount;
	VertexParticle* m_vertices;
	ComPtr<ID3D11Buffer> m_vertexBuffer;
	ComPtr<ID3D11Buffer> m_indexBuffer;
};

#endif // !_PARTICLESYSTEM_H_