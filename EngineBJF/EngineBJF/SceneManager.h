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
#include "FbxLibraryDLLAnimationHandler.h"

#include "XTime.h"

#include <fstream>
#include <vector>
#include "resource.h"
#include "WICTextureLoader.h"
#include <iostream>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

class SceneManager {
public:
	SceneManager();
	~SceneManager();

private:
	bool m_libraryLoadedMaterial;
	bool m_libraryLoadedMesh;
	Object*							myCube;
	Object*							myAdvancedMesh;
	Camera*							myCamera;
	Terrain*						myTerrain;
	DebugRenderer*					myDebugRenderer;
	D3DInitializer*					myD3DClass;
	FbxLibraryDLLMaterialHandler*	myMaterialHandler;
	FbxLibraryDLLMeshHandler*		myMeshHandler;
	FbxLibraryDLLAnimationHandler*	myAnimationHandler;
	GW::SYSTEM::GInput*				myGInput;
	bool m_rotate;
	XTime m_timer;
	float m_timeBetweenFrames;

	ComPtr<ID3D11Buffer>				m_constantBuffer;
	ComPtr<ID3D11Buffer>				m_tessellationConstantBuffer;
	ComPtr<ID3D11SamplerState>			m_samplerState;

	struct PipelineState
	{
		ComPtr<ID3D11InputLayout>			input_layout;
		ComPtr<ID3D11VertexShader>			vertex_shader;
		ComPtr<ID3D11PixelShader>			pixel_shader;
		/*ComPtr<ID3D11RenderTargetView>	render_target;
		ComPtr<ID3D11Texture2D>				depthStencilBuffer;
		ComPtr<ID3D11DepthStencilState>		depthStencilState;
		ComPtr<ID3D11DepthStencilView>		depthStencilView;
		ComPtr<ID3D11RasterizerState>		rasterState;*/
	} m_defaultPipeline;

	struct TessellationStuff {
		ComPtr<ID3D11InputLayout>	inputLayout;
		ComPtr<ID3D11VertexShader>	vertexShader;
		ComPtr<ID3D11PixelShader>	pixelShader;
		ComPtr<ID3D11HullShader>	hullShader;
		ComPtr<ID3D11DomainShader>  domainShader;
		ComPtr<ID3D11Buffer> m_quadVertexBuffer;
		ComPtr<ID3D11Buffer> m_modelCameraConstantBuffer;

		struct ModelCameraConstantBuffer {
			XMFLOAT4 cameraPos;
			XMFLOAT4X4 model;
		} m_modelCameraConstantBufferData;
	} m_tessellationStuff;

	struct PPVStuff {
		std::vector<ID3D11ShaderResourceView*> m_materialsSRVs;
		ComPtr<ID3D11PixelShader> m_PS;
		ComPtr<ID3D11VertexShader> m_VS;
		ComPtr<ID3D11InputLayout> m_IL;
		~PPVStuff();
	} m_PPVStuff;

public:
	void Update(void);
	void Render(void);

	void CheckUserInput();
	void RunTaskList(int _screenWidth, int _screenHeight, bool _vsync, HWND& _hwnd, bool _fullscreen, float _screenFar, float _screenNear);
	float GetTimeBetweenFrames();
	Camera* GetCamera();

	void RunDebugMessage(void);

public:
	enum CameraState {
		cameraDefault = 1,
		lookAtOrigin,
		lookAtCube,
		lookAtMesh,
		turnToCube,
		turnToMesh
	} m_cameraState;

	bool mouseMove;
	POINT prevCursorPos;
	POINT currCursorPos;

	ModelViewProjectionConstantBuffer m_constantBufferData;
	ModelViewProjectionConstantBuffer m_tessellationConstantBufferData;

private:
	void InitConstantBuffer(ComPtr<ID3D11Buffer>& _buffer);
	void InitShadersAndInputLayout(ComPtr<ID3D11PixelShader>& _PS, ComPtr<ID3D11VertexShader>& _VS, ComPtr<ID3D11InputLayout>& _IL);

	bool LoadCompiledShaderData(char **byteCode, size_t &byteCodeSize, const char *fileName);
	void UpdateStandardConstantBuffer(XMMATRIX _modelsMatrix);
	void UpdateTessellationConstantBuffer(void);
	void SetPipelineStates(PipelineState& _pS);

	bool RunTaskForPPV(void);
	void RunDebuggerTask(void);
	void Tessellation(void);
};

#endif //!_SCENEMANAGER_H_