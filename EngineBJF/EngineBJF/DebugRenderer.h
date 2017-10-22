#pragma once
/***************************
* Filename: DebugRenderer.h
***************************/
#ifndef _DEBUGRENDERER_H_
#define _DEBUGRENDERER_H_

/***************************
* INCLUDES
***************************/
#include "IncludesBJF.h"

class DebugRenderer {
	const int MAX_VERTS = 2048;				// Upper limit. Raise if needed  
	ComPtr<ID3D11Buffer> m_vertexBuffer;	// Initialized to be MAX_VERTS in size  
	VertexPositionColor* vertArray;			//Red(X), Green(Y), and Blue(Z)
	int vertCount;

public:
	DebugRenderer();
	~DebugRenderer();

	bool CreateVertexBuffer(ComPtr<ID3D11Device>& _device);
	void AddLine(VertexPositionColor* _a, VertexPositionColor* _b);
	void AddLine(VertexPositionColor& _a, VertexPositionColor& _b);
	void Render(ComPtr<ID3D11Device>& _device, ComPtr<ID3D11DeviceContext>& _deviceContext);		// Renders the current vertex buffer and then calls Flush()
	void Flush(ComPtr<ID3D11Device>& _device);														// Clears the current vertex buffer and resets the vertex count
	void Shutdown();

private:
	bool CreateVertexBufferTask(ComPtr<ID3D11Device> _device);
	void AddLineToBuffers(VertexPositionColor* _a, VertexPositionColor* _b);
	void AddLineToBuffers(VertexPositionColor& _a, VertexPositionColor& _b);
	void RenderBuffers(ComPtr<ID3D11Device>& _device, ComPtr<ID3D11DeviceContext>& _deviceContext);		// Renders the current vertex buffer and then calls Flush()
	void FlushBuffers(ComPtr<ID3D11Device>& _device);													// Clears the current vertex buffer and resets the vertex count
	void ShutdownBuffers();
};

#endif // !_DEBUGRENDERER_H_