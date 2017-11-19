#include "SceneManager.h"

SceneManager::SceneManager()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(272);
	m_libraryLoadedMaterial = false;
	m_libraryLoadedMesh = false;
	myCube				= new Object();
	myCamera			= new Camera();
	myTerrain			= new Terrain();
	myDebugRenderer		= new DebugRenderer();
	myD3DClass			= new D3DInitializer();
	myTeddyBear			= new Object();
	myTeddyBearAnim		= new Object();
	myBattleMage		= new Object();
	myMaterialHandler	= new FbxLibraryDLLMaterialHandler();
	myMeshHandler		= new FbxLibraryDLLMeshHandler();
	myAnimationHandler	= new FbxLibraryDLLAnimationHandler();
	myParticleSystem	= new ParticleSystem();
	mouseMove = false;
	m_rotate = false;
	m_cameraState = cameraDefault;
	m_timeBetweenFrames = 0.f;
	m_timer.Restart();
	m_animationTimer.Restart();
	animationFrame = 0;
	m_timeForAnimation = 0;
	freeRun = true;
	// Decrement count of GInput
}

SceneManager::~SceneManager()
{
	if (myCube) delete myCube;
	if (myCamera) delete myCamera;
	if (myTerrain) delete myTerrain;
	if (myDebugRenderer) delete myDebugRenderer;
	if (myD3DClass) delete myD3DClass;
	if (myTeddyBear) delete myTeddyBear;
	if (myTeddyBearAnim) delete myTeddyBearAnim;
	if (myBattleMage) delete myBattleMage;
	if (myMaterialHandler) delete myMaterialHandler;
	if (myMeshHandler) delete myMeshHandler;
	if (myAnimationHandler) delete myAnimationHandler;
	if (myGInput) 	myGInput->DecrementCount();
	if (myParticleSystem) delete myParticleSystem;
}

void SceneManager::Initialize(int _screenWidth, int _screenHeight, HWND _hWnd)
{
	InitializeClass(_screenWidth, _screenHeight, _hWnd);
}

void SceneManager::InitializeClass(int _screenWidth, int _screenHeight, HWND _hWnd)
{
	GetCursorPos(&prevCursorPos);
	ScreenToClient(_hWnd, &prevCursorPos);
	RunTaskList(_screenWidth, _screenHeight, VSYNC_ENABLED, _hWnd, FULL_SCREEN, SCREEN_FAR, SCREEN_NEAR);
}

void SceneManager::InitializeConstantBuffer(ComPtr<ID3D11Buffer>& _buffer)
{
	CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ModelViewProjectionConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
	myD3DClass->GetDevice()->CreateBuffer(&constantBufferDesc, nullptr, _buffer.GetAddressOf());
}

void SceneManager::InitializeShadersAndInputLayout(ComPtr<ID3D11PixelShader>& _PS, ComPtr<ID3D11VertexShader>& _VS, ComPtr<ID3D11InputLayout>& _IL)
{
	char* bytecode = nullptr;
	size_t byteCodeSize = 0;
	LoadCompiledShaderData(&bytecode, byteCodeSize, "Shaders/Pixel Shaders/PS_Standard.cso");
	myD3DClass->GetDevice()->CreatePixelShader(bytecode, byteCodeSize, nullptr, _PS.GetAddressOf());
	delete[] bytecode;

	char* bytecode2 = nullptr;
	size_t byteCodeSize2 = 0;
	LoadCompiledShaderData(&bytecode2, byteCodeSize2, "Shaders/Vertex Shaders/VS_Standard.cso");
	myD3DClass->GetDevice()->CreateVertexShader(bytecode2, byteCodeSize2, nullptr, _VS.GetAddressOf());
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	HRESULT hr = myD3DClass->GetDevice()->CreateInputLayout(vertexDesc, ARRAYSIZE(vertexDesc), bytecode2, byteCodeSize2, _IL.GetAddressOf());
	delete[] bytecode2;
}

void SceneManager::InitializeSamplerState(ComPtr<ID3D11SamplerState>& _samplerState)
{
	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.MinLOD = -3.402823466e+38F;
	samplerDesc.MaxLOD = 3.402823466e+38F;
	samplerDesc.MipLODBias = 0.f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;

	myD3DClass->GetDevice()->CreateSamplerState(&samplerDesc, _samplerState.GetAddressOf());
}

void SceneManager::SetPipelineStates(PipelineState& _pipeState)
{
	myD3DClass->GetDeviceContext()->IASetInputLayout(_pipeState.input_layout.Get());
	myD3DClass->GetDeviceContext()->VSSetShader(_pipeState.vertex_shader.Get(), NULL, 0);
	myD3DClass->GetDeviceContext()->PSSetShader(_pipeState.pixel_shader.Get(), NULL, 0);
}

void SceneManager::Update(void)
{	
	m_timer.Signal();
	m_animationTimer.Signal();
	m_timeBetweenFrames = (float)m_timer.Delta();
	m_timeForAnimation += (float)m_animationTimer.Delta();
	if (m_timeForAnimation > animClip.frames.back().time)
	{
		m_timeForAnimation = 0;
	}

	myParticleSystem->UpdateFrame(m_timeBetweenFrames, myD3DClass->GetDeviceContext());

	CheckUserInput();
	
	switch (m_cameraState)
	{
		case SceneManager::cameraDefault:
			break;
		case SceneManager::lookAtOrigin:
		{
			XMVECTOR at = { 0.f, 0.f, 0.f, 1.f };
			XMVECTOR up = { 0.f, 1.f, 0.f, 1.f };
			myCamera->SetCamera(myCamera->CameraLookAt(myCamera->GetCameraMatrix().r[3], at, up));
		}
		break;
		case SceneManager::lookAtCube:
		{
			XMVECTOR up = { 0.f, 1.f, 0.f, 1.f };
			myCamera->SetCamera(myCamera->CameraLookAt(myCamera->GetCameraMatrix().r[3], myCube->GetObjectMatrix().r[3], up));
		}
			break;
		case SceneManager::lookAtMesh:
		{
			XMVECTOR up = { 0.f, 1.f, 0.f, 1.f };
			myCamera->SetCamera(myCamera->CameraLookAt(myCamera->GetCameraMatrix().r[3], myTeddyBear->GetObjectMatrix().r[3], up));
		}
			break;
		case SceneManager::turnToCube:
			myCamera->SetCamera(myCamera->CameraTurnTo(myCamera->GetCameraMatrix(), myCube->GetObjectMatrix().r[3], m_timeBetweenFrames * 20.f));
			break;
		case SceneManager::turnToMesh:
			myCamera->SetCamera(myCamera->CameraTurnTo(myCamera->GetCameraMatrix(), myTeddyBear->GetObjectMatrix().r[3], m_timeBetweenFrames * 20.f));
			break;
		default:
			break;
	}

	if (m_rotate)
	{
		myCube->ObjectRotationY(0.50f * m_timeBetweenFrames);
		myTeddyBear->ObjectRotationY(0.5f * m_timeBetweenFrames);
		myBattleMage->ObjectRotationY(0.5f * m_timeBetweenFrames);
	}

	myCamera->CreateViewAndPerspectiveMatrix();
}

