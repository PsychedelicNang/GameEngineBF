#include "Object.h"
Object::Object()
{
	ComPtr<ID3D11Buffer>	m_vertexBuffer = nullptr;
	ComPtr<ID3D11Buffer>	m_indexBuffer = nullptr;
	int						m_indexCount = 0;
	m_matrix = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
	ComPtr<ID3D11Texture2D>				m_texture = nullptr;
	ComPtr<ID3D11ShaderResourceView>	m_shaderResourceView = nullptr;
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

void Object::ObjectTranslation(Object& _name, XMVECTOR _traslationAmount)
{
	XMStoreFloat4x4(&_name.m_matrix, XMMatrixMultiply(XMLoadFloat4x4(&_name.m_matrix), XMMatrixTranslationFromVector(_traslationAmount)));
}

void Object::ObjectTranslationX(Object& _name, float _xDelta)
{
	XMStoreFloat4x4(&_name.m_matrix, XMMatrixMultiply(XMLoadFloat4x4(&_name.m_matrix), XMMatrixTranslation(_xDelta, 0.f, 0.f)));
}

void Object::ObjectTranslationY(Object& _name, float _yDelta)
{
	XMStoreFloat4x4(&_name.m_matrix, XMMatrixMultiply(XMLoadFloat4x4(&_name.m_matrix), XMMatrixTranslation(0.f, _yDelta, 0.f)));
}

void Object::ObjectTranslationZ(Object& _name, float _zDelta)
{
	XMStoreFloat4x4(&_name.m_matrix, XMMatrixMultiply(XMLoadFloat4x4(&_name.m_matrix), XMMatrixTranslation(0.f, 0.f, _zDelta)));
}

void Object::ObjectTranslation(Object& _name, float _xDelta, float _yDelta, float _zDelta)
{
	XMStoreFloat4x4(&_name.m_matrix, XMMatrixMultiply(XMLoadFloat4x4(&_name.m_matrix), XMMatrixTranslation(_xDelta, _yDelta, _zDelta)));
}

void Object::ObjectChangePosition(Object & _name, float _xDelta, float _yDelta, float _zDelta)
{
	XMStoreFloat4x4(&_name.m_matrix, XMMatrixTranslation(_xDelta, _yDelta, _zDelta));
}

void Object::ObjectRotationY(Object & _name, float _radians)
{
	XMStoreFloat4x4(&_name.m_matrix, XMMatrixMultiply(XMMatrixRotationY(_radians), XMLoadFloat4x4(&_name.m_matrix)));
}

bool Object::InitializeBuffers(ComPtr<ID3D11Device>& _device)
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

	m_indexCount = ARRAYSIZE(cubeIndices);

	D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
	indexBufferData.pSysMem = cubeIndices;
	indexBufferData.SysMemPitch = 0;
	indexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC indexBufferDesc(sizeof(cubeIndices), D3D11_BIND_INDEX_BUFFER);
	result = _device->CreateBuffer(&indexBufferDesc, &indexBufferData, m_indexBuffer.GetAddressOf());
	if (result != S_OK) return false;

	m_matrix = DirectX::XMFLOAT4X4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	return true;
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

void Object::ShutdownBuffers()
{
	m_vertexBuffer.Reset();
	m_indexBuffer.Reset();
	m_indexCount = 0;
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
	unsigned int stride = sizeof(VertexPositionColor);
	unsigned int offset = 0;

	_deviceContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
	_deviceContext->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	_deviceContext->DrawIndexed(m_indexCount, 0, 0);
}