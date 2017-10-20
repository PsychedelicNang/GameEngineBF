#pragma once
#include <iostream>
#include <fstream> 
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

#include "IncludesBJF.h"
#include "DebugRenderer.h"
#include "Terrain.h"
#include "Object.h"
#include "Camera.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#define WIDTH 1024
#define HEIGHT 768

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

	Object* myCube;
	Camera* myCamera;
	Terrain* myTerrain;
	DebugRenderer* myDebugRenderer;
	
	//struct PPVStuff {
	//	std::vector<ID3D11ShaderResourceView*> m_materialsSRVs;
	//	ComPtr<ID3D11PixelShader> m_PS;
	//	ComPtr<ID3D11VertexShader> m_VS;
	//	ComPtr<ID3D11InputLayout> m_IL;
	//	~PPVStuff();
	//} m_PPVStuff, m_AdvancedMeshStuff;

	enum CameraState {
		cameraDefault = 1,
		lookAtOrigin,
		lookAtCube1,
		lookAtCube2,
		turnToCube1,
		turnToCube2
	} m_cameraState;

	XTime timer;
	float timeBetweenFrames;

	ComPtr<ID3D11Device>				m_device;
	ComPtr<ID3D11DeviceContext>			m_imedContext;
	ComPtr<IDXGISwapChain>				m_swapChain;
	ComPtr<ID3D11Buffer>				m_constantBuffer;
	D3D11_VIEWPORT						m_viewport;

	float radians;

	bool mouseMove;
	POINT prevCursorPos;
	POINT currCursorPos;

	ModelViewProjectionConstantBuffer m_constantBufferData;

	bool LoadCompiledShaderData(char **byteCode, size_t &byteCodeSize, const char *fileName);

	void InitViewport(D3D11_VIEWPORT& _viewport);
	void InitDepthBuffer(ComPtr<ID3D11Texture2D>& _depthBuffer);
	void InitDepthState(ComPtr<ID3D11DepthStencilState>& _depthState);
	void InitDepthView(ComPtr<ID3D11DepthStencilView>& _depthView);
	void InitRasterState(ComPtr<ID3D11RasterizerState>& _rasterState);
	void InitConstantBuffer(ComPtr<ID3D11Buffer>& _buffer);
	void InitShadersAndInputLayout(ComPtr<ID3D11PixelShader>& _PS, ComPtr<ID3D11VertexShader>& _VS, ComPtr<ID3D11InputLayout>& _IL);

	void CreateWindowResources(HWND& _hWnd);

	void Update(void);
	void Render(void);

	void UpdateConstantBuffer(XMMATRIX _modelsMatrix);

	//bool ReadInBinaryMeshFile(Object& _fillOutObject);
	//bool ReadInAdvancedBinaryMeshFile(const char* _fileName, Object& _fillOutObject);
	
	void SetPipelineStates(PipelineState& _pS);
	void CheckUserInput(WPARAM wParam);
	void RunTaskList(HWND& _hWnd);
	//void RunDebugMessage(void);
	
	bool RunFbxLoader(void);
	bool RunTaskForPPV(void);
	bool RunTaskForAdvancedMesh(void);
};