void SceneManager::Render(void)
{
	float RGBA[4] = { .2f, .5f, 1.f, 1.f };
	//float RGBA[4] = { 0.f, 0.f, 0.f, 1.f };

	myD3DClass->BeginScene(RGBA);

	ComPtr<ID3D11DeviceContext> m_deviceContext = myD3DClass->GetDeviceContext();
	ComPtr<ID3D11Device> m_device = myD3DClass->GetDevice();		
#if 1
	if (m_libraryLoadedMesh && m_libraryLoadedMesh)
	{
		m_deviceContext->IASetInputLayout(m_PPVBattleMage.m_IL.Get());
		m_deviceContext->VSSetShader(m_PPVBattleMage.m_VS.Get(), NULL, 0);
		m_deviceContext->PSSetShader(m_PPVBattleMage.m_PS.Get(), NULL, 0);
		m_deviceContext->PSSetSamplers(0, 1, m_samplerState.GetAddressOf());
		m_deviceContext->PSSetShaderResources(0, 1, &m_PPVBattleMage.m_materialsSRVs.data()[1]);	// 1, 0, 3 because of the input from shaders... diffuse, emissive, specular
		m_deviceContext->PSSetShaderResources(1, 1, &m_PPVBattleMage.m_materialsSRVs.data()[0]);	// Skip [2] because we are not using normal mapping right now
		m_deviceContext->PSSetShaderResources(2, 1, &m_PPVBattleMage.m_materialsSRVs.data()[3]);
		UpdateStandardConstantBuffer(myCube->GetObjectMatrix());
		myCube->Render(m_deviceContext);

		UpdateStandardConstantBuffer(myBattleMage->GetObjectMatrix());
		myBattleMage->Render(m_deviceContext);

		UpdateStandardConstantBuffer(myTeddyBear->GetObjectMatrix());
		m_deviceContext->PSSetShaderResources(0, 1, &m_PPVStuff.m_materialsSRVs.data()[0]);
		m_deviceContext->PSSetShaderResources(1, 1, &m_PPVStuff.m_materialsSRVs.data()[0]);
		//m_deviceContext->PSSetShaderResources(2, 1, &m_PPVStuff.m_materialsSRVs.data()[0]);
		myTeddyBear->Render(m_deviceContext);

		/**********************Skeleton Animation**********************/
		SetPipelineStates(m_defaultPipeline);
		UpdateStandardConstantBuffer(XMMatrixIdentity());
		PlayAnimation();
		myDebugRenderer->CreateVertexBuffer(m_device);
		myDebugRenderer->Render(m_device, m_deviceContext);
		/**********************Skeleton Animation**********************/


		/**********************Skinned Animation**********************/
		//Float4x4 joints_for_vs[NumJoints]
		//for i = 0; i < NumJoints; ++i        
		//	joints_for_vs[i] = multiply(invBind[i], tweenJoint[i])
		//upload_joints_to_gpu(joints_for_vs)

		size_t numberOfJoints = m_jointsForFrameToPresent.size();
		//m_SkinnedTransforms.transforms = new XMMATRIX[numberOfJoints];
		for (size_t i = 0; i < numberOfJoints; i++)
		{
			m_SkinnedTransforms.transforms[i] = XMMatrixMultiply(XMMatrixInverse(nullptr, m_bindPoseMatrices[i]), m_jointsForFrameToPresent[i]);
		}

		CD3D11_BUFFER_DESC constantBufferDesc(sizeof(SkinnedTransforms), D3D11_BIND_CONSTANT_BUFFER);
		myD3DClass->GetDevice()->CreateBuffer(&constantBufferDesc, nullptr, m_skinnedAnimationConstantBuffer.GetAddressOf());

		UpdateStandardConstantBuffer(myTeddyBearAnim->GetObjectMatrix());
		myD3DClass->GetDeviceContext()->UpdateSubresource(m_skinnedAnimationConstantBuffer.Get(), 0, NULL, &m_SkinnedTransforms, 0, 0);
		myD3DClass->GetDeviceContext()->VSSetConstantBuffers(1, 1, m_skinnedAnimationConstantBuffer.GetAddressOf());

		m_deviceContext->IASetInputLayout(m_PPVSkinnedAnimation.m_IL.Get());
		m_deviceContext->VSSetShader(m_PPVSkinnedAnimation.m_VS.Get(), NULL, 0);
		m_deviceContext->PSSetShader(m_PPVSkinnedAnimation.m_PS.Get(), NULL, 0);
		m_deviceContext->PSSetSamplers(0, 1, m_samplerState.GetAddressOf());
		m_deviceContext->PSSetShaderResources(0, 1, &m_PPVStuff.m_materialsSRVs.data()[0]);
		//m_deviceContext->PSSetShaderResources(1, 1, &m_PPVStuff.m_materialsSRVs.data()[0]);
		myTeddyBearAnim->Render(m_deviceContext);

		m_skinnedAnimationConstantBuffer.Reset();
		/**********************Skinned Animation**********************/
	}
	
	SetPipelineStates(m_defaultPipeline);
	UpdateStandardConstantBuffer(XMMatrixIdentity());
	myTerrain->Render(m_deviceContext);

	/********************Tessellation******************************/
	m_deviceContext->IASetInputLayout(m_tessellationStuff.inputLayout.Get());
	
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST);
	UINT stride = sizeof(VertexPositionColor);
	UINT offset = 0;
	
	UpdateTessellationConstantBuffer();
	m_deviceContext->IASetVertexBuffers(0, 1, m_tessellationStuff.m_quadVertexBuffer.GetAddressOf(), &stride, &offset);
	m_deviceContext->VSSetShader(m_tessellationStuff.vertexShader.Get(), NULL, 0);
	m_deviceContext->PSSetShader(m_tessellationStuff.pixelShader.Get(), NULL, 0);
	m_deviceContext->HSSetShader(m_tessellationStuff.hullShader.Get(), NULL, 0);
	m_deviceContext->DSSetShader(m_tessellationStuff.domainShader.Get(), NULL, 0);
	
	m_deviceContext->Draw(3, 0);
	m_deviceContext->HSSetShader(NULL, NULL, 0);
	m_deviceContext->DSSetShader(NULL, NULL, 0);
	/********************Tessellation******************************/

	/********************TessellationQuad******************************/
	//m_deviceContext->IASetInputLayout(m_tessellationQuad.inputLayout.Get());
	//
	//m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);
	//UINT stride = sizeof(VertexPositionColor);
	//UINT offset = 0;
	//
	//UpdateTessellationQuadConstantBuffer();
	//m_deviceContext->IASetVertexBuffers(0, 1, m_tessellationQuad.m_quadVertexBuffer.GetAddressOf(), &stride, &offset);
	//m_deviceContext->VSSetShader(m_tessellationQuad.vertexShader.Get(), NULL, 0);
	//m_deviceContext->PSSetShader(m_tessellationQuad.pixelShader.Get(), NULL, 0);
	//m_deviceContext->HSSetShader(m_tessellationQuad.hullShader.Get(), NULL, 0);
	//m_deviceContext->DSSetShader(m_tessellationQuad.domainShader.Get(), NULL, 0);
	//
	//m_deviceContext->Draw(4, 0);
	//m_deviceContext->HSSetShader(NULL, NULL, 0);
	//m_deviceContext->DSSetShader(NULL, NULL, 0);
	/********************TessellationQuad******************************/


	myD3DClass->EnableAlphaBlending();
	m_deviceContext->IASetInputLayout(m_particlePipeline.input_layout.Get());
	m_deviceContext->VSSetShader(m_particlePipeline.vertex_shader.Get(), NULL, 0);
	m_deviceContext->PSSetShader(m_particlePipeline.pixel_shader.Get(), NULL, 0);
	m_deviceContext->PSSetSamplers(0, 1, m_samplerState.GetAddressOf());
	XMMATRIX particleModel = XMMatrixTranslation(2.f, 3.f, 3.f);
	UpdateStandardConstantBuffer(particleModel);
	myParticleSystem->Render(m_deviceContext);
	myD3DClass->DisableAlphaBlending();
