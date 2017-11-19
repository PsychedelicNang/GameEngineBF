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
#include "ParticleSystem.h"
#include "FPSInformation.h"
#include "CPUInformation.h"

// Time
#include "XTime.h"

//Utility
#include <fstream>
#include <vector>
#include "resource.h"
#include "WICTextureLoader.h"
#include <iostream>
#include "../Gateware Middleware/Interface/G_System/GInput.h"

// Memory leak detection
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

class SceneManager {
public:
	SceneManager();
	~SceneManager();

private:
	const bool FULL_SCREEN = false;
	const bool VSYNC_ENABLED = true;
	const float SCREEN_FAR = 1000.0f;
	const float SCREEN_NEAR = 0.1f;

	bool m_libraryLoadedMaterial;
	bool m_libraryLoadedMesh;
	bool m_rotate;
	Object*							myCube;
	Object*							myTeddyBear;
	Object*							myTeddyBearAnim;
	Object*							myBattleMage;
	Camera*							myCamera;
	Terrain*						myTerrain;
	DebugRenderer*					myDebugRenderer;
	D3DInitializer*					myD3DClass;
	FbxLibraryDLLMaterialHandler*	myMaterialHandler;
	FbxLibraryDLLMeshHandler*		myMeshHandler;
	FbxLibraryDLLAnimationHandler*	myAnimationHandler;
	ParticleSystem*					myParticleSystem;
	FPSInformation*					myFPSInformation;
	CPUInformation*					myCPUInformation;

	GW::SYSTEM::GInput*				myGInput;
	XTime m_timer;
	XTime m_animationTimer;
	float m_timeBetweenFrames;
	float m_timeForAnimation;

	ComPtr<ID3D11Buffer>				m_constantBuffer;
	ComPtr<ID3D11Buffer>				m_tessellationConstantBuffer;
	ComPtr<ID3D11Buffer>				m_tessellationQuadConstantBuffer;
	ComPtr<ID3D11SamplerState>			m_samplerState;

	AnimationComponents::AnimationClip animClip;
	std::vector<AnimationComponents::SkeletonJoints> skelJoints;
	std::vector<XMMATRIX> m_jointMatrices;
	std::vector<XMMATRIX> m_bindPoseMatrices;
	XMMATRIX m_bindPoseMatrix;
	AnimationComponents::BindPose bindPose;
	std::vector<XMMATRIX> m_jointsForFrameToPresent;
	bool freeRun;

	ComPtr<ID3D11Buffer>				m_skinnedAnimationConstantBuffer;
	struct SkinnedTransforms {
		//DirectX::XMFLOAT4X4 transforms[37];
		//DirectX::XMMATRIX* transforms;
		DirectX::XMMATRIX transforms[37];
	} m_SkinnedTransforms;

	int animationFrame;
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
	} m_defaultPipeline, m_particlePipeline;

	struct TessellationStuff {
		ComPtr<ID3D11InputLayout>	inputLayout;
		ComPtr<ID3D11VertexShader>	vertexShader;
		ComPtr<ID3D11PixelShader>	pixelShader;
		ComPtr<ID3D11HullShader>	hullShader;
		ComPtr<ID3D11DomainShader>  domainShader;
		ComPtr<ID3D11Buffer>		m_quadVertexBuffer;
		ComPtr<ID3D11Buffer>		m_modelCameraConstantBuffer;

		struct ModelCameraConstantBuffer {
			XMFLOAT4 cameraPos;
			XMFLOAT4X4 model;
		} m_modelCameraConstantBufferData;
	} m_tessellationStuff, m_tessellationQuad;

	struct PPVStuff {
		std::vector<ID3D11ShaderResourceView*> m_materialsSRVs;
		ComPtr<ID3D11PixelShader> m_PS;
		ComPtr<ID3D11VertexShader> m_VS;
		ComPtr<ID3D11InputLayout> m_IL;
		~PPVStuff();
	} m_PPVStuff, m_PPVBattleMage, m_PPVSkinnedAnimation;

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
	ModelViewProjectionConstantBuffer m_tessellationQuadConstantBufferData;

public:
	void Initialize(int _screenWidth, int _screenHeight, HWND _hWnd);
	void Update(void);
	void Render(void);

	// Checks user input for non toggling events
	void CheckUserInput();

	// Checks user input for toggling events
	void CheckUserInput(WPARAM _wParam);

	// Checks windows messages such as a key press or mouse movement
	void CheckWindowsMessage(UINT _message, HWND _hWnd);

	void RunTaskList(int _screenWidth, int _screenHeight, bool _vsync, HWND& _hwnd, bool _fullscreen, float _screenFar, float _screenNear);
	float GetTimeBetweenFrames();
	Camera* GetCamera();

	void RunDebugMessage(void);

private:
	void InitializeClass(int _screenWidth, int _screenHeight, HWND _hWnd);
	void InitializeConstantBuffer(ComPtr<ID3D11Buffer>& _buffer);
	void InitializeShadersAndInputLayout(ComPtr<ID3D11PixelShader>& _PS, ComPtr<ID3D11VertexShader>& _VS, ComPtr<ID3D11InputLayout>& _IL);
	void InitializeSamplerState(ComPtr<ID3D11SamplerState>& _samplerState);

	bool LoadCompiledShaderData(char **byteCode, size_t &byteCodeSize, const char *fileName);
	void UpdateStandardConstantBuffer(XMMATRIX _modelsMatrix);
	void UpdateTessellationConstantBuffer(void);
	void SetPipelineStates(PipelineState& _pS);

	bool RunTaskForPPV(void);
	void RunDebuggerTask(void);
	void Tessellation(void);

	void TessellationQuad(void);
	void UpdateTessellationQuadConstantBuffer(void);

	void PlayAnimation(void);

	void ParticleSystemStuff(void);
};

#endif //!_SCENEMANAGER_H_