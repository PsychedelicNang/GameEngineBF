#pragma once
///////////////////////
// Filename: Object.h
///////////////////////
#ifndef _OBJECT_H_
#define _OBJECT_H_

///////////////////////
// INCLUDES
///////////////////////
#include "IncludesBJF.h"

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
	XMFLOAT4X4 m_matrix;
	ComPtr<ID3D11Texture2D>				m_texture;
	ComPtr<ID3D11ShaderResourceView>	m_shaderResourceView;

private:
	bool InitializeBuffers(ComPtr<ID3D11Device>& _device);
	bool InitializeBuffers(ComPtr<ID3D11Device>& _device, XMFLOAT4X4 _matrix);
	void ShutdownBuffers();
	void ShutdownTextures();
	void RenderBuffers(ComPtr<ID3D11DeviceContext>& _deviceContext);
};

#endif // !_OBJECT_H_

//void SceneManager::CreateCube(void)
//{
//	// Load mesh vertices. Each vertex has a position and a color.
//	//VertexPositionColor cubeVertices[] =
//	//{
//	//	{ XMFLOAT4(-1.0f, 1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 0.f, 0.f) },
//	//	{ XMFLOAT4(1.0f,  1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 0.f, 0.f) },
//	//	{ XMFLOAT4(1.0f,  1.0f,  1.0f, 1.0f)  , XMFLOAT4(0.f, 1.f, 0.f, 0.f) },
//	//	{ XMFLOAT4(-1.0f,  1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 1.f, 0.f, 0.f) },
//	//	{ XMFLOAT4(-1.0f, -1.0f, -1.0f, 1.0f) , XMFLOAT4(0.f, 0.f, 1.f, 0.f) },
//	//	{ XMFLOAT4(1.0f, -1.0f, -1.0f, 1.0f)  , XMFLOAT4(0.f, 0.f, 1.f, 0.f) },
//	//	{ XMFLOAT4(1.0f, -1.0f,  1.0f, 1.0f)  , XMFLOAT4(0.f, 0.f, 0.f, 1.f) },
//	//	{ XMFLOAT4(-1.0f, -1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 0.f, 0.f, 1.f) },
//	//};
//
//	//VertexPositionColor cubeVertices[] =
//	//{
//	//	////3, 1, 0,
//	//	//{ XMFLOAT4(-1.0f,  1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 1.f, 0.f, 1.f) },
//	//	//{ XMFLOAT4(1.0f,  1.0f, -1.0f, 1.0f)  , XMFLOAT4(0.f, 1.f, 0.f, 1.f) },
//	//	//{ XMFLOAT4(-1.0f, 1.0f, -1.0f, 1.0f)  , XMFLOAT4(0.f, 1.f, 0.f, 1.f) },
//	//	////2, 1, 3,
//	//	//{ XMFLOAT4(1.0f,  1.0f,  1.0f, 1.0f)  , XMFLOAT4(0.f, 1.f, 0.f, 1.f) },
//	//	//{ XMFLOAT4(1.0f,  1.0f, -1.0f, 1.0f)  , XMFLOAT4(0.f, 1.f, 0.f, 1.f) },
//	//	//{ XMFLOAT4(-1.0f,  1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 1.f, 0.f, 1.f) },
//	//	//0, 5, 4,
//	//	{ XMFLOAT4(-1.0f, 1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 1.f, 1.f)},
//	//	{ XMFLOAT4(1.0f, -1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 1.f, 1.f)},
//	//	{ XMFLOAT4(-1.0f, -1.0f, -1.0f, 1.0f) , XMFLOAT4(1.f, 0.f, 1.f, 1.f)},
//	//	//1, 5, 0,
//	//	{ XMFLOAT4(1.0f,  1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 1.f, 1.f)},
//	//	//{ XMFLOAT4(1.0f, -1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 1.f, 1.f)},
//	//	//{ XMFLOAT4(-1.0f, 1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 1.f, 1.f)},
//	//	////3, 4, 7,
//	//	//{ XMFLOAT4(-1.0f,  1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 1.f, 1.f, 1.f) },
//	//	//{ XMFLOAT4(-1.0f, -1.0f, -1.0f, 1.0f) , XMFLOAT4(0.f, 1.f, 1.f, 1.f) },
//	//	//{ XMFLOAT4(-1.0f, -1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 1.f, 1.f, 1.f) },
//	//	////0, 4, 3,
//	//	//{ XMFLOAT4(-1.0f, 1.0f, -1.0f, 1.0f)  , XMFLOAT4(0.f, 1.f, 1.f, 1.f) },
//	//	//{ XMFLOAT4(-1.0f, -1.0f, -1.0f, 1.0f) , XMFLOAT4(0.f, 1.f, 1.f, 1.f) },
//	//	//{ XMFLOAT4(-1.0f,  1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 1.f, 1.f, 1.f) },
//	//	////1, 6, 5,
//	//	//{ XMFLOAT4(1.0f,  1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 0.f, 1.f) },
//	//	//{ XMFLOAT4(1.0f, -1.0f,  1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 0.f, 1.f) },
//	//	//{ XMFLOAT4(1.0f, -1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 0.f, 1.f) },
//	//	////2, 6, 1,
//	//	//{ XMFLOAT4(1.0f,  1.0f,  1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 0.f, 1.f) },
//	//	//{ XMFLOAT4(1.0f, -1.0f,  1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 0.f, 1.f) },
//	//	//{ XMFLOAT4(1.0f,  1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 0.f, 1.f) },
//	//	////2, 7, 6,
//	//	//{ XMFLOAT4(1.0f,  1.0f,  1.0f, 1.0f)  , XMFLOAT4(0.f, 0.f, 1.f, 1.f) },
//	//	//{ XMFLOAT4(-1.0f, -1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 0.f, 1.f, 1.f) },
//	//	//{ XMFLOAT4(1.0f, -1.0f,  1.0f, 1.0f)  , XMFLOAT4(0.f, 0.f, 1.f, 1.f) },
//	//	////3, 7, 2,
//	//	//{ XMFLOAT4(-1.0f,  1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 0.f, 1.f, 1.f) },
//	//	//{ XMFLOAT4(-1.0f, -1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 0.f, 1.f, 1.f) },
//	//	//{ XMFLOAT4(1.0f,  1.0f,  1.0f, 1.0f)  , XMFLOAT4(0.f, 0.f, 1.f, 1.f) },
//	//	////6, 4, 5,
//	//	//{ XMFLOAT4(1.0f, -1.0f,  1.0f, 1.0f)  , XMFLOAT4(1.f, 1.f, 0.f, 1.f) },
//	//	//{ XMFLOAT4(-1.0f, -1.0f, -1.0f, 1.0f) , XMFLOAT4(1.f, 1.f, 0.f, 1.f) },
//	//	//{ XMFLOAT4(1.0f, -1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 1.f, 0.f, 1.f) },
//	//	////7, 4, 6,
//	//	//{ XMFLOAT4(-1.0f, -1.0f,  1.0f, 1.0f) , XMFLOAT4(1.f, 1.f, 0.f, 1.f) },
//	//	//{ XMFLOAT4(-1.0f, -1.0f, -1.0f, 1.0f) , XMFLOAT4(1.f, 1.f, 0.f, 1.f) },
//	//	//{ XMFLOAT4(1.0f, -1.0f,  1.0f, 1.0f)  , XMFLOAT4(1.f, 1.f, 0.f, 1.f) },
//	//};
//
//	VertexPositionColorUVNormal cubeVertices[] =
//	{
//		//3, 1, 0,
//		{ XMFLOAT4(-1.0f,  1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 1.f, 0.f, 1.f), XMFLOAT4(0.f, 0.f, 0.f, 0.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f) },
//		{ XMFLOAT4(1.0f,  1.0f, -1.0f, 1.0f)  , XMFLOAT4(0.f, 1.f, 0.f, 1.f), XMFLOAT4(1.f, 1.f, 0.f, 0.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f) },
//		{ XMFLOAT4(-1.0f, 1.0f, -1.0f, 1.0f)  , XMFLOAT4(0.f, 1.f, 0.f, 1.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f) },
//		//2, 1, 3,
//		{ XMFLOAT4(1.0f,  1.0f,  1.0f, 1.0f)  , XMFLOAT4(0.f, 1.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f) },
//		{ XMFLOAT4(1.0f,  1.0f, -1.0f, 1.0f)  , XMFLOAT4(0.f, 1.f, 0.f, 1.f), XMFLOAT4(1.f, 1.f, 0.f, 0.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f) },
//		{ XMFLOAT4(-1.0f,  1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 1.f, 0.f, 1.f), XMFLOAT4(0.f, 0.f, 0.f, 0.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f) },
//		//0, 5, 4,
//		{ XMFLOAT4(-1.0f, 1.0f, -1.0f, 1.0f) , XMFLOAT4(1.f, 0.f, 1.f, 1.f), XMFLOAT4(0.f, 0.f, 0.f, 0.f), XMFLOAT4(0.f, 0.f, -1.f, 0.f) },
//		{ XMFLOAT4(1.0f, -1.0f, -1.0f, 1.0f) , XMFLOAT4(1.f, 0.f, 1.f, 1.f), XMFLOAT4(1.f, 1.f, 0.f, 0.f), XMFLOAT4(0.f, 0.f, -1.f, 0.f) },
//		{ XMFLOAT4(-1.0f, -1.0f, -1.0f, 1.0f), XMFLOAT4(1.f, 0.f, 1.f, 1.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f), XMFLOAT4(0.f, 0.f, -1.f, 0.f) },
//		//1, 5, 0,
//		{ XMFLOAT4(1.0f,  1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 1.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f), XMFLOAT4(0.f, 0.f, -1.f, 0.f) },
//		{ XMFLOAT4(1.0f, -1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 1.f, 1.f), XMFLOAT4(1.f, 1.f, 0.f, 0.f), XMFLOAT4(0.f, 0.f, -1.f, 0.f) },
//		{ XMFLOAT4(-1.0f, 1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 1.f, 1.f), XMFLOAT4(0.f, 0.f, 0.f, 0.f), XMFLOAT4(0.f, 0.f, -1.f, 0.f) },
//		//3, 4, 7,
//		{ XMFLOAT4(-1.0f,  1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 1.f, 1.f, 1.f), XMFLOAT4(0.f, 0.f, 0.f, 0.f), XMFLOAT4(-1.f, 0.f, 0.f, 0.f) },
//		{ XMFLOAT4(-1.0f, -1.0f, -1.0f, 1.0f) , XMFLOAT4(0.f, 1.f, 1.f, 1.f), XMFLOAT4(1.f, 1.f, 0.f, 0.f), XMFLOAT4(-1.f, 0.f, 0.f, 0.f) },
//		{ XMFLOAT4(-1.0f, -1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 1.f, 1.f, 1.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f), XMFLOAT4(-1.f, 0.f, 0.f, 0.f) },
//		//0, 4, 3,
//		{ XMFLOAT4(-1.0f, 1.0f, -1.0f, 1.0f)  , XMFLOAT4(0.f, 1.f, 1.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f), XMFLOAT4(-1.f, 0.f, 0.f, 0.f) },
//		{ XMFLOAT4(-1.0f, -1.0f, -1.0f, 1.0f) , XMFLOAT4(0.f, 1.f, 1.f, 1.f), XMFLOAT4(1.f, 1.f, 0.f, 0.f), XMFLOAT4(-1.f, 0.f, 0.f, 0.f) },
//		{ XMFLOAT4(-1.0f,  1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 1.f, 1.f, 1.f), XMFLOAT4(0.f, 0.f, 0.f, 0.f), XMFLOAT4(-1.f, 0.f, 0.f, 0.f) },
//		//1, 6, 5,
//		{ XMFLOAT4(1.0f,  1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 0.f, 1.f), XMFLOAT4(0.f, 0.f, 0.f, 0.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) },
//		{ XMFLOAT4(1.0f, -1.0f,  1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 1.f, 0.f, 0.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) },
//		{ XMFLOAT4(1.0f, -1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 0.f, 1.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) },
//		//2, 6, 1,
//		{ XMFLOAT4(1.0f,  1.0f,  1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) },
//		{ XMFLOAT4(1.0f, -1.0f,  1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 1.f, 0.f, 0.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) },
//		{ XMFLOAT4(1.0f,  1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 0.f, 1.f), XMFLOAT4(0.f, 0.f, 0.f, 0.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) },
//		//2, 7, 6,
//		{ XMFLOAT4(1.0f,  1.0f,  1.0f, 1.0f)  , XMFLOAT4(0.f, 0.f, 1.f, 1.f), XMFLOAT4(0.f, 0.f, 0.f, 0.f), XMFLOAT4(0.f, 0.f, 1.f, 0.f) },
//		{ XMFLOAT4(-1.0f, -1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 0.f, 1.f, 1.f), XMFLOAT4(1.f, 1.f, 0.f, 0.f), XMFLOAT4(0.f, 0.f, 1.f, 0.f) },
//		{ XMFLOAT4(1.0f, -1.0f,  1.0f, 1.0f)  , XMFLOAT4(0.f, 0.f, 1.f, 1.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f), XMFLOAT4(0.f, 0.f, 1.f, 0.f) },
//		//3, 7, 2,
//		{ XMFLOAT4(-1.0f,  1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 0.f, 1.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f), XMFLOAT4(0.f, 0.f, 1.f, 0.f) },
//		{ XMFLOAT4(-1.0f, -1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 0.f, 1.f, 1.f), XMFLOAT4(1.f, 1.f, 0.f, 0.f), XMFLOAT4(0.f, 0.f, 1.f, 0.f) },
//		{ XMFLOAT4(1.0f,  1.0f,  1.0f, 1.0f)  , XMFLOAT4(0.f, 0.f, 1.f, 1.f), XMFLOAT4(0.f, 0.f, 0.f, 0.f), XMFLOAT4(0.f, 0.f, 1.f, 0.f) },
//		//6, 4, 5,
//		{ XMFLOAT4(1.0f, -1.0f,  1.0f, 1.0f)  , XMFLOAT4(1.f, 1.f, 0.f, 1.f), XMFLOAT4(0.f, 0.f, 0.f, 0.f), XMFLOAT4(0.f, -1.f, 0.f, 0.f) },
//		{ XMFLOAT4(-1.0f, -1.0f, -1.0f, 1.0f) , XMFLOAT4(1.f, 1.f, 0.f, 1.f), XMFLOAT4(1.f, 1.f, 0.f, 0.f), XMFLOAT4(0.f, -1.f, 0.f, 0.f) },
//		{ XMFLOAT4(1.0f, -1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 1.f, 0.f, 1.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f), XMFLOAT4(0.f, -1.f, 0.f, 0.f) },
//		//7, 4, 6,
//		{ XMFLOAT4(-1.0f, -1.0f,  1.0f, 1.0f) , XMFLOAT4(1.f, 1.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f), XMFLOAT4(0.f, -1.f, 0.f, 0.f) },
//		{ XMFLOAT4(-1.0f, -1.0f, -1.0f, 1.0f) , XMFLOAT4(1.f, 1.f, 0.f, 1.f), XMFLOAT4(1.f, 1.f, 0.f, 0.f), XMFLOAT4(0.f, -1.f, 0.f, 0.f) },
//		{ XMFLOAT4(1.0f, -1.0f,  1.0f, 1.0f)  , XMFLOAT4(1.f, 1.f, 0.f, 1.f), XMFLOAT4(0.f, 0.f, 0.f, 0.f), XMFLOAT4(0.f, -1.f, 0.f, 0.f) }
//	};
//
//	D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
//	vertexBufferData.pSysMem = cubeVertices;
//	vertexBufferData.SysMemPitch = 0;
//	vertexBufferData.SysMemSlicePitch = 0;
//	CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(cubeVertices), D3D11_BIND_VERTEX_BUFFER);
//	m_device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, m_cube.m_vertexBuffer.GetAddressOf());
//
//	static const unsigned short cubeIndices[] =
//	{
//		3, 1, 0,
//		2, 1, 3,
//		0, 5, 4,
//		1, 5, 0,
//		3, 4, 7,
//		0, 4, 3,
//		1, 6, 5,
//		2, 6, 1,
//		2, 7, 6,
//		3, 7, 2,
//		6, 4, 5,
//		7, 4, 6
//	};
//
//	m_cube.m_indexCount = ARRAYSIZE(cubeIndices);
//
//	D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
//	indexBufferData.pSysMem = cubeIndices;
//	indexBufferData.SysMemPitch = 0;
//	indexBufferData.SysMemSlicePitch = 0;
//	CD3D11_BUFFER_DESC indexBufferDesc(sizeof(cubeIndices), D3D11_BIND_INDEX_BUFFER);
//	m_device->CreateBuffer(&indexBufferDesc, &indexBufferData, m_cube.m_indexBuffer.GetAddressOf());
//
//	m_cube.matrix = DirectX::XMFLOAT4X4(
//		1, 0, 0, 0,
//		0, 1, 0, 0,
//		0, 0, 1, 0,
//		-4, 0, -5, 1);
//	m_objectsToRender.push_back(&m_cube);
//}
////