#endif

	m_deviceContext.Reset();
	m_device.Reset();

	myD3DClass->EndScene();
}

void SceneManager::UpdateStandardConstantBuffer(XMMATRIX _modelsMatrix)
{
	XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(_modelsMatrix));
	XMStoreFloat4x4(&m_constantBufferData.view, XMMatrixTranspose(XMLoadFloat4x4(&myCamera->m_constantBufferData.view)));
	XMStoreFloat4x4(&m_constantBufferData.projection, XMMatrixTranspose(XMLoadFloat4x4(&myCamera->m_constantBufferData.projection)));
	myD3DClass->GetDeviceContext()->UpdateSubresource(m_constantBuffer.Get(), 0, NULL, &m_constantBufferData, 0, 0);
	myD3DClass->GetDeviceContext()->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
}

void SceneManager::UpdateTessellationConstantBuffer(void)
{
	XMMATRIX triangleModel = XMMatrixTranslation(0.f, 0.f, 10.f);
	XMStoreFloat4x4(&m_tessellationStuff.m_modelCameraConstantBufferData.model, XMMatrixTranspose(triangleModel));
	XMVECTOR camPos = myCamera->GetCameraMatrix().r[3];
	m_tessellationStuff.m_modelCameraConstantBufferData.cameraPos = XMFLOAT4(camPos.m128_f32[0], camPos.m128_f32[1], camPos.m128_f32[2], camPos.m128_f32[3]);

	myD3DClass->GetDeviceContext()->UpdateSubresource(m_tessellationStuff.m_modelCameraConstantBuffer.Get(), 0, NULL, &m_tessellationStuff.m_modelCameraConstantBufferData, 0, 0);
	XMStoreFloat4x4(&m_tessellationConstantBufferData.model, XMMatrixTranspose(triangleModel));
	XMStoreFloat4x4(&m_tessellationConstantBufferData.view, XMMatrixTranspose(XMLoadFloat4x4(&myCamera->m_constantBufferData.view)));
	XMStoreFloat4x4(&m_tessellationConstantBufferData.projection, XMMatrixTranspose(XMLoadFloat4x4(&myCamera->m_constantBufferData.projection)));
	myD3DClass->GetDeviceContext()->UpdateSubresource(m_tessellationConstantBuffer.Get(), 0, NULL, &m_tessellationConstantBufferData, 0, 0);

	myD3DClass->GetDeviceContext()->HSSetConstantBuffers(1, 1, m_tessellationStuff.m_modelCameraConstantBuffer.GetAddressOf());
	myD3DClass->GetDeviceContext()->DSSetConstantBuffers(2, 1, m_tessellationConstantBuffer.GetAddressOf());
}

void SceneManager::UpdateTessellationQuadConstantBuffer(void)
{
	XMMATRIX quadModel = XMMatrixTranslation(0.f, 0.f, 20.f);
	XMStoreFloat4x4(&m_tessellationQuad.m_modelCameraConstantBufferData.model, XMMatrixTranspose(quadModel));
	XMVECTOR camPos = myCamera->GetCameraMatrix().r[3];
	m_tessellationQuad.m_modelCameraConstantBufferData.cameraPos = XMFLOAT4(camPos.m128_f32[0], camPos.m128_f32[1], camPos.m128_f32[2], camPos.m128_f32[3]);

	myD3DClass->GetDeviceContext()->UpdateSubresource(m_tessellationQuad.m_modelCameraConstantBuffer.Get(), 0, NULL, &m_tessellationQuad.m_modelCameraConstantBufferData, 0, 0);
	XMStoreFloat4x4(&m_tessellationQuadConstantBufferData.model, XMMatrixTranspose(quadModel));
	XMStoreFloat4x4(&m_tessellationQuadConstantBufferData.view, XMMatrixTranspose(XMLoadFloat4x4(&myCamera->m_constantBufferData.view)));
	XMStoreFloat4x4(&m_tessellationQuadConstantBufferData.projection, XMMatrixTranspose(XMLoadFloat4x4(&myCamera->m_constantBufferData.projection)));
	myD3DClass->GetDeviceContext()->UpdateSubresource(m_tessellationQuadConstantBuffer.Get(), 0, NULL, &m_tessellationQuadConstantBufferData, 0, 0);

	myD3DClass->GetDeviceContext()->HSSetConstantBuffers(1, 1, m_tessellationQuad.m_modelCameraConstantBuffer.GetAddressOf());
	myD3DClass->GetDeviceContext()->DSSetConstantBuffers(2, 1, m_tessellationQuadConstantBuffer.GetAddressOf());
}

bool SceneManager::LoadCompiledShaderData(char **byteCode, size_t &byteCodeSize, const char *fileName)
{
	std::ifstream load;
	load.open(fileName, std::ios_base::binary);
	if (!load.is_open()) return false;
	load.seekg(0, std::ios_base::end);
	byteCodeSize = size_t(load.tellg());
	*byteCode = new char[byteCodeSize];
	load.seekg(0, std::ios_base::beg);
	load.read(*byteCode, byteCodeSize);
	load.close();

	return true;
}

