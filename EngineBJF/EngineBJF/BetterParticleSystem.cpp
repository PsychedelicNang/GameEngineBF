#include "BetterParticleSystem.h"

BetterParticleSystem::BetterParticleSystem()
{
	m_simpleParticles = 0;
	m_particleCount = 10000;
	m_randomNumbers = new RandomNumbers();
	numberOfRandomNumbers = 0;
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

	CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ParticleSystemProperties), D3D11_BIND_CONSTANT_BUFFER);
	result = _device->CreateBuffer(&constantBufferDesc, nullptr, m_particleSystemPropertiesConstantBuffer.GetAddressOf());

	CD3D11_BUFFER_DESC constantBufferDesc2(sizeof(XMFLOAT4) * numberOfRandomNumbers + sizeof(XMFLOAT3) * numberOfRandomNumbers + sizeof(float) * numberOfRandomNumbers, D3D11_BIND_CONSTANT_BUFFER);
	result = _device->CreateBuffer(&constantBufferDesc2, nullptr, m_randomNumbersConstantBuffer.GetAddressOf());

	CD3D11_BUFFER_DESC constantBufferDesc3(sizeof(ParticleSystemDynamicProperties), D3D11_BIND_CONSTANT_BUFFER);
	result = _device->CreateBuffer(&constantBufferDesc3, nullptr, m_particleSystemDynamicPropertiesConstantBuffer.GetAddressOf());

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

	// Initialize the particle list.
	m_simpleParticles = new SimpleParticle[m_particleCount];
	
	// Initialize the current particle count to zero since none are emitted yet.
	m_currentParticleCount = 0;

	// Clear the initial accumulated time for the particle per second emission rate.
	m_accumulatedTime = 0.0f;

	m_particleSystemProperiesStruct.m_particleDeviationX = 0.5f;
	m_particleSystemProperiesStruct.m_particleDeviationY = 0.1f;
	m_particleSystemProperiesStruct.m_particleDeviationZ = 2.0f;
	m_particleSystemProperiesStruct.m_particleVelocity = 5.0f;
	m_particleSystemProperiesStruct.m_particleVelocityVariation = 0.2f;
	m_particleSystemProperiesStruct.m_particleSize = 0.2f;
	m_particleSystemProperiesStruct.m_particlesPerSecond = 100.0f;
	m_particleSystemProperiesStruct.m_maxParticles = 10000;

	XMStoreFloat4x4(&m_particleSystemDynamicProperties.m_model, XMMatrixIdentity());
	m_particleSystemDynamicProperties.m_deltaTime = 0.f;

	numberOfRandomNumbers = 100;
	m_randomNumbers->m_randomColors = new XMFLOAT4[numberOfRandomNumbers];
	m_randomNumbers->m_randomPositions = new XMFLOAT3[numberOfRandomNumbers];
	m_randomNumbers->m_randomSpeed = new float[numberOfRandomNumbers];

	for (unsigned i = 0; i < m_particleCount; i++)
	{
		if (i < numberOfRandomNumbers)
		{
			m_randomNumbers->m_randomPositions[i].x = (((float)rand() - (float)rand()) / RAND_MAX) * m_particleDeviationX;
			m_randomNumbers->m_randomPositions[i].y = (((float)rand() - (float)rand()) / RAND_MAX) * m_particleDeviationY;
			m_randomNumbers->m_randomPositions[i].z = (((float)rand() - (float)rand()) / RAND_MAX) * m_particleDeviationZ;

			m_randomNumbers->m_randomSpeed[i] = m_particleVelocity + (((float)rand() - (float)rand()) / RAND_MAX) * m_particleVelocityVariation;

			m_randomNumbers->m_randomColors[i].x = (((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
			m_randomNumbers->m_randomColors[i].y = (((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
			m_randomNumbers->m_randomColors[i].z = (((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
			m_randomNumbers->m_randomColors[i].w = (((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
		}

		m_simpleParticles[i].m_age = 0.f;
		m_simpleParticles[i].m_position = m_randomNumbers->m_randomPositions[i % numberOfRandomNumbers];
		m_simpleParticles[i].m_color = m_randomNumbers->m_randomColors[i % numberOfRandomNumbers];
		m_simpleParticles[i].m_speed = m_randomNumbers->m_randomSpeed[i % numberOfRandomNumbers];
	}

	return true;
}

bool BetterParticleSystem::InitializeBuffers(ComPtr<ID3D11Device>& _device)
{
	D3D11_BUFFER_DESC particleBufferDesc;
	D3D11_SUBRESOURCE_DATA particleBufferData;
	HRESULT result;

	// Set up the description of the dynamic vertex buffer.
	ZeroMemory(&particleBufferDesc, sizeof(particleBufferDesc));
	particleBufferDesc.Usage = D3D11_USAGE_DEFAULT;
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

	D3D11_UNORDERED_ACCESS_VIEW_DESC UAVDesc;
	D3D11_BUFFER_UAV UAVBuffer;
	ZeroMemory(&UAVBuffer, sizeof(UAVBuffer));
	ZeroMemory(&UAVDesc, sizeof(UAVDesc));
	UAVBuffer.FirstElement = 0;
	UAVBuffer.NumElements = m_particleCount;

	UAVDesc.Format = DXGI_FORMAT_UNKNOWN;
	UAVDesc.Buffer = UAVBuffer;
	UAVDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;

	result = _device->CreateUnorderedAccessView(m_structuredBuffer.Get(), &UAVDesc, m_UAV.GetAddressOf());
	
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

BetterParticleSystem::RandomNumbers::RandomNumbers()
{
	m_randomColors = 0;
	m_randomPositions = 0;
	m_randomSpeed = 0;
}
