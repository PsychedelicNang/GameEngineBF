#include "Object.h"
Object::Object()
{
	m_vertexBuffer = nullptr;
	m_indexBuffer = nullptr;
	m_indexCount = 0;
	m_vertexCount = 0;
	m_stride = 0;
	m_matrix = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
	m_texture = nullptr;
	m_shaderResourceView = nullptr;
}

Object::~Object()
{
	Shutdown();
}

bool Object::Initialize(ComPtr<ID3D11Device>& _device)
{
	if (!InitializeBuffers(_device)) return false;

	return true;
}

bool Object::Initialize(ComPtr<ID3D11Device>& _device, XMFLOAT4X4 _matrix)
{
	if (!InitializeBuffers(_device, _matrix)) return false;

	return true;
}

void Object::Shutdown()
{
	ShutdownBuffers();
	ShutdownTextures();
}

void Object::Render(ComPtr<ID3D11DeviceContext>& _deviceContext)
{
	RenderBuffers(_deviceContext);
}

int Object::GetIndexCount()
{
	return m_indexCount;
}

XMFLOAT4X4 Object::GetObjectFloat4x4()
{
	return m_matrix;
}

XMMATRIX Object::GetObjectMatrix()
{
	return XMLoadFloat4x4(&m_matrix);
}

void Object::ObjectTranslation(XMVECTOR _traslationAmount)
{
	XMStoreFloat4x4(&m_matrix, XMMatrixMultiply(XMLoadFloat4x4(&m_matrix), XMMatrixTranslationFromVector(_traslationAmount)));
}

void Object::ObjectTranslationX(float _xDelta)
{
	XMStoreFloat4x4(&m_matrix, XMMatrixMultiply(XMLoadFloat4x4(&m_matrix), XMMatrixTranslation(_xDelta, 0.f, 0.f)));
}

void Object::ObjectTranslationY(float _yDelta)
{
	XMStoreFloat4x4(&m_matrix, XMMatrixMultiply(XMLoadFloat4x4(&m_matrix), XMMatrixTranslation(0.f, _yDelta, 0.f)));
}

void Object::ObjectTranslationZ(float _zDelta)
{
	XMStoreFloat4x4(&m_matrix, XMMatrixMultiply(XMLoadFloat4x4(&m_matrix), XMMatrixTranslation(0.f, 0.f, _zDelta)));
}

void Object::ObjectTranslation(float _xDelta, float _yDelta, float _zDelta)
{
	XMStoreFloat4x4(&m_matrix, XMMatrixMultiply(XMLoadFloat4x4(&m_matrix), XMMatrixTranslation(_xDelta, _yDelta, _zDelta)));
}

void Object::ObjectChangePosition(float _newXPosition, float _newYPosition, float _newZPosition)
{
	m_matrix = XMFLOAT4X4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
		_newXPosition, _newYPosition, _newZPosition, 1);
}

void Object::ObjectRotationX(float _radians)
{
	XMStoreFloat4x4(&m_matrix, XMMatrixMultiply(XMMatrixRotationX(_radians), XMLoadFloat4x4(&m_matrix)));
}

void Object::ObjectRotationY(float _radians)
{
	XMStoreFloat4x4(&m_matrix, XMMatrixMultiply(XMMatrixRotationY(_radians), XMLoadFloat4x4(&m_matrix)));
}

void Object::ObjectRotationZ(float _radians)
{
	XMStoreFloat4x4(&m_matrix, XMMatrixMultiply(XMMatrixRotationZ(_radians), XMLoadFloat4x4(&m_matrix)));
}

bool Object::ReadInMeshFromBinaryFile(ComPtr<ID3D11Device>& _device, const char * _fileName)
{
	if (!ReadInBinaryMeshFile(_device, _fileName)) return false;

	return true;
}

bool Object::ReadInAdvancedMeshFromBinaryFile(ComPtr<ID3D11Device>& _device, const char * _fileName)
{
	if (!ReadInAdvancedBinaryMeshFile(_device, _fileName)) return false;

	return true;
}