void SceneManager::RunTaskList(int _screenWidth, int _screenHeight, bool _vsync, HWND& _hwnd, bool _fullscreen, float _screenFar, float _screenNear)
{
	myD3DClass->Initialize(_screenWidth, _screenHeight, _vsync, _hwnd, _fullscreen, _screenFar, _screenNear);
	GW::SYSTEM::CreateGInput(_hwnd, sizeof(_hwnd), &myGInput);
	InitializeConstantBuffer(m_constantBuffer);
	InitializeShadersAndInputLayout(m_defaultPipeline.pixel_shader, m_defaultPipeline.vertex_shader, m_defaultPipeline.input_layout);
	InitializeSamplerState(m_samplerState);
	ParticleSystemStuff();
	float m_viewportWidth = 1024;
	float m_viewportHeight = 768;
	float m_cameraZoom = 70.0f;
	float m_nearPlane = 0.1f;
	float m_farPlane = 10000.0f;
	XMVECTOR eye = { 3.0f, 3.f, -5.f, 1.0f };
	XMVECTOR at = { 3.0f, 3.f, 0.f, 1.0f };
	XMVECTOR up = { 0.0f, 1.0f, 0.0f, 1.0f };
	myCamera->Initialize(m_viewportWidth, m_viewportHeight, m_nearPlane, m_farPlane, m_cameraZoom, eye, at, up);
	//myCamera->Initialize();

	myCube->Initialize(myD3DClass->GetDevice());
	myTerrain->Initialize(myD3DClass->GetDevice());
	RunTaskForPPV();

	m_libraryLoadedMesh = myMeshHandler->Initialize();

	//if (myAnimationHandler->Initialize())	myAnimationHandler->LoadAnimationFBX("Teddy/Teddy_Run.fbx", animClip, skelJoints, 0.02f);
	myAnimationHandler->Initialize();
	std::vector<MeshComponentsAdvanced::OutInformationAdvanced> meshes;
	if (m_libraryLoadedMesh) m_libraryLoadedMesh = myMeshHandler->LoadAdvancedMeshFBX("BattleMage.fbx", meshes);
	if (m_libraryLoadedMesh) myMeshHandler->ExportAdvancedMesh("BattleMageAdv.bin", meshes[0]);
	if (m_libraryLoadedMesh) m_libraryLoadedMesh = myBattleMage->ReadInAdvancedMeshFromBinaryFile(myD3DClass->GetDevice(), "BattleMageAdv.bin");

	std::vector<MeshComponentsAdvanced::OutInformationAdvanced> meshes2;
	if (m_libraryLoadedMesh) m_libraryLoadedMesh = myMeshHandler->LoadAdvancedMeshFBX("Teddy/Teddy_Run.fbx", meshes2);
	if (m_libraryLoadedMesh) myMeshHandler->ExportAdvancedMesh("Teddy/Teddy_Run.bin", meshes2[0]);
	if (m_libraryLoadedMesh) m_libraryLoadedMesh = myTeddyBear->ReadInAdvancedMeshFromBinaryFile(myD3DClass->GetDevice(), "Teddy/Teddy_Run.bin", 0.02f);

	std::vector<MeshComponentsAnimation::OutInformationAdvanced> meshes3;
	
	//if (m_libraryLoadedMesh) m_libraryLoadedMesh = myMeshHandler->LoadAdvancedMeshWithSkinnedAnimationFBX("Teddy/Teddy_Run.fbx", meshes3);
	bool test = myAnimationHandler->LoadFBX("Teddy/Teddy_Run.fbx", meshes3, bindPose, animClip, skelJoints, 0.02f);
	if (m_libraryLoadedMesh) myMeshHandler->ExportAdvancedMeshWithSkinnedAnimationBinary("Teddy/Teddy_Run_Skinned.bin", meshes3[0]);
	if (m_libraryLoadedMesh) m_libraryLoadedMesh = myTeddyBearAnim->ReadInAdvancedMeshWithSkinnedAnimationFromBinaryFile(myD3DClass->GetDevice(), "Teddy/Teddy_Run_Skinned.bin", 0.02f);
	
	for (size_t i = 0; i < skelJoints.size(); i++)
	{	
		m_jointMatrices.push_back(XMMATRIX(skelJoints[i].globalTransformArray));
		//m_bindPoseMatrices.push_back(XMMATRIX(animClip.frames[0].joints[i].globalTransformArray));
		m_bindPoseMatrices.push_back(XMMATRIX(bindPose.joints[i].globalTransformArray));
	}
	m_bindPoseMatrix = XMMATRIX(skelJoints[0].globalTransformArray);
	//animClip.frames[0].joints

	myTeddyBear->ObjectChangePosition(-3.f, -2.f, -5.f);
	myBattleMage->ObjectChangePosition(0.f, -2.f, -5.f);
	Tessellation();
	//TessellationQuad();
}

float SceneManager::GetTimeBetweenFrames()
{
	return m_timeBetweenFrames;
}

Camera * SceneManager::GetCamera()
{
	return myCamera;
}

// Checks user input for non toggling events
void SceneManager::CheckUserInput()
{
	float returnValue;

	myGInput->GetState(G_KEY_A, returnValue);
	if (returnValue) {
		myCamera->MoveCameraLocalLeft(m_timeBetweenFrames, 20.f);
	}

	myGInput->GetState(G_KEY_D, returnValue);
	if (returnValue) {
		myCamera->MoveCameraLocalRight(m_timeBetweenFrames, 20.f);
	}

	myGInput->GetState(G_KEY_W, returnValue);
	if (returnValue) {
		myCamera->MoveCameraLocalForward(m_timeBetweenFrames, 20.f);
	}

	myGInput->GetState(G_KEY_S, returnValue);
	if (returnValue) {
		myCamera->MoveCameraLocalBackward(m_timeBetweenFrames, 20.f);
	}

	myGInput->GetState(G_KEY_SPACE, returnValue);
	if (returnValue) {
		myCamera->MoveCameraLocalUp(m_timeBetweenFrames, 20.f);
	}

	myGInput->GetState(G_KEY_X, returnValue);
	if (returnValue) {
		myCamera->MoveCameraLocalDown(m_timeBetweenFrames, 20.f);
	}
}

