#include "Object.h"
Object::Object()
{
	ComPtr<ID3D11Buffer>	m_vertexBuffer = nullptr;
	ComPtr<ID3D11Buffer>	m_indexBuffer = nullptr;
	int						m_indexCount = 0;
	size_t					m_byteSizeOfVertex = 0;
	DXGI_FORMAT				m_indexFormat = DXGI_FORMAT_UNKNOWN;
	D3D_PRIMITIVE_TOPOLOGY	m_topology = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
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

void Object::Initialize(ComPtr<ID3D11Buffer>& _vertexBuffer, ComPtr<ID3D11Buffer>& _indexBuffer, int _indexCount, size_t _byteSizeOfVertex, DXGI_FORMAT _indexFormat, D3D_PRIMITIVE_TOPOLOGY _topology)
{
	InitializeBuffers(_vertexBuffer, _indexBuffer, _indexCount, _byteSizeOfVertex, _indexFormat, _topology);
}

void Object::Initialize(ComPtr<ID3D11Buffer>& _vertexBuffer, ComPtr<ID3D11Buffer>& _indexBuffer, int _indexCount, size_t _byteSizeOfVertex, DXGI_FORMAT _indexFormat, D3D_PRIMITIVE_TOPOLOGY _topology, XMFLOAT4X4 _matrix)
{
	InitializeBuffers(_vertexBuffer, _indexBuffer, _indexCount, _byteSizeOfVertex, _indexFormat, _topology, _matrix);
}

void Object::Initialize(ComPtr<ID3D11Buffer>& _vertexBuffer, ComPtr<ID3D11Buffer>& _indexBuffer, int _indexCount, size_t _byteSizeOfVertex, DXGI_FORMAT _indexFormat, D3D_PRIMITIVE_TOPOLOGY _topology, XMFLOAT4X4 _matrix, ComPtr<ID3D11Texture2D> _texture, ComPtr<ID3D11ShaderResourceView> _shaderResourceView)
{
	InitializeBuffers(_vertexBuffer, _indexBuffer, _indexCount, _byteSizeOfVertex, _indexFormat, _topology, _matrix, _texture, _shaderResourceView);
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

XMFLOAT4X4 Object::GetMatrix()
{
	return m_matrix;
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

void Object::InitializeBuffers(ComPtr<ID3D11Buffer>& _vertexBuffer, ComPtr<ID3D11Buffer>& _indexBuffer, int _indexCount, size_t _byteSizeOfVertex, DXGI_FORMAT _indexFormat, D3D_PRIMITIVE_TOPOLOGY _topology)
{
	m_vertexBuffer = _vertexBuffer;
	m_indexBuffer = _indexBuffer;
	m_indexCount = _indexCount;
	m_byteSizeOfVertex = _byteSizeOfVertex;
	m_indexFormat = _indexFormat;
	m_topology = _topology;
}

void Object::InitializeBuffers(ComPtr<ID3D11Buffer>& _vertexBuffer, ComPtr<ID3D11Buffer>& _indexBuffer, int _indexCount, size_t _byteSizeOfVertex, DXGI_FORMAT _indexFormat, D3D_PRIMITIVE_TOPOLOGY _topology, XMFLOAT4X4 _matrix)
{
	m_vertexBuffer = _vertexBuffer;
	m_indexBuffer = _indexBuffer;
	m_indexCount = _indexCount;
	m_byteSizeOfVertex = _byteSizeOfVertex;
	m_indexFormat = _indexFormat;
	m_topology = _topology;
	m_matrix = _matrix;
}

void Object::InitializeBuffers(ComPtr<ID3D11Buffer>& _vertexBuffer, ComPtr<ID3D11Buffer>& _indexBuffer, int _indexCount, size_t _byteSizeOfVertex, DXGI_FORMAT _indexFormat, D3D_PRIMITIVE_TOPOLOGY _topology, XMFLOAT4X4 _matrix, ComPtr<ID3D11Texture2D> _texture, ComPtr<ID3D11ShaderResourceView> _shaderResourceView)
{
	m_vertexBuffer = _vertexBuffer;
	m_indexBuffer = _indexBuffer;
	m_indexCount = _indexCount;
	m_byteSizeOfVertex = _byteSizeOfVertex;
	m_indexFormat = _indexFormat;
	m_topology = _topology;
	m_matrix = _matrix;
	m_texture = _texture;
	m_shaderResourceView = _shaderResourceView;
}

void Object::ShutdownBuffers()
{
	m_vertexBuffer.Reset();
	m_indexBuffer.Reset();
	m_indexCount = 0;
	size_t					m_byteSizeOfVertex = 0;
	DXGI_FORMAT				m_indexFormat = DXGI_FORMAT_UNKNOWN;
	D3D_PRIMITIVE_TOPOLOGY	m_topology = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
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
	unsigned int stride = m_byteSizeOfVertex;
	unsigned int offset = 0;

	_deviceContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
	_deviceContext->IASetIndexBuffer(m_indexBuffer.Get(), m_indexFormat, 0);
	_deviceContext->IASetPrimitiveTopology(m_topology);
	_deviceContext->DrawIndexed(m_indexCount, 0, 0);
}