bool Object::InitializeBuffers(ComPtr<ID3D11Device>& _device)
{
#if 0
	HRESULT result;

	// Load mesh vertices. Each vertex has a position and a color.
	VertexPositionColor cubeVertices[] =
	{
		{ XMFLOAT4(-1.0f, 1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 0.f, 0.f) },
		{ XMFLOAT4(1.0f,  1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 0.f, 0.f) },
		{ XMFLOAT4(1.0f,  1.0f,  1.0f, 1.0f)  , XMFLOAT4(0.f, 1.f, 0.f, 0.f) },
		{ XMFLOAT4(-1.0f,  1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 1.f, 0.f, 0.f) },
		{ XMFLOAT4(-1.0f, -1.0f, -1.0f, 1.0f) , XMFLOAT4(0.f, 0.f, 1.f, 0.f) },
		{ XMFLOAT4(1.0f, -1.0f, -1.0f, 1.0f)  , XMFLOAT4(0.f, 0.f, 1.f, 0.f) },
		{ XMFLOAT4(1.0f, -1.0f,  1.0f, 1.0f)  , XMFLOAT4(0.f, 0.f, 0.f, 1.f) },
		{ XMFLOAT4(-1.0f, -1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 0.f, 0.f, 1.f) },
	};

	//	-X / +X : Cyan / Red
	//	 - Y / +Y : Magenta / Green
	// - Z / +Z : Yellow / Blue

	D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
	vertexBufferData.pSysMem = cubeVertices;
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(cubeVertices), D3D11_BIND_VERTEX_BUFFER);
	result = _device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, m_vertexBuffer.GetAddressOf());
	if (FAILED(result))
	{
		return false;
	}

	static const unsigned cubeIndices[] =
	{
		3, 1, 0,
		2, 1, 3,

		0, 5, 4,
		1, 5, 0,

		3, 4, 7,
		0, 4, 3,

		1, 6, 5,
		2, 6, 1,

		2, 7, 6,
		3, 7, 2,

		6, 4, 5,
		7, 4, 6,
	};

	m_indexCount = ARRAYSIZE(cubeIndices);

	D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
	indexBufferData.pSysMem = cubeIndices;
	indexBufferData.SysMemPitch = 0;
	indexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC indexBufferDesc(sizeof(cubeIndices), D3D11_BIND_INDEX_BUFFER);
	result = _device->CreateBuffer(&indexBufferDesc, &indexBufferData, m_indexBuffer.GetAddressOf());
	if (FAILED(result))
	{
		return false;
	}

	m_matrix = DirectX::XMFLOAT4X4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	m_stride = sizeof(VertexPositionColor);
	m_hasIndexBuffer = true;

	return true;
#endif