// Checks user input for toggling events
void SceneManager::CheckUserInput(WPARAM _wParam)
{
	switch (_wParam)
	{
	case VK_UP:
		if (!freeRun)
		{
			if (animationFrame < animClip.frames.size() - 1) animationFrame++;
			else if (animationFrame >= animClip.frames.size() - 1) animationFrame = 0;
		}
		break;
	case VK_DOWN:
		if (!freeRun)
		{
			if (animationFrame > 0) animationFrame--;
			else if (animationFrame < 0) animationFrame = 0;
		}
		break;
	case '1':
		freeRun = true;
		break;
	case '2':
		freeRun = false;
		break;
	case 'P':
		m_cameraState = cameraDefault;
		break;
	case 'T':
		m_cameraState = turnToCube;
		break;
	case 'Y':
		m_cameraState = turnToMesh;
		break;
	case 'K':
		m_cameraState = lookAtCube;
		break;
	case 'L':
		m_cameraState = lookAtMesh;
		break;
	case 'O':
		m_cameraState = lookAtOrigin;
		break;
	case 'R':
		m_rotate = !m_rotate;
		break;
	case 'N':
		myD3DClass->ReinitializeRasterizerState(!myD3DClass->GetBackFaceCullingValue(), myD3DClass->GetWireframeValue());
		break;
	case 'M':
		myD3DClass->ReinitializeRasterizerState(myD3DClass->GetBackFaceCullingValue(), !myD3DClass->GetWireframeValue());
		break;
	default:
		break;
	}
}

// Checks windows messages such as a key press or mouse movement
void SceneManager::CheckWindowsMessage(UINT _message, HWND _hWnd)
{
	switch (_message)
	{
	case WM_MOUSEMOVE:
		if (mouseMove)
		{
			GetCursorPos(&currCursorPos);
			ScreenToClient(_hWnd, &currCursorPos);
			GetCamera()->CameraMouseLook(GetCamera()->GetCameraFloat4x4(), (currCursorPos.x - prevCursorPos.x) * m_timeBetweenFrames, (currCursorPos.y - prevCursorPos.y) * m_timeBetweenFrames);
			prevCursorPos = currCursorPos;
		}
		GetCursorPos(&prevCursorPos);
		ScreenToClient(_hWnd, &prevCursorPos);
		break;
	case WM_RBUTTONDOWN:
		mouseMove = true;
		break;
	case WM_RBUTTONUP:
		mouseMove = false;
		break;
	default:
		break;
	}
}

void SceneManager::RunDebugMessage(void)
{
	//printf(myCamera->GetCameraEye().m128_f32[0]);
	std::cout << myCamera->GetCameraFloat4x4()._11 << ", " << myCamera->GetCameraFloat4x4()._12 << ", " << myCamera->GetCameraFloat4x4()._13 << ", " << myCamera->GetCameraFloat4x4()._14 << "\n";
	std::cout << myCamera->GetCameraFloat4x4()._21 << ", " << myCamera->GetCameraFloat4x4()._22 << ", " << myCamera->GetCameraFloat4x4()._23 << ", " << myCamera->GetCameraFloat4x4()._24 << "\n";
	std::cout << myCamera->GetCameraFloat4x4()._31 << ", " << myCamera->GetCameraFloat4x4()._32 << ", " << myCamera->GetCameraFloat4x4()._33 << ", " << myCamera->GetCameraFloat4x4()._34 << "\n";
	std::cout << myCamera->GetCameraFloat4x4()._41 << ", " << myCamera->GetCameraFloat4x4()._42 << ", " << myCamera->GetCameraFloat4x4()._43 << ", " << myCamera->GetCameraFloat4x4()._44 << "\n\n";
}

