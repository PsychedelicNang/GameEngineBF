///////////////////////
// Filename: Terrain.cpp
///////////////////////

#include "Terrain.h"

Terrain::Terrain()
{
	m_vertexBuffer = nullptr;
	m_indexBuffer = nullptr;
	m_terrainWidth = 0;
	m_terrainHeight = 0;
	m_vertexCount = 0;
	m_indexCount = 0;
}

Terrain::~Terrain()
{
	Shutdown();
}

bool Terrain::Initialize(ComPtr<ID3D11Device>& _device)
{
	// Manually set the width and height of the terrain.
	m_terrainWidth = 100;
	m_terrainHeight = 100;

	// Initialize the vertex and index buffer that hold the geometry for the terrain.
	if (InitializeBuffers(_device)) return false;

	return true;
}

void Terrain::Shutdown()
{
	// Release the buffers inside of the Terrain Class.
	ShutdownBuffers();
}

void Terrain::Render(ComPtr<ID3D11DeviceContext>& _deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(_deviceContext);
}

int Terrain::GetIndexCount()
{
	return m_indexCount;
}

bool Terrain::InitializeBuffers(ComPtr<ID3D11Device>& _device)
{
	VertexPositionColor* vertices;
	unsigned int* indices;
	int index = 0;
	float xPos, zPos;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	// Calculate the number of vertices in the terrain mesh.
	m_vertexCount = (m_terrainWidth - 1) * (m_terrainHeight - 1) * 8;

	// Set the index count to the same as the vertex count.
	m_indexCount = m_vertexCount;

	// Create the vertex array.
	vertices = new VertexPositionColor[m_vertexCount];
	if (!vertices)
		return false;

	// Create the index array.
	indices = new unsigned int[m_indexCount];
	if (!indices)
		return false;

	// Load the vertex and index arrays with the terrain data.
	for (int y = 0; y < m_terrainHeight - 1; y++)
	{
		for (int x = 0; x < m_terrainWidth - 1; x++)
		{
			// LINE 1
			// Upper left.
			xPos = (float)x;
			zPos = (float)(y + 1);

			vertices[index].position = XMFLOAT3(xPos, 0.0f, zPos);
			vertices[index].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			indices[index] = index;
			index++;

			// Upper right.
			xPos = (float)(x + 1);
			zPos = (float)(y + 1);

			vertices[index].position = XMFLOAT3(xPos, 0.0f, zPos);
			vertices[index].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			indices[index] = index;
			index++;

			// LINE 2
			// Upper right.
			xPos = (float)(x + 1);
			zPos = (float)(y + 1);

			vertices[index].position = XMFLOAT3(xPos, 0.0f, zPos);
			vertices[index].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			indices[index] = index;
			index++;

			// Bottom right.
			xPos = (float)(x + 1);
			zPos = (float)y;

			vertices[index].position = XMFLOAT3(xPos, 0.0f, zPos);
			vertices[index].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			indices[index] = index;
			index++;

			// LINE 3
			// Bottom right.
			xPos = (float)(x + 1);
			zPos = (float)y;

			vertices[index].position = XMFLOAT3(xPos, 0.0f, zPos);
			vertices[index].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			indices[index] = index;
			index++;

			// Bottom left.
			xPos = (float)x;
			zPos = (float)y;

			vertices[index].position = XMFLOAT3(xPos, 0.0f, zPos);
			vertices[index].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			indices[index] = index;
			index++;

			// LINE 4
			// Bottom left.
			xPos = (float)x;
			zPos = (float)y;

			vertices[index].position = XMFLOAT3(xPos, 0.0f, zPos);
			vertices[index].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			indices[index] = index;
			index++;

			// Upper left.
			xPos = (float)x;
			zPos = (float)(y + 1);

			vertices[index].position = XMFLOAT3(xPos, 0.0f, zPos);
			vertices[index].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			indices[index] = index;
			index++;
		}
	}

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexPositionColor) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = _device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (!result)
		return false;

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned int) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = _device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (!result)
		return false;

	// Release the arrays now that the buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

void Terrain::ShutdownBuffers()
{
	m_vertexBuffer.Reset();
	m_indexBuffer.Reset();
}

void Terrain::RenderBuffers(ComPtr<ID3D11DeviceContext>& _deviceContext)
{
	unsigned int stride = sizeof(VertexPositionColor);
	unsigned int offset = 0;

	_deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	_deviceContext->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	_deviceContext->DrawIndexed(m_indexCount, 0, 0);
}