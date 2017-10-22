#pragma once
/***************************
* Filename: SceneManager.h
***************************/
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

/***************************
* INCLUDES
***************************/
#include "IncludesBJF.h"
#include "D3DInitializer.h"
#include "DebugRenderer.h"
#include "Terrain.h"
#include "Object.h"
#include "Camera.h"
#include "FbxLibraryDLLMeshHandler.h"
#include "FbxLibraryDLLMaterialHandler.h"

#include "XTime.h"

#include <fstream>
#include <vector>
#include "resource.h"
#include "WICTextureLoader.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

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
private:
	Object*							myCube;
	Object*							myAdvancedMesh;
	Camera*							myCamera;
	Terrain*						myTerrain;
	DebugRenderer*					myDebugRenderer;
	D3DInitializer*					myD3DClass;
	FbxLibraryDLLMaterialHandler*	myMaterialHandler;
	FbxLibraryDLLMeshHandler*		myMeshHandler;
public:
	struct PPVStuff {
		std::vector<ID3D11ShaderResourceView*> m_materialsSRVs;
		ComPtr<ID3D11PixelShader> m_PS;
		ComPtr<ID3D11VertexShader> m_VS;
		ComPtr<ID3D11InputLayout> m_IL;
		~PPVStuff();
	} m_PPVStuff, m_AdvancedMeshStuff;

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

	ComPtr<ID3D11Buffer>				m_constantBuffer;

	bool mouseMove;
	POINT prevCursorPos;
	POINT currCursorPos;

	ModelViewProjectionConstantBuffer m_constantBufferData;

	bool LoadCompiledShaderData(char **byteCode, size_t &byteCodeSize, const char *fileName);

	void InitConstantBuffer(ComPtr<ID3D11Buffer>& _buffer);
	void InitShadersAndInputLayout(ComPtr<ID3D11PixelShader>& _PS, ComPtr<ID3D11VertexShader>& _VS, ComPtr<ID3D11InputLayout>& _IL);

	void Update(void);
	void Render(void);

	void UpdateConstantBuffer(XMMATRIX _modelsMatrix);

	void SetPipelineStates(PipelineState& _pS);
	void CheckUserInput(WPARAM wParam);
	void RunTaskList(int _screenWidth, int _screenHeight, bool _vsync, HWND& _hwnd, bool _fullscreen, float _screenFar, float _screenNear);
	void RunDebugMessage(void);
	
	bool RunTaskForPPV(void);

	void RunDebuggerTask(void);
};

#endif //!_SCENEMANAGER_H_