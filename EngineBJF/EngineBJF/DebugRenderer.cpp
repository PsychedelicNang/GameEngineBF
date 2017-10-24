///////////////////////
// Filename: DebugRenderer.cpp
///////////////////////

#include "DebugRenderer.h"

DebugRenderer::DebugRenderer()
{
	vertCount = 0;
	m_vertexBuffer = nullptr;
	vertArray = new VertexPositionColor[MAX_VERTS];
}

DebugRenderer::~DebugRenderer()
{
	Shutdown();
}

bool DebugRenderer::CreateVertexBuffer(ComPtr<ID3D11Device>& _device)
{
	if (!CreateVertexBufferTask(_device)) return false;
	return true;
}

void DebugRenderer::AddLine(VertexPositionColor* _a, VertexPositionColor* _b)
{
	AddLineToBuffers(_a, _b);
}

void DebugRenderer::AddLine(VertexPositionColor & _a, VertexPositionColor & _b)
{
	AddLineToBuffers(_a, _b);
}

void DebugRenderer::Render(ComPtr<ID3D11Device>& _device, ComPtr<ID3D11DeviceContext>& _deviceContext)
{
	RenderBuffers(_device, _deviceContext);
}

void DebugRenderer::Flush(ComPtr<ID3D11Device>& _device)
{
	FlushBuffers(_device);
}

bool DebugRenderer::CreateVertexBufferTask(ComPtr<ID3D11Device> _device)
{
	HRESULT result;

	D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
	vertexBufferData.pSysMem = vertArray;
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(VertexPositionColor) * MAX_VERTS, D3D11_BIND_VERTEX_BUFFER);
	result = _device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, m_vertexBuffer.GetAddressOf());

	if (result != S_OK) return false;
	return true;
}

void DebugRenderer::AddLineToBuffers(VertexPositionColor* _a, VertexPositionColor* _b)
{
	vertArray[vertCount] = *_a;
	vertArray[++vertCount] = *_b;
	vertCount++;
}

void DebugRenderer::AddLineToBuffers(VertexPositionColor& _a, VertexPositionColor& _b)
{
	vertArray[vertCount] = _a;
	vertArray[++vertCount] = _b;
	vertCount++;
}

void DebugRenderer::RenderBuffers(ComPtr<ID3D11Device>& _device, ComPtr<ID3D11DeviceContext>& _deviceContext)
{
	unsigned int stride = sizeof(VertexPositionColor);
	unsigned int offset = 0;
	_deviceContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
	_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	_deviceContext->Draw(vertCount, 0);
	Flush(_device);
}

void DebugRenderer::FlushBuffers(ComPtr<ID3D11Device>& _device)
{
	m_vertexBuffer.Reset();
	vertCount = 0;
}

void DebugRenderer::Shutdown()
{
	ShutdownBuffers();
}

void DebugRenderer::ShutdownBuffers()
{
	m_vertexBuffer.Reset();
	vertCount = 0;
	delete[] vertArray;
}