#if 1
	HRESULT result;

	VertexPositionColorUVNormal cubeVertices[] =
	{
		//3, 1, 0,
		{ XMFLOAT4(-1.0f,  1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 1.f, 0.f, 1.f), XMFLOAT4(0.f, 0.f, 0.f, 0.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f) },
		{ XMFLOAT4(1.0f,  1.0f, -1.0f, 1.0f)  , XMFLOAT4(0.f, 1.f, 0.f, 1.f), XMFLOAT4(1.f, 1.f, 0.f, 0.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f) },
		{ XMFLOAT4(-1.0f, 1.0f, -1.0f, 1.0f)  , XMFLOAT4(0.f, 1.f, 0.f, 1.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f) },
		//2, 1, 3,
		{ XMFLOAT4(1.0f,  1.0f,  1.0f, 1.0f)  , XMFLOAT4(0.f, 1.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f) },
		{ XMFLOAT4(1.0f,  1.0f, -1.0f, 1.0f)  , XMFLOAT4(0.f, 1.f, 0.f, 1.f), XMFLOAT4(1.f, 1.f, 0.f, 0.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f) },
		{ XMFLOAT4(-1.0f,  1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 1.f, 0.f, 1.f), XMFLOAT4(0.f, 0.f, 0.f, 0.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f) },
		//0, 5, 4,
		{ XMFLOAT4(-1.0f, 1.0f, -1.0f, 1.0f) , XMFLOAT4(1.f, 0.f, 1.f, 1.f), XMFLOAT4(0.f, 0.f, 0.f, 0.f), XMFLOAT4(0.f, 0.f, -1.f, 0.f) },
		{ XMFLOAT4(1.0f, -1.0f, -1.0f, 1.0f) , XMFLOAT4(1.f, 0.f, 1.f, 1.f), XMFLOAT4(1.f, 1.f, 0.f, 0.f), XMFLOAT4(0.f, 0.f, -1.f, 0.f) },
		{ XMFLOAT4(-1.0f, -1.0f, -1.0f, 1.0f), XMFLOAT4(1.f, 0.f, 1.f, 1.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f), XMFLOAT4(0.f, 0.f, -1.f, 0.f) },
		//1, 5, 0,
		{ XMFLOAT4(1.0f,  1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 1.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f), XMFLOAT4(0.f, 0.f, -1.f, 0.f) },
		{ XMFLOAT4(1.0f, -1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 1.f, 1.f), XMFLOAT4(1.f, 1.f, 0.f, 0.f), XMFLOAT4(0.f, 0.f, -1.f, 0.f) },
		{ XMFLOAT4(-1.0f, 1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 1.f, 1.f), XMFLOAT4(0.f, 0.f, 0.f, 0.f), XMFLOAT4(0.f, 0.f, -1.f, 0.f) },
		//3, 4, 7,
		{ XMFLOAT4(-1.0f,  1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 1.f, 1.f, 1.f), XMFLOAT4(0.f, 0.f, 0.f, 0.f), XMFLOAT4(-1.f, 0.f, 0.f, 0.f) },
		{ XMFLOAT4(-1.0f, -1.0f, -1.0f, 1.0f) , XMFLOAT4(0.f, 1.f, 1.f, 1.f), XMFLOAT4(1.f, 1.f, 0.f, 0.f), XMFLOAT4(-1.f, 0.f, 0.f, 0.f) },
		{ XMFLOAT4(-1.0f, -1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 1.f, 1.f, 1.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f), XMFLOAT4(-1.f, 0.f, 0.f, 0.f) },
		//0, 4, 3,
		{ XMFLOAT4(-1.0f, 1.0f, -1.0f, 1.0f)  , XMFLOAT4(0.f, 1.f, 1.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f), XMFLOAT4(-1.f, 0.f, 0.f, 0.f) },
		{ XMFLOAT4(-1.0f, -1.0f, -1.0f, 1.0f) , XMFLOAT4(0.f, 1.f, 1.f, 1.f), XMFLOAT4(1.f, 1.f, 0.f, 0.f), XMFLOAT4(-1.f, 0.f, 0.f, 0.f) },
		{ XMFLOAT4(-1.0f,  1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 1.f, 1.f, 1.f), XMFLOAT4(0.f, 0.f, 0.f, 0.f), XMFLOAT4(-1.f, 0.f, 0.f, 0.f) },
		//1, 6, 5,
		{ XMFLOAT4(1.0f,  1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 0.f, 1.f), XMFLOAT4(0.f, 0.f, 0.f, 0.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) },
		{ XMFLOAT4(1.0f, -1.0f,  1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 1.f, 0.f, 0.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) },
		{ XMFLOAT4(1.0f, -1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 0.f, 1.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) },
		//2, 6, 1,
		{ XMFLOAT4(1.0f,  1.0f,  1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) },
		{ XMFLOAT4(1.0f, -1.0f,  1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 1.f, 0.f, 0.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) },
		{ XMFLOAT4(1.0f,  1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 0.f, 1.f), XMFLOAT4(0.f, 0.f, 0.f, 0.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) },
		//2, 7, 6,
		{ XMFLOAT4(1.0f,  1.0f,  1.0f, 1.0f)  , XMFLOAT4(0.f, 0.f, 1.f, 1.f), XMFLOAT4(0.f, 0.f, 0.f, 0.f), XMFLOAT4(0.f, 0.f, 1.f, 0.f) },
		{ XMFLOAT4(-1.0f, -1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 0.f, 1.f, 1.f), XMFLOAT4(1.f, 1.f, 0.f, 0.f), XMFLOAT4(0.f, 0.f, 1.f, 0.f) },
		{ XMFLOAT4(1.0f, -1.0f,  1.0f, 1.0f)  , XMFLOAT4(0.f, 0.f, 1.f, 1.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f), XMFLOAT4(0.f, 0.f, 1.f, 0.f) },
		//3, 7, 2,
		{ XMFLOAT4(-1.0f,  1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 0.f, 1.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f), XMFLOAT4(0.f, 0.f, 1.f, 0.f) },
		{ XMFLOAT4(-1.0f, -1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 0.f, 1.f, 1.f), XMFLOAT4(1.f, 1.f, 0.f, 0.f), XMFLOAT4(0.f, 0.f, 1.f, 0.f) },
		{ XMFLOAT4(1.0f,  1.0f,  1.0f, 1.0f)  , XMFLOAT4(0.f, 0.f, 1.f, 1.f), XMFLOAT4(0.f, 0.f, 0.f, 0.f), XMFLOAT4(0.f, 0.f, 1.f, 0.f) },
		//6, 4, 5,
		{ XMFLOAT4(1.0f, -1.0f,  1.0f, 1.0f)  , XMFLOAT4(1.f, 1.f, 0.f, 1.f), XMFLOAT4(0.f, 0.f, 0.f, 0.f), XMFLOAT4(0.f, -1.f, 0.f, 0.f) },
		{ XMFLOAT4(-1.0f, -1.0f, -1.0f, 1.0f) , XMFLOAT4(1.f, 1.f, 0.f, 1.f), XMFLOAT4(1.f, 1.f, 0.f, 0.f), XMFLOAT4(0.f, -1.f, 0.f, 0.f) },
		{ XMFLOAT4(1.0f, -1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 1.f, 0.f, 1.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f), XMFLOAT4(0.f, -1.f, 0.f, 0.f) },
		//7, 4, 6,
		{ XMFLOAT4(-1.0f, -1.0f,  1.0f, 1.0f) , XMFLOAT4(1.f, 1.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f), XMFLOAT4(0.f, -1.f, 0.f, 0.f) },
		{ XMFLOAT4(-1.0f, -1.0f, -1.0f, 1.0f) , XMFLOAT4(1.f, 1.f, 0.f, 1.f), XMFLOAT4(1.f, 1.f, 0.f, 0.f), XMFLOAT4(0.f, -1.f, 0.f, 0.f) },
		{ XMFLOAT4(1.0f, -1.0f,  1.0f, 1.0f)  , XMFLOAT4(1.f, 1.f, 0.f, 1.f), XMFLOAT4(0.f, 0.f, 0.f, 0.f), XMFLOAT4(0.f, -1.f, 0.f, 0.f) }
	};

	m_vertexCount = ARRAYSIZE(cubeVertices);

	D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
	vertexBufferData.pSysMem = cubeVertices;
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(cubeVertices), D3D11_BIND_VERTEX_BUFFER);
	result = _device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, m_vertexBuffer.GetAddressOf());
	if (FAILED(result))
	{
		return false;
	}

	static const unsigned cubeIndices[] =
	{
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		9, 10, 11,
		12, 13, 14,
		15, 16, 17,
		18, 19, 20,
		21, 22, 23,
		24, 25, 26,
		27, 28, 29,
		30, 31, 32,
		33, 34, 35
	};
	
	m_indexCount = ARRAYSIZE(cubeIndices);
	
	D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
	indexBufferData.pSysMem = cubeIndices;
	indexBufferData.SysMemPitch = 0;
	indexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC indexBufferDesc(sizeof(cubeIndices), D3D11_BIND_INDEX_BUFFER);
	result = _device->CreateBuffer(&indexBufferDesc, &indexBufferData, m_indexBuffer.GetAddressOf());
	if (FAILED(result))
	{
		return false;
	}

	m_matrix = DirectX::XMFLOAT4X4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		3, 0, -5, 1);

	m_stride = sizeof(VertexPositionColorUVNormal);

	return true;
