#pragma once
///////////////////////
// Filename: DebugRenderer.h
///////////////////////
#ifndef _DEBUGRENDERER_H_
#define _DEBUGRENDERER_H_

///////////////////////
// INCLUDES
///////////////////////
#include <d3d11.h>			// ID3D11 & D3D11
#pragma comment(lib, "d3d11.lib")
#include <DirectXMath.h>	// XMFLOAT
#include <Windows.h>		// For ComPtr
#include <wrl.h>			// For ComPtr

using namespace DirectX;
using namespace Microsoft::WRL;

class DebugRenderer {
	struct VertexPositionColor {
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

	const int MAX_VERTS = 2048;				// Upper limit. Raise if needed  
	ComPtr<ID3D11Buffer> m_vertexBuffer;	// Initialized to be MAX_VERTS in size  
	VertexPositionColor* vertArray;			//Red(X), Green(Y), and Blue(Z)
	int vertCount;

public:
	DebugRenderer();
	~DebugRenderer();

	void AddLine(VertexPositionColor& _a, VertexPositionColor& _b);
	void Render(ComPtr<ID3D11Device>& _device, ComPtr<ID3D11DeviceContext>& _deviceContext);		// Calls Flush as well
	void Flush(ComPtr<ID3D11Device>& _device);														// Clears the current vertex buffer and creates a new one with the current vertArray
	void Shutdown();

private:
	void ShutdownBuffers();
};

#endif // !_DEBUGRENDERER_H_

//
//VertexPositionColor vert01 = { XMFLOAT4(0.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) };
//XMStoreFloat4(&vert01.pos, XMVector4Transform(XMLoadFloat4(&vert01.pos), XMLoadFloat4x4(&m_cube.matrix)));
//
//VertexPositionColor vert02 = { XMFLOAT4(2.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) };
//XMStoreFloat4(&vert02.pos, XMVector4Transform(XMLoadFloat4(&vert02.pos), XMLoadFloat4x4(&m_cube.matrix)));
//
//VertexPositionColor vert03 = { XMFLOAT4(0.f, 0.f, 0.f, 1.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f) };
//XMStoreFloat4(&vert03.pos, XMVector4Transform(XMLoadFloat4(&vert03.pos), XMLoadFloat4x4(&m_cube.matrix)));
//
//VertexPositionColor vert04 = { XMFLOAT4(0.f, 2.f, 0.f, 1.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f) };
//XMStoreFloat4(&vert04.pos, XMVector4Transform(XMLoadFloat4(&vert04.pos), XMLoadFloat4x4(&m_cube.matrix)));
//
//VertexPositionColor vert05 = { XMFLOAT4(0.f, 0.f, 0.f, 1.f), XMFLOAT4(0.f, 0.f, 1.f, 0.f) };
//XMStoreFloat4(&vert05.pos, XMVector4Transform(XMLoadFloat4(&vert05.pos), XMLoadFloat4x4(&m_cube.matrix)));
//
//VertexPositionColor vert06 = { XMFLOAT4(0.f, 0.f, 2.f, 1.f), XMFLOAT4(0.f, 0.f, 1.f, 0.f) };
//XMStoreFloat4(&vert06.pos, XMVector4Transform(XMLoadFloat4(&vert06.pos), XMLoadFloat4x4(&m_cube.matrix)));
//
//VertexPositionColor vert07 = { XMFLOAT4(0.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) };
//XMStoreFloat4(&vert07.pos, XMVector4Transform(XMLoadFloat4(&vert07.pos), XMLoadFloat4x4(&m_cube02.matrix)));
//
//VertexPositionColor vert08 = { XMFLOAT4(2.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) };
//XMStoreFloat4(&vert08.pos, XMVector4Transform(XMLoadFloat4(&vert08.pos), XMLoadFloat4x4(&m_cube02.matrix)));
//
//VertexPositionColor vert09 = { XMFLOAT4(0.f, 0.f, 0.f, 1.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f) };
//XMStoreFloat4(&vert09.pos, XMVector4Transform(XMLoadFloat4(&vert09.pos), XMLoadFloat4x4(&m_cube02.matrix)));
//
//VertexPositionColor vert10 = { XMFLOAT4(0.f, 2.f, 0.f, 1.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f) };
//XMStoreFloat4(&vert10.pos, XMVector4Transform(XMLoadFloat4(&vert10.pos), XMLoadFloat4x4(&m_cube02.matrix)));
//
//VertexPositionColor vert11 = { XMFLOAT4(0.f, 0.f, 0.f, 1.f), XMFLOAT4(0.f, 0.f, 1.f, 0.f) };
//XMStoreFloat4(&vert11.pos, XMVector4Transform(XMLoadFloat4(&vert11.pos), XMLoadFloat4x4(&m_cube02.matrix)));
//
//VertexPositionColor vert12 = { XMFLOAT4(0.f, 0.f, 2.f, 1.f), XMFLOAT4(0.f, 0.f, 1.f, 0.f) };
//XMStoreFloat4(&vert12.pos, XMVector4Transform(XMLoadFloat4(&vert12.pos), XMLoadFloat4x4(&m_cube02.matrix)));