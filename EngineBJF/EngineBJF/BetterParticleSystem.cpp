#include "BetterParticleSystem.h"

BetterParticleSystem::BetterParticleSystem()
{
	m_simpleParticles = 0;
	m_particleCount = 1024;
}

BetterParticleSystem::~BetterParticleSystem()
{
	delete[] m_simpleParticles;
}

bool BetterParticleSystem::Initialize(ComPtr<ID3D11Device>& _device, WCHAR * _fileName)
{
	// Load the texture that is used for the particles in this system.
	bool result = LoadTexture(_device, _fileName);

	if (!result)
	{
		return false;
	}

	// Initialize the particle system.
	result = InitializeParticleSystem();
	if (!result)
	{
		return false;
	}

	// Create the buffers that will be used to render the particles with.
	result = InitializeBuffers(_device);
	if (!result)
	{
		return false;
	}

	return true;
}

bool BetterParticleSystem::LoadTexture(ComPtr<ID3D11Device>& _device, WCHAR * _fileName)
{
	HRESULT result = CreateWICTextureFromFile(_device.Get(), nullptr, _fileName, nullptr, m_texture.GetAddressOf(), 0);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool BetterParticleSystem::InitializeParticleSystem()
{
	// Set the random deviation of where the particles can be located when emitted.
	m_particleDeviationX = 0.5f;
	m_particleDeviationY = 0.1f;
	m_particleDeviationZ = 2.0f;

	// Set the speed and speed variation of particles.
	m_particleVelocity = 5.0f;
	m_particleVelocityVariation = 0.2f;

	// Set the physical size of the particles.
	m_particleSize = 0.2f;

	// Set the number of particles to emit per second.
	m_particlesPerSecond = 30.0f;

	// Set the maximum number of particles allowed in the particle system.
	m_maxParticles = 5000;

	// Create the particle list.
	if (!m_particleList)
	{
		return false;
	}

	// Initialize the particle list.
	m_simpleParticles = new SimpleParticle[m_particleCount];
	
	// Initialize the current particle count to zero since none are emitted yet.
	m_currentParticleCount = 0;

	// Clear the initial accumulated time for the particle per second emission rate.
	m_accumulatedTime = 0.0f;

	return true;
}

bool BetterParticleSystem::InitializeBuffers(ComPtr<ID3D11Device>& _device)
{
	D3D11_BUFFER_DESC particleBufferDesc;
	D3D11_SUBRESOURCE_DATA particleBufferData;
	HRESULT result;

	// Set up the description of the dynamic vertex buffer.
	particleBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	particleBufferDesc.ByteWidth = sizeof(SimpleParticle) * m_particleCount;
	particleBufferDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS;
	particleBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
	particleBufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	particleBufferDesc.StructureByteStride = sizeof(SimpleParticle);

	// Give the subresource structure a pointer to the vertex data.
	particleBufferData.pSysMem = m_simpleParticles;
	particleBufferData.SysMemPitch = 0;
	particleBufferData.SysMemSlicePitch = 0;

	// Now finally create the vertex buffer.
	result = _device->CreateBuffer(&particleBufferDesc, &particleBufferData, m_structuredBuffer.GetAddressOf());
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool BetterParticleSystem::InitializeUAV(ComPtr<ID3D11Device>& _device)
{
	D3D11_UNORDERED_ACCESS_VIEW_DESC UAVDesc;
	UAVDesc.Format = DXGI_FORMAT_UNKNOWN;
	return false;
}