bool SceneManager::RunTaskForPPV(void)
{
	m_libraryLoadedMaterial = myMaterialHandler->Initialize();

	if (m_libraryLoadedMaterial)
	{
		std::vector<MaterialComponents::Material> m_VecMaterials02;
		bool res = myMaterialHandler->LoadMaterialFBX("Teddy/Teddy_Run.fbx", m_VecMaterials02);

		for each (MaterialComponents::Material mat in m_VecMaterials02)
		{
			for (mat.m_mapPropValuesIter = mat.m_mapPropValues.begin(); mat.m_mapPropValuesIter != mat.m_mapPropValues.end(); ++mat.m_mapPropValuesIter)
			{
				MaterialComponents::Material::properties prop = mat.m_mapPropValuesIter->first;
				MaterialComponents::Material::properties_t prop_t = mat.m_mapPropValuesIter->second;
				if (prop_t.filePath.compare("WasNotGiven") != 0)	// if we have a file path, get the file path
				{
					ID3D11ShaderResourceView * tempSRV;
					std::wstring widestr = std::wstring(prop_t.filePath.begin(), prop_t.filePath.end());
					std::string fpath = std::string("Teddy\\");
					std::wstring wid = std::wstring(fpath.begin(), fpath.end());
					wid += widestr;
					const wchar_t* szName = wid.c_str();
					CreateWICTextureFromFile(myD3DClass->GetDevice().Get(), nullptr, szName, nullptr, &tempSRV, 0);
					m_PPVStuff.m_materialsSRVs.push_back(tempSRV);
				}
			}
		}

		myMaterialHandler->DisplayMaterialPropertiesInText(m_VecMaterials02);
	}

	if (m_libraryLoadedMaterial)
	{
		std::vector<MaterialComponents::Material> m_VecMaterials;
		bool result = myMaterialHandler->LoadMaterialsBinary("BattleMage.bin", m_VecMaterials);

		for each (MaterialComponents::Material mat in m_VecMaterials)
		{
			for (mat.m_mapPropValuesIter = mat.m_mapPropValues.begin(); mat.m_mapPropValuesIter != mat.m_mapPropValues.end(); ++mat.m_mapPropValuesIter)
			{
				MaterialComponents::Material::properties prop = mat.m_mapPropValuesIter->first;
				MaterialComponents::Material::properties_t prop_t = mat.m_mapPropValuesIter->second;
				if (prop_t.filePath.compare("WasNotGiven") != 0)	// if we have a file path, get the file path
				{
					ID3D11ShaderResourceView * tempSRV;
					std::wstring widestr = std::wstring(prop_t.filePath.begin(), prop_t.filePath.end());
					const wchar_t* szName = widestr.c_str();
					CreateWICTextureFromFile(myD3DClass->GetDevice().Get(), nullptr, szName, nullptr, &tempSRV, 0);
					m_PPVBattleMage.m_materialsSRVs.push_back(tempSRV);
				}
			}
		}

		myMaterialHandler->DisplayMaterialPropertiesInText(m_VecMaterials);
	}
	char* bytecode = nullptr;
	size_t byteCodeSize = 0;
	LoadCompiledShaderData(&bytecode, byteCodeSize, "Shaders/Pixel Shaders/PS_Material.cso");
	myD3DClass->GetDevice()->CreatePixelShader(bytecode, byteCodeSize, nullptr, m_PPVStuff.m_PS.GetAddressOf());
	delete[] bytecode;

	char* bytecode2 = nullptr;
	size_t byteCodeSize2 = 0;
	LoadCompiledShaderData(&bytecode2, byteCodeSize2, "Shaders/Vertex Shaders/VS_Material.cso");
	myD3DClass->GetDevice()->CreateVertexShader(bytecode2, byteCodeSize2, nullptr, m_PPVStuff.m_VS.GetAddressOf());

	D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UVS", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "PADDING", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMALS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	HRESULT hr = myD3DClass->GetDevice()->CreateInputLayout(vertexDesc, ARRAYSIZE(vertexDesc), bytecode2, byteCodeSize2, m_PPVStuff.m_IL.GetAddressOf());
	delete[] bytecode2;

	char* bytecode3 = nullptr;
	size_t byteCodeSize3 = 0;
	LoadCompiledShaderData(&bytecode3, byteCodeSize3, "Shaders/Pixel Shaders/PS_Material.cso");
	myD3DClass->GetDevice()->CreatePixelShader(bytecode3, byteCodeSize3, nullptr, m_PPVBattleMage.m_PS.GetAddressOf());
	delete[] bytecode3;

	char* bytecode4 = nullptr;
	size_t byteCodeSize4 = 0;
	LoadCompiledShaderData(&bytecode4, byteCodeSize4, "Shaders/Vertex Shaders/VS_Material.cso");
	myD3DClass->GetDevice()->CreateVertexShader(bytecode4, byteCodeSize4, nullptr, m_PPVBattleMage.m_VS.GetAddressOf());

	D3D11_INPUT_ELEMENT_DESC vertexDesc2[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UVS", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "PADDING", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMALS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	hr = myD3DClass->GetDevice()->CreateInputLayout(vertexDesc2, ARRAYSIZE(vertexDesc2), bytecode4, byteCodeSize4, m_PPVBattleMage.m_IL.GetAddressOf());
	delete[] bytecode4;

	char* bytecode5 = nullptr;
	size_t byteCodeSize5 = 0;
	LoadCompiledShaderData(&bytecode5, byteCodeSize5, "Shaders/Pixel Shaders/PS_SkinnedAnimation.cso");
	myD3DClass->GetDevice()->CreatePixelShader(bytecode5, byteCodeSize5, nullptr, m_PPVSkinnedAnimation.m_PS.GetAddressOf());
	delete[] bytecode5;

	char* bytecode6 = nullptr;
	size_t byteCodeSize6 = 0;
	LoadCompiledShaderData(&bytecode6, byteCodeSize6, "Shaders/Vertex Shaders/VS_SkinnedAnimation.cso");
	myD3DClass->GetDevice()->CreateVertexShader(bytecode6, byteCodeSize6, nullptr, m_PPVSkinnedAnimation.m_VS.GetAddressOf());

	D3D11_INPUT_ELEMENT_DESC vertexDesc3[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UVS", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "PADDING", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMALS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "WEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "JOINT", 0, DXGI_FORMAT_R32G32B32A32_SINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	hr = myD3DClass->GetDevice()->CreateInputLayout(vertexDesc3, ARRAYSIZE(vertexDesc3), bytecode6, byteCodeSize6, m_PPVSkinnedAnimation.m_IL.GetAddressOf());
	delete[] bytecode6;

	printf("Task Complete");
	return true;
}

void SceneManager::RunDebuggerTask(void)
{
	//VertexPositionColor vert01 = { XMFLOAT4(0.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) };
	//XMStoreFloat4(&vert01.position, XMVector4Transform(XMLoadFloat4(&vert01.position), myCube->GetObjectMatrix()));
	//
	//VertexPositionColor vert02 = { XMFLOAT4(2.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) };
	//XMStoreFloat4(&vert02.position, XMVector4Transform(XMLoadFloat4(&vert02.position), myCube->GetObjectMatrix()));
	//
	//VertexPositionColor vert03 = { XMFLOAT4(0.f, 0.f, 0.f, 1.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f) };
	//XMStoreFloat4(&vert03.position, XMVector4Transform(XMLoadFloat4(&vert03.position), myCube->GetObjectMatrix()));
	//
	//VertexPositionColor vert04 = { XMFLOAT4(0.f, 2.f, 0.f, 1.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f) };
	//XMStoreFloat4(&vert04.position, XMVector4Transform(XMLoadFloat4(&vert04.position), myCube->GetObjectMatrix()));
	//
	//VertexPositionColor vert05 = { XMFLOAT4(0.f, 0.f, 0.f, 1.f), XMFLOAT4(0.f, 0.f, 1.f, 0.f) };
	//XMStoreFloat4(&vert05.position, XMVector4Transform(XMLoadFloat4(&vert05.position), myCube->GetObjectMatrix()));
	//
	//VertexPositionColor vert06 = { XMFLOAT4(0.f, 0.f, 2.f, 1.f), XMFLOAT4(0.f, 0.f, 1.f, 0.f) };
	//XMStoreFloat4(&vert06.position, XMVector4Transform(XMLoadFloat4(&vert06.position), myCube->GetObjectMatrix()));

	/**********************Animation**********************/
	if (!freeRun)
	{
		VertexPositionColor vert01 = { XMFLOAT4(0.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) };
		VertexPositionColor vert02 = { XMFLOAT4(2.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) };
		for (size_t i = 1; i < animClip.frames[animationFrame].joints.size(); i++)
		{
			XMStoreFloat4(&vert01.position, XMMATRIX(animClip.frames[animationFrame].joints[animClip.frames[animationFrame].joints[i].parentIndex].globalTransformArray).r[3]);
			XMStoreFloat4(&vert02.position, XMMATRIX(animClip.frames[animationFrame].joints[i].globalTransformArray).r[3]);
			//XMStoreFloat4(&vert01.position, jointMatrices[skelJoints[i].parentIndex].r[3]);
			//XMStoreFloat4(&vert02.position, jointMatrices[i].r[3]);
			myDebugRenderer->AddLine(&vert01, &vert02);
		}
	}
	else
	{
		VertexPositionColor vert01 = { XMFLOAT4(0.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) };
		VertexPositionColor vert02 = { XMFLOAT4(2.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) };
		for (size_t i = 1; i < animClip.frames[animationFrame].joints.size(); i++)
		{
			XMStoreFloat4(&vert01.position, XMMATRIX(animClip.frames[animationFrame].joints[animClip.frames[animationFrame].joints[i].parentIndex].globalTransformArray).r[3]);
			XMStoreFloat4(&vert02.position, XMMATRIX(animClip.frames[animationFrame].joints[i].globalTransformArray).r[3]);
			//XMStoreFloat4(&vert01.position, jointMatrices[skelJoints[i].parentIndex].r[3]);
			//XMStoreFloat4(&vert02.position, jointMatrices[i].r[3]);
			myDebugRenderer->AddLine(&vert01, &vert02);
		}
	}
	//}
	//for (unsigned i = 1; i < skelJoints.size(); i++)
	//{
	//	XMStoreFloat4(&vert01.position, jointMatrices[skelJoints[i].parentIndex].r[3]);
	//	XMStoreFloat4(&vert02.position, jointMatrices[i].r[3]);
	//	myDebugRenderer->AddLine(&vert01, &vert02);
	//}
	/**********************Animation**********************/
	
	//myDebugRenderer->AddLine(&vert01, &vert02);
	//myDebugRenderer->AddLine(&vert03, &vert04);
	//myDebugRenderer->AddLine(&vert05, &vert06);
}

void SceneManager::Tessellation(void)
{
	D3D11_BUFFER_DESC quadBuffDesc;
	quadBuffDesc.Usage = D3D11_USAGE_IMMUTABLE;
	quadBuffDesc.ByteWidth = sizeof(VertexPositionColor) * 3;
	quadBuffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	quadBuffDesc.CPUAccessFlags = 0;
	quadBuffDesc.MiscFlags = 0;

	VertexPositionColor vertices[] = 
	{
		{ XMFLOAT4(+10.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 1.f, 1.f, 1.f) },
		{ XMFLOAT4(-10.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 1.f, 1.f, 1.f) },
		{ XMFLOAT4(-0.f, 10.f, 0.f, 1.f), XMFLOAT4(1.f, 1.f, 1.f, 1.f) }
	};

	D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
	vertexBufferData.pSysMem = vertices;
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;
	HRESULT hr = myD3DClass->GetDevice()->CreateBuffer(&quadBuffDesc, &vertexBufferData, m_tessellationStuff.m_quadVertexBuffer.GetAddressOf());

	CD3D11_BUFFER_DESC constantBufferDesc(sizeof(TessellationStuff::ModelCameraConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
	myD3DClass->GetDevice()->CreateBuffer(&constantBufferDesc, nullptr, m_tessellationStuff. m_modelCameraConstantBuffer.GetAddressOf());

	CD3D11_BUFFER_DESC tessellationConstantBufferDesc(sizeof(ModelViewProjectionConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
	myD3DClass->GetDevice()->CreateBuffer(&tessellationConstantBufferDesc, nullptr, m_tessellationConstantBuffer.GetAddressOf());

	char* bytecode = nullptr;
	size_t byteCodeSize = 0;
	LoadCompiledShaderData(&bytecode, byteCodeSize, "Shaders/Vertex Shaders/VS_Tessellation.cso");
	myD3DClass->GetDevice()->CreateVertexShader(bytecode, byteCodeSize, nullptr, m_tessellationStuff.vertexShader.GetAddressOf());
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	hr = myD3DClass->GetDevice()->CreateInputLayout(vertexDesc, ARRAYSIZE(vertexDesc), bytecode, byteCodeSize, m_tessellationStuff.inputLayout.GetAddressOf());
	delete[] bytecode;

	char* bytecode2 = nullptr;
	size_t byteCodeSize2 = 0;
	LoadCompiledShaderData(&bytecode2, byteCodeSize2, "Shaders/Domain Shaders/DS_Standard.cso");
	myD3DClass->GetDevice()->CreateDomainShader(bytecode2, byteCodeSize2, nullptr, m_tessellationStuff.domainShader.GetAddressOf());
	delete[] bytecode2;

	char* bytecode3 = nullptr;
	size_t byteCodeSize3 = 0;
	LoadCompiledShaderData(&bytecode3, byteCodeSize3, "Shaders/Hull Shaders/HS_Standard.cso");
	myD3DClass->GetDevice()->CreateHullShader(bytecode3, byteCodeSize3, nullptr, m_tessellationStuff.hullShader.GetAddressOf());
	delete[] bytecode3;

	char* bytecode4 = nullptr;
	size_t byteCodeSize4 = 0;
	LoadCompiledShaderData(&bytecode4, byteCodeSize4, "Shaders/Pixel Shaders/PS_Tessellation.cso");
	myD3DClass->GetDevice()->CreatePixelShader(bytecode4, byteCodeSize4, nullptr, m_tessellationStuff.pixelShader.GetAddressOf());
	delete[] bytecode4;
}

void SceneManager::TessellationQuad(void)
{
	D3D11_BUFFER_DESC quadBuffDesc;
	quadBuffDesc.Usage = D3D11_USAGE_IMMUTABLE;
	quadBuffDesc.ByteWidth = sizeof(VertexPositionColor) * 4;
	quadBuffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	quadBuffDesc.CPUAccessFlags = 0;
	quadBuffDesc.MiscFlags = 0;

	VertexPositionColor vertices[] =
	{
		{ XMFLOAT4(+10.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 1.f, 1.f, 1.f) },
		{ XMFLOAT4(-10.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 1.f, 1.f, 1.f) },
		{ XMFLOAT4(-10.f, 10.f, 0.f, 1.f), XMFLOAT4(1.f, 1.f, 1.f, 1.f) },
		{ XMFLOAT4(+10.f, 10.f, 0.f, 1.f), XMFLOAT4(1.f, 1.f, 1.f, 1.f) }
	};

	D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
	vertexBufferData.pSysMem = vertices;
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;
	HRESULT hr = myD3DClass->GetDevice()->CreateBuffer(&quadBuffDesc, &vertexBufferData, m_tessellationQuad.m_quadVertexBuffer.GetAddressOf());

	CD3D11_BUFFER_DESC constantBufferDesc(sizeof(TessellationStuff::ModelCameraConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
	myD3DClass->GetDevice()->CreateBuffer(&constantBufferDesc, nullptr, m_tessellationQuad.m_modelCameraConstantBuffer.GetAddressOf());

	CD3D11_BUFFER_DESC tessellationConstantBufferDesc(sizeof(ModelViewProjectionConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
	myD3DClass->GetDevice()->CreateBuffer(&tessellationConstantBufferDesc, nullptr, m_tessellationQuadConstantBuffer.GetAddressOf());

	char* bytecode = nullptr;
	size_t byteCodeSize = 0;
	LoadCompiledShaderData(&bytecode, byteCodeSize, "Shaders/Vertex Shaders/VS_TessellationQuad.cso");
	myD3DClass->GetDevice()->CreateVertexShader(bytecode, byteCodeSize, nullptr, m_tessellationQuad.vertexShader.GetAddressOf());
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	hr = myD3DClass->GetDevice()->CreateInputLayout(vertexDesc, ARRAYSIZE(vertexDesc), bytecode, byteCodeSize, m_tessellationQuad.inputLayout.GetAddressOf());
	delete[] bytecode;

	char* bytecode2 = nullptr;
	size_t byteCodeSize2 = 0;
	LoadCompiledShaderData(&bytecode2, byteCodeSize2, "Shaders/Domain Shaders/DS_TessellationQuad.cso");
	myD3DClass->GetDevice()->CreateDomainShader(bytecode2, byteCodeSize2, nullptr, m_tessellationQuad.domainShader.GetAddressOf());
	delete[] bytecode2;

	char* bytecode3 = nullptr;
	size_t byteCodeSize3 = 0;
	LoadCompiledShaderData(&bytecode3, byteCodeSize3, "Shaders/Hull Shaders/HS_TessellationQuad.cso");
	myD3DClass->GetDevice()->CreateHullShader(bytecode3, byteCodeSize3, nullptr, m_tessellationQuad.hullShader.GetAddressOf());
	delete[] bytecode3;

	char* bytecode4 = nullptr;
	size_t byteCodeSize4 = 0;
	LoadCompiledShaderData(&bytecode4, byteCodeSize4, "Shaders/Pixel Shaders/PS_TessellationQuad.cso");
	myD3DClass->GetDevice()->CreatePixelShader(bytecode4, byteCodeSize4, nullptr, m_tessellationQuad.pixelShader.GetAddressOf());
	delete[] bytecode4;
}

void SceneManager::PlayAnimation(void)
{
	// Manually go through keyframes
	if (!freeRun)
	{
		VertexPositionColor vert01 = { XMFLOAT4(0.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) };
		VertexPositionColor vert02 = { XMFLOAT4(2.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) };
		for (size_t i = 1; i < animClip.frames[animationFrame].joints.size(); i++)
		{
			XMStoreFloat4(&vert01.position, XMMATRIX(animClip.frames[animationFrame].joints[animClip.frames[animationFrame].joints[i].parentIndex].globalTransformArray).r[3]);
			XMStoreFloat4(&vert02.position, XMMATRIX(animClip.frames[animationFrame].joints[i].globalTransformArray).r[3]);
			myDebugRenderer->AddLine(&vert01, &vert02);
		}
	}
	// Let animation run by itself
	else
	{
		AnimationComponents::Keyframe previousKeyframe, nextKeyframe, currentKeyframe;

		// Fill out the current key frame's joint name and parent index in preperation for drawing
		currentKeyframe.joints.resize(animClip.frames[0].joints.size());
		for (size_t i = 0; i < animClip.frames[0].joints.size(); i++)
		{
			currentKeyframe.joints[i].jointName = animClip.frames[0].joints[i].jointName;
			currentKeyframe.joints[i].parentIndex = animClip.frames[0].joints[i].parentIndex;
			// currentKeyframe.joints[i].4x4 and array will not be filled out because we don't need that information
		}
		float ratio = 0.f;
		for (size_t i = 0; i < animClip.frames.size(); i++)
		{
			if (animClip.frames[i].time > m_timeForAnimation)
			{
				if (0 == i)
				{
					previousKeyframe = animClip.frames[animClip.frames.size() - 1];
					//previousKeyframe.time = 0.f;
				}

				else previousKeyframe = animClip.frames[i - 1];

				nextKeyframe = animClip.frames[i];
				break;
			}
		}
		if (m_timeForAnimation > nextKeyframe.time)
		{
			ratio = (float)(m_timeForAnimation / (previousKeyframe.time - nextKeyframe.time));
		}
		else if (nextKeyframe.time > previousKeyframe.time)
		{
			ratio = (float) ((m_timeForAnimation - previousKeyframe.time) / (nextKeyframe.time - previousKeyframe.time));
		}

		m_jointsForFrameToPresent.clear();

		for (unsigned int i = 0; i < nextKeyframe.joints.size(); i++)
		{
			XMVECTOR quaternionPosition = XMVectorLerp(XMMATRIX(previousKeyframe.joints[i].globalTransformArray).r[3], XMMATRIX(nextKeyframe.joints[i].globalTransformArray).r[3], ratio);
			
			XMVECTOR quaternion01 = XMQuaternionRotationMatrix(XMMATRIX(previousKeyframe.joints[i].globalTransformArray));
			XMVECTOR quaternion02 = XMQuaternionRotationMatrix(XMMATRIX(nextKeyframe.joints[i].globalTransformArray));

			XMVECTOR quaternionSlerp = XMQuaternionSlerp(quaternion01, quaternion02, ratio);

			XMMATRIX quaternionMartix = XMMatrixRotationQuaternion(quaternionSlerp);
			quaternionMartix.r[3] = quaternionPosition;
			m_jointsForFrameToPresent.push_back(quaternionMartix);
		}
		VertexPositionColor vert01 = { XMFLOAT4(0.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) };
		VertexPositionColor vert02 = { XMFLOAT4(2.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) };
		for (size_t i = 1; i < currentKeyframe.joints.size(); i++)
		{
			XMStoreFloat4(&vert01.position, m_jointsForFrameToPresent[currentKeyframe.joints[i].parentIndex].r[3]);
			XMStoreFloat4(&vert02.position, m_jointsForFrameToPresent[i].r[3]);
			myDebugRenderer->AddLine(&vert01, &vert02);
		}
	}
}

void SceneManager::ParticleSystemStuff(void)
{
	bool result = myParticleSystem->Initialize(myD3DClass->GetDevice(), L"star.png");
	char* bytecode = nullptr;
	size_t byteCodeSize = 0;
	LoadCompiledShaderData(&bytecode, byteCodeSize, "Shaders/Pixel Shaders/PS_Particle.cso");
	myD3DClass->GetDevice()->CreatePixelShader(bytecode, byteCodeSize, nullptr, m_particlePipeline.pixel_shader.GetAddressOf());
	delete[] bytecode;

	char* bytecode2 = nullptr;
	size_t byteCodeSize2 = 0;
	LoadCompiledShaderData(&bytecode2, byteCodeSize2, "Shaders/Vertex Shaders/VS_Particle.cso");
	myD3DClass->GetDevice()->CreateVertexShader(bytecode2, byteCodeSize2, nullptr, m_particlePipeline.vertex_shader.GetAddressOf());

	D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	HRESULT hr = myD3DClass->GetDevice()->CreateInputLayout(vertexDesc, ARRAYSIZE(vertexDesc), bytecode2, byteCodeSize2, m_particlePipeline.input_layout.GetAddressOf());
	delete[] bytecode2;
}

SceneManager::PPVStuff::~PPVStuff()
{
	for (unsigned i = 0; i < m_materialsSRVs.size(); i++)
	{
		m_materialsSRVs[i]->Release();
	}
	m_materialsSRVs.clear();
	m_PS.Reset();
	m_VS.Reset();
	m_IL.Reset();
}