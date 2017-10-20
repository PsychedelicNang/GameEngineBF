#pragma once
///////////////////////
// Filename: Terrain.h
///////////////////////
#ifndef _TERRAIN_H_
#define _TERRAIN_H_

///////////////////////
// INCLUDES
///////////////////////
#include "IncludesBJF.h"

class Terrain {
public:
	Terrain();
	~Terrain();

	bool Initialize(ComPtr<ID3D11Device>& _device);
	void Shutdown();
	void Render(ComPtr<ID3D11DeviceContext>& _deviceContext);

	int GetIndexCount();

private:
	bool InitializeBuffers(ComPtr<ID3D11Device>& _device);
	void ShutdownBuffers();
	void RenderBuffers(ComPtr<ID3D11DeviceContext>& _deviceContext);

private:
	int m_terrainWidth, m_terrainHeight;
	int m_vertexCount, m_indexCount;
	ComPtr<ID3D11Buffer> m_vertexBuffer, m_indexBuffer;
};

#endif // !_TERRAIN_H_