#endif
}


bool Object::InitializeBuffers(ComPtr<ID3D11Device>& _device, XMFLOAT4X4 _matrix)
{
	HRESULT result;
	// Load mesh vertices. Each vertex has a position and a color.
	VertexPositionColor cubeVertices[] =
	{
		{ XMFLOAT4(-1.0f, 1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 0.f, 0.f) },
		{ XMFLOAT4(1.0f,  1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 0.f, 0.f) },
		{ XMFLOAT4(1.0f,  1.0f,  1.0f, 1.0f)  , XMFLOAT4(0.f, 1.f, 0.f, 0.f) },
		{ XMFLOAT4(-1.0f,  1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 1.f, 0.f, 0.f) },
		{ XMFLOAT4(-1.0f, -1.0f, -1.0f, 1.0f) , XMFLOAT4(0.f, 0.f, 1.f, 0.f) },
		{ XMFLOAT4(1.0f, -1.0f, -1.0f, 1.0f)  , XMFLOAT4(0.f, 0.f, 1.f, 0.f) },
		{ XMFLOAT4(1.0f, -1.0f,  1.0f, 1.0f)  , XMFLOAT4(0.f, 0.f, 0.f, 1.f) },
		{ XMFLOAT4(-1.0f, -1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 0.f, 0.f, 1.f) },
	};

	//	-X / +X : Cyan / Red
	//	 - Y / +Y : Magenta / Green
	// - Z / +Z : Yellow / Blue

	D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
	vertexBufferData.pSysMem = cubeVertices;
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(cubeVertices), D3D11_BIND_VERTEX_BUFFER);
	result = _device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, m_vertexBuffer.GetAddressOf());
	if (result != S_OK) return false;

	static const unsigned cubeIndices[] =
	{
		3, 1, 0,
		2, 1, 3,

		0, 5, 4,
		1, 5, 0,

		3, 4, 7,
		0, 4, 3,

		1, 6, 5,
		2, 6, 1,

		2, 7, 6,
		3, 7, 2,

		6, 4, 5,
		7, 4, 6,
	};

	D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
	indexBufferData.pSysMem = cubeIndices;
	indexBufferData.SysMemPitch = 0;
	indexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC indexBufferDesc(sizeof(cubeIndices), D3D11_BIND_INDEX_BUFFER);
	result = _device->CreateBuffer(&indexBufferDesc, &indexBufferData, m_indexBuffer.GetAddressOf());
	if (result != S_OK) return false;

	m_matrix = _matrix;

	return true;
}

