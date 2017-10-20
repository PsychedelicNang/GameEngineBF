#pragma once
///////////////////////
// Filename: Object.h
///////////////////////
#ifndef _OBJECT_H_
#define _OBJECT_H_

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

class Object {
public:
	Object();
	~Object();

	void Initialize(ComPtr<ID3D11Buffer>& _vertexBuffer, ComPtr<ID3D11Buffer>& _indexBuffer, int _indexCount, size_t _byteSizeOfVertex, DXGI_FORMAT _indexFormat, D3D_PRIMITIVE_TOPOLOGY _topology);
	void Initialize(ComPtr<ID3D11Buffer>& _vertexBuffer, ComPtr<ID3D11Buffer>& _indexBuffer, int _indexCount, size_t _byteSizeOfVertex, DXGI_FORMAT _indexFormat, D3D_PRIMITIVE_TOPOLOGY _topology, XMFLOAT4X4 _matrix);
	void Initialize(ComPtr<ID3D11Buffer>& _vertexBuffer, ComPtr<ID3D11Buffer>& _indexBuffer, int _indexCount, size_t _byteSizeOfVertex, DXGI_FORMAT _indexFormat, D3D_PRIMITIVE_TOPOLOGY _topology, XMFLOAT4X4 _matrix, ComPtr<ID3D11Texture2D> _texture, ComPtr<ID3D11ShaderResourceView> _shaderResourceView);
	void Shutdown();
	void Render(ComPtr<ID3D11DeviceContext>& _deviceContext);

	int GetIndexCount();
	XMFLOAT4X4 GetMatrix();
	void ObjectTranslation(Object& _name, XMVECTOR _traslationAmount);
	void ObjectTranslation(Object& _name, float _xDelta, float _yDelta, float _zDelta);
	void ObjectTranslationX(Object& _name, float _xDelta);
	void ObjectTranslationY(Object& _name, float _yDelta);
	void ObjectTranslationZ(Object& _name, float _zDelta);
	void ObjectChangePosition(Object& _name, float _xDelta, float _yDelta, float _zDelta);
	void ObjectRotationY(Object& _name, float _radians);

private:
	ComPtr<ID3D11Buffer>				m_vertexBuffer;
	ComPtr<ID3D11Buffer>				m_indexBuffer;
	int m_indexCount;
	size_t m_byteSizeOfVertex;
	DXGI_FORMAT m_indexFormat;
	D3D_PRIMITIVE_TOPOLOGY m_topology;
	XMFLOAT4X4 m_matrix;
	ComPtr<ID3D11Texture2D>				m_texture;
	ComPtr<ID3D11ShaderResourceView>	m_shaderResourceView;

private:
	void InitializeBuffers(ComPtr<ID3D11Buffer>& _vertexBuffer, ComPtr<ID3D11Buffer>& _indexBuffer, int _indexCount, size_t _byteSizeOfVertex, DXGI_FORMAT _indexFormat, D3D_PRIMITIVE_TOPOLOGY _topology);
	void InitializeBuffers(ComPtr<ID3D11Buffer>& _vertexBuffer, ComPtr<ID3D11Buffer>& _indexBuffer, int _indexCount, size_t _byteSizeOfVertex, DXGI_FORMAT _indexFormat, D3D_PRIMITIVE_TOPOLOGY _topology, XMFLOAT4X4 _matrix);
	void InitializeBuffers(ComPtr<ID3D11Buffer>& _vertexBuffer, ComPtr<ID3D11Buffer>& _indexBuffer, int _indexCount, size_t _byteSizeOfVertex, DXGI_FORMAT _indexFormat, D3D_PRIMITIVE_TOPOLOGY _topology, XMFLOAT4X4 _matrix, ComPtr<ID3D11Texture2D> _texture, ComPtr<ID3D11ShaderResourceView> _shaderResourceView);
	void ShutdownBuffers();
	void ShutdownTextures();
	void RenderBuffers(ComPtr<ID3D11DeviceContext>& _deviceContext);
};

#endif // !_OBJECT_H_