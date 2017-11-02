#pragma once
/***************************
* Filename: Object.h
***************************/
#ifndef _OBJECT_H_
#define _OBJECT_H_

/***************************
* INCLUDES
***************************/
#include "IncludesBJF.h"
#include <fstream>
class Object {
public:
	Object();
	~Object();

	bool Initialize(ComPtr<ID3D11Device>& _device);
	bool Initialize(ComPtr<ID3D11Device>& _device, XMFLOAT4X4 _matrix);
	void Shutdown();
	void Render(ComPtr<ID3D11DeviceContext>& _deviceContext);

	int GetIndexCount();
	XMFLOAT4X4 GetObjectFloat4x4();
	XMMATRIX GetObjectMatrix();

	void ObjectTranslation(XMVECTOR _traslationAmount);
	void ObjectTranslation(float _xDelta, float _yDelta, float _zDelta);
	void ObjectTranslationX(float _xDelta);
	void ObjectTranslationY(float _yDelta);
	void ObjectTranslationZ(float _zDelta);
	void ObjectChangePosition(float _newXPosition, float _newYPosition, float _newZPosition);
	void ObjectRotationX(float _radians);
	void ObjectRotationY(float _radians);
	void ObjectRotationZ(float _radians);

	// Reads in a binary mesh file containing vertex and index position data and fills out the object of which this function was called from
	bool ReadInMeshFromBinaryFile(ComPtr<ID3D11Device>& _device, const char * _fileName);
	
	// Reads in a binary mesh file containing vertex and index Position, UV, and Normal data and fills out the object of which this function was called from
	bool ReadInAdvancedMeshFromBinaryFile(ComPtr<ID3D11Device>& _device, const char* _fileName);
private:
	ComPtr<ID3D11Buffer>				m_vertexBuffer;
	ComPtr<ID3D11Buffer>				m_indexBuffer;
	int m_indexCount, m_vertexCount, m_stride;
	XMFLOAT4X4 m_matrix;
	ComPtr<ID3D11Texture2D>				m_texture;
	ComPtr<ID3D11ShaderResourceView>	m_shaderResourceView;

private:
	bool InitializeBuffers(ComPtr<ID3D11Device>& _device);
	bool InitializeBuffers(ComPtr<ID3D11Device>& _device, XMFLOAT4X4 _matrix);

	// Reads in a binary mesh file containing vertex and index position data and fills out the object of which this function was called from
	bool ReadInBinaryMeshFile(ComPtr<ID3D11Device>& _device, const char * _fileName);
	
	// Reads in a binary mesh file containing vertex and index Position, UV, and Normal data and fills out the object of which this function was called from
	bool ReadInAdvancedBinaryMeshFile(ComPtr<ID3D11Device>& _device, const char* _fileName);

	void RenderBuffers(ComPtr<ID3D11DeviceContext>& _deviceContext);

	void ShutdownBuffers();
	void ShutdownTextures();
};

#endif // !_OBJECT_H_