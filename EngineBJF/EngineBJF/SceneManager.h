#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <iostream>
#include <fstream> 
#include <Windows.h>
#include <wrl.h>
#include <vector>
#include <fstream>
#include "XTime.h"
#include "resource.h"
#include "ShaderStructures.h"
#include "Mesh.h"
#include "FbxLibraryDLLLoaderAndFileReader.h"
#include "MaterialComponents.h"
#include "WICTextureLoader.h"
#include "MeshComponents.h"
#define WIDTH 1024
#define HEIGHT 768
#define PPVMATERIALLAB 1
using namespace DirectX;
using namespace Microsoft::WRL;

class SceneManager {
public:
	SceneManager();
	~SceneManager();
	struct PipelineState
	{
		ComPtr<ID3D11InputLayout>			input_layout;
		ComPtr<ID3D11VertexShader>			vertex_shader;
		ComPtr<ID3D11PixelShader>			pixel_shader;
		ComPtr<ID3D11RenderTargetView>		render_target;
		ComPtr<ID3D11Texture2D>				depthStencilBuffer;
		ComPtr<ID3D11DepthStencilState>		depthStencilState;
		ComPtr<ID3D11DepthStencilView>		depthStencilView;
		ComPtr<ID3D11RasterizerState>		rasterState;
	} m_defaultPipeline;

	struct Object {
		ComPtr<ID3D11Buffer>				m_vertexBuffer;
		ComPtr<ID3D11Buffer>				m_indexBuffer;
		UINT32 m_indexCount = 0;
		XMFLOAT4X4 matrix = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1 };
		ComPtr<ID3D11Texture2D>				m_texture;
		ComPtr<ID3D11ShaderResourceView>	m_shaderResourceView;

	} m_cube, m_cube02, m_triangle, m_mesh, m_advancedMesh;
	
	struct PPVStuff {
		std::vector<ID3D11ShaderResourceView*> m_materialsSRVs;
		ComPtr<ID3D11PixelShader> m_PS;
		ComPtr<ID3D11VertexShader> m_VS;
		ComPtr<ID3D11InputLayout> m_IL;
		~PPVStuff();
	} m_PPVStuff, m_AdvancedMeshStuff;

	class DebugRenderer{
	public:
		DebugRenderer();
		~DebugRenderer();
		const int MAX_VERTS = 2048;				// Upper limit. Raise if needed  
		ComPtr<ID3D11Buffer> m_vertexBuffer;	// Initialized to be MAX_VERTS in size  
		VertexPositionColor vertArray[2048];		//Red(X), Green(Y), and Blue(Z)
		int vertCount = 0;

		void AddLine(VertexPositionColor _a, VertexPositionColor _b);
		void Flush(ComPtr<ID3D11Device>& _device);
	} m_debugRenderer;

	enum CameraState {
		cameraDefault = 1,
		lookAtOrigin,
		lookAtCube1,
		lookAtCube2,
		turnToCube1,
		turnToCube2
	} m_cameraState;

	XTime timer;
	ComPtr<ID3D11Device>				m_device;
	ComPtr<ID3D11DeviceContext>			m_imedContext;
	ComPtr<IDXGISwapChain>				m_swapChain;
	ComPtr<ID3D11Buffer>				m_constantBuffer;
	D3D11_VIEWPORT						m_viewport;

	ModelViewProjectionConstantBuffer m_constantBufferData;
	XMFLOAT4X4 m_camera;
	XMFLOAT4X4 m_testCamera;
	std::vector<Object*> m_objectsToRender;

	float radians;
	float m_camerazoom;
	float m_nearPlane;
	float m_farPlane;

	float timeBetweenFrames;
	bool mouseMove;
	bool rotateObjects;
	POINT prevCursorPos;
	POINT currCursorPos;

	XMVECTOR eye;
	XMVECTOR at;
	XMVECTOR up;

	bool LoadCompiledShaderData(char **byteCode, size_t &byteCodeSize, const char *fileName);

	void InitViewport(D3D11_VIEWPORT& _viewport);
	void InitDepthBuffer(ComPtr<ID3D11Texture2D>& _depthBuffer);
	void InitDepthState(ComPtr<ID3D11DepthStencilState>& _depthState);
	void InitDepthView(ComPtr<ID3D11DepthStencilView>& _depthView);
	void InitRasterState(ComPtr<ID3D11RasterizerState>& _rasterState);
	void InitConstantBuffer(ComPtr<ID3D11Buffer>& _buffer);
	void InitShadersAndInputLayout(ComPtr<ID3D11PixelShader>& _PS, ComPtr<ID3D11VertexShader>& _VS, ComPtr<ID3D11InputLayout>& _IL);

	void CreateWindowResources(HWND& _hWnd);
	void CreateCube(void);
	void CreateCube(Object& _name, float _xPos, float _yPos, float _zPos);
	void CreateTriangle(void);
	void CreateViewAndPerspectiveMatrix(void);

	void ObjectTranslation(Object& _name, XMVECTOR _traslationAmount);
	void ObjectTranslation(Object& _name, float _xDelta, float _yDelta, float _zDelta);
	void ObjectTranslationX(Object& _name, float _xDelta);
	void ObjectTranslationY(Object& _name, float _yDelta);
	void ObjectTranslationZ(Object& _name, float _zDelta);
	void ObjectChangePosition(Object& _name, float _xDelta, float _yDelta, float _zDelta);
	void ObjectRotationY(Object& _name, float _radians);

	void CameraTranslation(XMVECTOR _traslationAmount);
	void CameraTranslation(float _xDelta, float _yDelta, float _zDelta);
	void CameraTranslationX(float _xDelta);
	void CameraTranslationY(float _yDelta);
	void CameraTranslationZ(float _zDelta);
	void CameraMoveEyePosition(float _x, float _y, float _z);
	XMMATRIX CameraLookAt(XMVECTOR _viewerPos, XMVECTOR _targetPos, XMVECTOR _localUp);
	XMMATRIX CameraTurnTo(XMMATRIX _viewerMatrix, XMVECTOR _targetPos, float _speed);
	XMFLOAT4X4 CameraMouseLook(XMFLOAT4X4 _viewerMatrix, float _xDelta, float _yDelta);

	void Update(void);
	void Render(void);
	void UpdateConstBuffModelAndView(Object& _name);

	bool ReadInBinaryMeshFile(Object& _fillOutObject);
	bool ReadInAdvancedBinaryMeshFile(const char* _fileName, Object& _fillOutObject);
	
	void SetPipelineStates(PipelineState& _pS);
	void CheckUserInput(WPARAM wParam);
	void RunTaskList(HWND& _hWnd);
	void RunDebugMessage(void);
	
	bool RunFbxLoader(void);
	bool RunTaskForPPV(void);
	bool RunTaskForAdvancedMesh(void);
};