// Reads in a binary mesh file containing vertex and index position data and fills out the object of which this function was called from
bool Object::ReadInBinaryMeshFile(ComPtr<ID3D11Device>& _device, const char * _fileName)
{
	std::fstream file;
	file.open(_fileName, std::ios_base::binary | std::ios_base::in);
	
	if (file.is_open())
	{
		unsigned numOfIndices;
		unsigned numOfVertices;
	
		file.read((char*)&numOfIndices, 4);
	
		unsigned* indices = new unsigned[numOfIndices];
	
		m_indexCount = numOfIndices;
	
		for (unsigned i = 0; i < numOfIndices; i++)
			file.read((char*)(&indices[i]), sizeof(4));
	
		D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
		indexBufferData.pSysMem = indices;
		indexBufferData.SysMemPitch = 0;
		indexBufferData.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC indexBufferDesc(sizeof(unsigned) * numOfIndices, D3D11_BIND_INDEX_BUFFER);
		_device->CreateBuffer(&indexBufferDesc, &indexBufferData, m_indexBuffer.GetAddressOf());
	
		delete[] indices;
	
		file.read((char*)&numOfVertices, 4);
	
		VertexPositionColor* vertices = new VertexPositionColor[numOfVertices];
	
		for (unsigned i = 0; i < numOfVertices; i++)
		{
			file.read((char*)(&vertices[i].position.x), sizeof(4));
			file.read((char*)(&vertices[i].position.y), sizeof(4));
			file.read((char*)(&vertices[i].position.z), sizeof(4));
			file.read((char*)(&vertices[i].position.w), sizeof(4));
			//vertices[i].color = XMFLOAT4(1.f, 1.f, 1.f, 1.f);
			vertices[i].color = XMFLOAT4(((float)i) / numOfVertices, ((float)i) / numOfVertices, ((float)i) / numOfVertices, 1.f);
		}
	
		for (unsigned i = 0; i < numOfVertices; i++)
			vertices[i].position.w = 1.f;
	
		D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
		vertexBufferData.pSysMem = vertices;
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(VertexPositionColor) * numOfVertices, D3D11_BIND_VERTEX_BUFFER);
		_device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, m_vertexBuffer.GetAddressOf());
	
		m_matrix = DirectX::XMFLOAT4X4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
		m_indexCount = numOfIndices;
		m_vertexCount = numOfVertices;
		m_stride = sizeof(VertexPositionColor);

		delete[] vertices;
	
		file.close();
		return true;
	}
	return false;
}

