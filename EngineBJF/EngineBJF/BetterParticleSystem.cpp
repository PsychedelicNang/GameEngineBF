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

	unsigned size = (sizeof(XMFLOAT4) * numberOfRandomNumbers) + (sizeof(XMFLOAT3) * numberOfRandomNumbers) + (sizeof(float) * numberOfRandomNumbers);
	CD3D11_BUFFER_DESC constantBufferDesc2((sizeof(XMFLOAT4) * numberOfRandomNumbers) + (sizeof(XMFLOAT3) * numberOfRandomNumbers) + (sizeof(float) * numberOfRandomNumbers), D3D11_BIND_CONSTANT_BUFFER);
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

	m_particleSystemProperiesStruct.m_initialPosition = XMFLOAT3(0.0f, 5.0f, 0.0f);
	m_particleSystemProperiesStruct.m_initialVelocity = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_particleSystemProperiesStruct.m_particleDeviationX = 0.5f;
	m_particleSystemProperiesStruct.m_particleDeviationY = 0.1f;
	m_particleSystemProperiesStruct.m_particleDeviationZ = 2.0f;
	m_particleSystemProperiesStruct.m_particleVelocity = 5.0f;
	m_particleSystemProperiesStruct.m_particleVelocityVariation = 0.2f;
	m_particleSystemProperiesStruct.m_particleSize = 0.2f;
	m_particleSystemProperiesStruct.m_particlesPerSecond = 100.0f;
	m_particleSystemProperiesStruct.m_maxParticles = (unsigned)10000;

	XMStoreFloat4x4(&m_particleSystemDynamicProperties.m_model, XMMatrixIdentity());
	m_particleSystemDynamicProperties.m_deltaTime = 0.f;

	numberOfRandomNumbers = 100;
	m_randomNumbers->m_randomColors = new XMFLOAT4[numberOfRandomNumbers];
	m_randomNumbers->m_randomPositionsAndSpeed = new XMFLOAT4[numberOfRandomNumbers];

	XMFLOAT4 color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.f);
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
	for (unsigned i = 0; i < m_particleCount; i++)
	{
		if (i == 1)
		{
			// just to skip the first case..
		}
		else if (i % 100 == 1)
		{
			y += 1.f;
			x = 0.f;
		}
		else if (i % 200 == 1)
		{
			y += 1.f;
			x = 0.f;
		}
		else if (i % 300 == 1)
		{
			y += 1.f;
			x = 0.f;
		}
		else if (i % 400 == 1)
		{
			y += 1.f;
			x = 0.f;
		}
		else if (i % 500 == 1)
		{
			y += 1.f;
			x = 0.f;
		}
		else if (i % 600 == 1)
		{
			y += 1.f;
			x = 0.f;
		}
		else if (i % 700 == 1)
		{
			y += 1.f;
			x = 0.f;
		}
		else if (i % 800 == 1)
		{
			y += 1.f;
			x = 0.f;
		}
		else if (i % 900 == 1)
		{
			y += 1.f;
			x = 0.f;
		}
		x += .5f;
		//z += .5f;
		//color.x += 0.05;
		//color.y += 0.05;
		//color.z += 0.05;

		//if (color.x >= 1.f)
		//{
		//	color.x = 0.0f;
		//	color.y = 0.0f;
		//	color.z = 0.0f;
		//}
		//if (i < numberOfRandomNumbers)
		//{
		//	m_randomNumbers->m_randomPositionsAndSpeed[i].x = (((float)rand() - (float)rand()) / RAND_MAX) * m_particleDeviationX;
		//	m_randomNumbers->m_randomPositionsAndSpeed[i].y = (((float)rand() - (float)rand()) / RAND_MAX) * m_particleDeviationY;
		//	m_randomNumbers->m_randomPositionsAndSpeed[i].z = (((float)rand() - (float)rand()) / RAND_MAX) * m_particleDeviationZ;
		//	m_randomNumbers->m_randomPositionsAndSpeed[i].w = m_particleVelocity + (((float)rand() - (float)rand()) / RAND_MAX) * m_particleVelocityVariation;

		//	m_randomNumbers->m_randomColors[i].x = (((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
		//	m_randomNumbers->m_randomColors[i].y = (((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
		//	m_randomNumbers->m_randomColors[i].z = (((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
		//	m_randomNumbers->m_randomColors[i].w = (((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
		//}

		//m_simpleParticles[i].m_age = 0.f;
		//m_simpleParticles[i].m_position.x = m_randomNumbers->m_randomPositionsAndSpeed[i % numberOfRandomNumbers].x;
		//m_simpleParticles[i].m_position.y = m_randomNumbers->m_randomPositionsAndSpeed[i % numberOfRandomNumbers].y;
		//m_simpleParticles[i].m_position.z = m_randomNumbers->m_randomPositionsAndSpeed[i % numberOfRandomNumbers].z;
		//m_simpleParticles[i].m_color = m_randomNumbers->m_randomColors[i % numberOfRandomNumbers];
		//m_simpleParticles[i].m_speed = m_randomNumbers->m_randomPositionsAndSpeed[i % numberOfRandomNumbers].w;
		m_simpleParticles[i].m_position.x = x;
		m_simpleParticles[i].m_position.y = y;
		m_simpleParticles[i].m_position.z = z;
		m_simpleParticles[i].m_position.w = 1.f;
		m_simpleParticles[i].m_color = color;
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
	particleBufferDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
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

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	D3D11_BUFFER_SRV srvBuffer;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	ZeroMemory(&srvBuffer, sizeof(srvBuffer));
	srvBuffer.FirstElement = 0;
	srvBuffer.NumElements = m_particleCount;

	srvDesc.Buffer = srvBuffer;
	srvDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;

	result = _device->CreateShaderResourceView(m_structuredBuffer.Get(), &srvDesc, m_shaderResourceView.GetAddressOf());
	
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

BetterParticleSystem::RandomNumbers::RandomNumbers()
{
	m_randomColors = 0;
	m_randomPositionsAndSpeed = 0;
}

BetterParticleSystem::RandomNumbers::~RandomNumbers()
{
	delete[] m_randomColors;
	delete[] m_randomPositionsAndSpeed;
}

BetterParticleSystem::SimpleParticle::SimpleParticle()
{
	m_position = XMFLOAT4(0.f, 0.f, 0.f, 1.f);
	m_color = XMFLOAT4(0.f, 0.f, 0.f, 1.f);
}