// Reads in a binary mesh file containing vertex and index Position, UV, and Normal data and fills out the object of which this function was called from
bool Object::ReadInAdvancedBinaryMeshFile(ComPtr<ID3D11Device>& _device, const char * _fileName)
{
		std::fstream file;
		file.open(_fileName, std::ios_base::binary | std::ios_base::in);
	
		if (file.is_open())
		{
			unsigned numOfIndices;
			unsigned numOfVertices;
	
			file.read((char*)&numOfIndices, 4);
	
			unsigned* indices = new unsigned[numOfIndices];
	
			m_indexCount = numOfIndices;
	
			for (unsigned i = 0; i < numOfIndices; i++)
				file.read((char*)(&indices[i]), sizeof(4));
	
			D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
			indexBufferData.pSysMem = indices;
			indexBufferData.SysMemPitch = 0;
			indexBufferData.SysMemSlicePitch = 0;
			CD3D11_BUFFER_DESC indexBufferDesc(sizeof(unsigned) * numOfIndices, D3D11_BIND_INDEX_BUFFER);
			_device->CreateBuffer(&indexBufferDesc, &indexBufferData, m_indexBuffer.GetAddressOf());
	
			delete[] indices;
	
			file.read((char*)&numOfVertices, 4);
	
			VertexPositionColorUVNormal* vertices = new VertexPositionColorUVNormal[numOfVertices];
	
			for (unsigned i = 0; i < numOfVertices; i++)
			{
				file.read((char*)(&vertices[i].position.x), sizeof(4));
				file.read((char*)(&vertices[i].position.y), sizeof(4));
				file.read((char*)(&vertices[i].position.z), sizeof(4));
				file.read((char*)(&vertices[i].position.w), sizeof(4));
				//vertices[i].color = XMFLOAT4(.5f, 1.f, 1.f, 1.f);
				vertices[i].color = XMFLOAT4(((float)i) / numOfVertices, ((float)i) / numOfVertices, ((float)i) / numOfVertices, 1.f);
				
				file.read((char*)(&vertices[i].normal.x), sizeof(4));
				file.read((char*)(&vertices[i].normal.y), sizeof(4));
				file.read((char*)(&vertices[i].normal.z), sizeof(4));
				file.read((char*)(&vertices[i].normal.w), sizeof(4));
	
				file.read((char*)(&vertices[i].uv.x), sizeof(4));
				file.read((char*)(&vertices[i].uv.y), sizeof(4));

				/*************************************************/
				/*	Subtract the V value from 1 due to
				*	Because FBX models are created in a
				*	Right handed coordinate system
				*	and I'm using a Left handed cooridnate system
				*/
				vertices[i].uv.y = 1 - vertices[i].uv.y;
				/*************************************************/

				vertices[i].uv.z = 0.f;
				vertices[i].uv.w = 0.f;
			}
	
			for (unsigned i = 0; i < numOfVertices; i++)
				vertices[i].position.w = 1.f;

			for (size_t i = 0; i < numOfVertices; i++)
			{
				vertices[i].position.x *= 0.02f;
				vertices[i].position.y *= 0.02f;
				vertices[i].position.z *= 0.02f;
			}
	
			D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
			vertexBufferData.pSysMem = vertices;
			vertexBufferData.SysMemPitch = 0;
			vertexBufferData.SysMemSlicePitch = 0;
			CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(VertexPositionColorUVNormal) * numOfVertices, D3D11_BIND_VERTEX_BUFFER);
			_device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, m_vertexBuffer.GetAddressOf());
	
			m_matrix = DirectX::XMFLOAT4X4(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);

			m_indexCount = numOfIndices;
			m_vertexCount = numOfVertices;
			m_stride = sizeof(VertexPositionColorUVNormal);
	
			delete[] vertices;
	
			file.close();
			return true;
		}
		return false;
}

void Object::ShutdownBuffers()
{
	m_vertexBuffer.Reset();
	m_indexBuffer.Reset();
	m_indexCount = 0;
	m_stride = 0;
	m_matrix = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
}

void Object::ShutdownTextures()
{
	m_texture.Reset();
	m_shaderResourceView.Reset();
}

void Object::RenderBuffers(ComPtr<ID3D11DeviceContext>& _deviceContext)
{
	unsigned int offset = 0;
	unsigned int stride = m_stride;

	_deviceContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
	_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	if (m_indexBuffer)
	{
		_deviceContext->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		_deviceContext->DrawIndexed(m_indexCount, 0, 0);
	}
	else _deviceContext->Draw(m_vertexCount, 0);
}