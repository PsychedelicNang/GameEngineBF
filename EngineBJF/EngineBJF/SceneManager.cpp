#include "SceneManager.h"

SceneManager::SceneManager()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(569);
	m_libraryLoadedMaterial = false;
	m_libraryLoadedMesh = false;

	myCube				= new Object();
	myCamera			= new Camera();
	myTerrain			= new Terrain();
	myDebugRenderer		= new DebugRenderer();
	myD3DClass			= new D3DInitializer();
	myAdvancedMesh		= new Object();
	myMaterialHandler	= new FbxLibraryDLLMaterialHandler();
	myMeshHandler		= new FbxLibraryDLLMeshHandler();
	myAnimationHandler = new FbxLibraryDLLAnimationHandler();
	mouseMove = false;
	m_rotate = false;
	m_cameraState = cameraDefault;
	m_timeBetweenFrames = 0.f;
	m_timer.Restart();
	// Decrement count of GInput
}

SceneManager::~SceneManager()
{
	if (myCube) delete myCube;
	if (myCamera) delete myCamera;
	if (myTerrain) delete myTerrain;
	if (myDebugRenderer) delete myDebugRenderer;
	if (myD3DClass) delete myD3DClass;
	if (myAdvancedMesh) delete myAdvancedMesh;
	if (myMaterialHandler) delete myMaterialHandler;
	if (myMeshHandler) delete myMeshHandler;
	if (myAnimationHandler) delete myAnimationHandler;
}

void SceneManager::InitConstantBuffer(ComPtr<ID3D11Buffer>& _buffer)
{
	CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ModelViewProjectionConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
	myD3DClass->GetDevice()->CreateBuffer(&constantBufferDesc, nullptr, _buffer.GetAddressOf());
}

void SceneManager::InitShadersAndInputLayout(ComPtr<ID3D11PixelShader>& _PS, ComPtr<ID3D11VertexShader>& _VS, ComPtr<ID3D11InputLayout>& _IL)
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

void SceneManager::SetPipelineStates(PipelineState& _pipeState)
{
	myD3DClass->GetDeviceContext()->IASetInputLayout(_pipeState.input_layout.Get());
	myD3DClass->GetDeviceContext()->VSSetShader(_pipeState.vertex_shader.Get(), NULL, 0);
	myD3DClass->GetDeviceContext()->PSSetShader(_pipeState.pixel_shader.Get(), NULL, 0);
}

void SceneManager::Update(void)
{	
	CheckUserInput();

	m_timer.Signal();
	m_timeBetweenFrames = (float)m_timer.Delta();
	
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
			myCamera->SetCamera(myCamera->CameraLookAt(myCamera->GetCameraMatrix().r[3], myAdvancedMesh->GetObjectMatrix().r[3], up));
		}
			break;
		case SceneManager::turnToCube:
			myCamera->SetCamera(myCamera->CameraTurnTo(myCamera->GetCameraMatrix(), myCube->GetObjectMatrix().r[3], m_timeBetweenFrames * 5.f));
			break;
		case SceneManager::turnToMesh:
			myCamera->SetCamera(myCamera->CameraTurnTo(myCamera->GetCameraMatrix(), myAdvancedMesh->GetObjectMatrix().r[3], m_timeBetweenFrames * 5.f));
			break;
		default:
			break;
	}

	RunDebuggerTask();

	if (m_rotate)
	{
		myCube->ObjectRotationY(0.50f * m_timeBetweenFrames);
		myAdvancedMesh->ObjectRotationY(0.5f * m_timeBetweenFrames);
	}

	myCamera->CreateViewAndPerspectiveMatrix();
}

void SceneManager::Render(void)
{
	float RGBA[4] = { .25f, .5f, 1.f, 1.f };
	myD3DClass->BeginScene(RGBA);

	ComPtr<ID3D11DeviceContext> m_deviceContext = myD3DClass->GetDeviceContext();
	ComPtr<ID3D11Device> m_device = myD3DClass->GetDevice();
	
	m_deviceContext->IASetInputLayout(m_PPVStuff.m_IL.Get());
	m_deviceContext->HSSetShader(NULL, NULL, 0);
	m_deviceContext->DSSetShader(NULL, NULL, 0);
	m_deviceContext->VSSetSamplers(0, 1, m_samplerState.GetAddressOf());
	m_deviceContext->PSSetSamplers(0, 1, m_samplerState.GetAddressOf());
	
	m_deviceContext->VSSetShader(m_PPVStuff.m_VS.Get(), NULL, 0);
	m_deviceContext->PSSetShader(m_PPVStuff.m_PS.Get(), NULL, 0);
	//
	//if (m_libraryLoadedMesh && m_libraryLoadedMesh)
	//{
	//	m_deviceContext->PSSetShaderResources(0, 1, &m_PPVStuff.m_materialsSRVs.data()[1]); // 1, 0, 3 because of the input from shaders... diffuse, emissive, specular
	//	m_deviceContext->PSSetShaderResources(1, 1, &m_PPVStuff.m_materialsSRVs.data()[0]);	// Skip [2] because we are not using normal mapping right now
	//	m_deviceContext->PSSetShaderResources(2, 1, &m_PPVStuff.m_materialsSRVs.data()[3]);
	//}
	//m_deviceContext->PSSetShaderResources(3, 1, m_PPVStuff.m_materialsSRVs.data());
	//UpdateStandardConstantBuffer(myCube->GetObjectMatrix());
	//myCube->Render(m_deviceContext);
	
	//if (m_libraryLoadedMesh && m_libraryLoadedMesh)
	//{
	//	m_deviceContext->PSSetShaderResources(0, 1, &m_PPVStuff.m_materialsSRVs.data()[0]); // 1, 0, 3 because of the input from shaders... diffuse, emissive, specular
	//	//m_deviceContext->PSSetShaderResources(0, 1, m_PPVStuff.m_materialsSRVs.data());
	//}
	//if (m_libraryLoadedMesh) {
	//	UpdateStandardConstantBuffer(myAdvancedMesh->GetObjectMatrix());
	//	myAdvancedMesh->Render(m_deviceContext);
	//}
	
	SetPipelineStates(m_defaultPipeline);
	UpdateStandardConstantBuffer(XMMatrixIdentity());
	myTerrain->Render(m_deviceContext);
	
	myDebugRenderer->CreateVertexBuffer(m_device);
	myDebugRenderer->Render(m_device, m_deviceContext);

	/********************Tessellation******************************/
	//m_deviceContext->IASetInputLayout(m_tessellationStuff.inputLayout.Get());
	//
	//m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST);
	//UINT stride = sizeof(VertexPositionColor);
	//UINT offset = 0;
	//
	//UpdateTessellationConstantBuffer();
	//m_deviceContext->IASetVertexBuffers(0, 1, m_tessellationStuff.m_quadVertexBuffer.GetAddressOf(), &stride, &offset);
	//m_deviceContext->VSSetShader(m_tessellationStuff.vertexShader.Get(), NULL, 0);
	//m_deviceContext->PSSetShader(m_tessellationStuff.pixelShader.Get(), NULL, 0);
	//m_deviceContext->HSSetShader(m_tessellationStuff.hullShader.Get(), NULL, 0);
	//m_deviceContext->DSSetShader(m_tessellationStuff.domainShader.Get(), NULL, 0);
	//
	//m_deviceContext->Draw(3, 0);
	/********************Tessellation******************************/

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

	myGInput = myD3DClass->myGInput;
	InitConstantBuffer(m_constantBuffer);
	InitShadersAndInputLayout(m_defaultPipeline.pixel_shader, m_defaultPipeline.vertex_shader, m_defaultPipeline.input_layout);
	
	myCube->Initialize(myD3DClass->GetDevice());
	myCamera->Initialize();

	//float m_viewportWidth = 1024;
	//float m_viewportHeight = 768;
	//float m_cameraZoom = 70.0f;
	//float m_nearPlane = 0.1f;
	//float m_farPlane = 10000.0f;
	//XMVECTOR eye = { 20.0f, 5.f, -10.f, 1.0f };
	//XMVECTOR at = { 20.0f, 0.f, 0.f, 1.0f };
	//XMVECTOR up = { 0.0f, 1.0f, 0.0f, 1.0f };
	//myCamera->Initialize(m_viewportWidth, m_viewportHeight, m_nearPlane, m_farPlane, m_cameraZoom, eye, at, up);
	
	myTerrain->Initialize(myD3DClass->GetDevice());

	RunTaskForPPV();

	m_libraryLoadedMesh = myMeshHandler->Initialize();

	std::vector<MeshComponentsAdvanced::OutInformationAdvanced> meshes;
	//if (m_libraryLoadedMesh) m_libraryLoadedMesh = myMeshHandler->LoadAdvancedMeshFBX("BattleMage.fbx", meshes);
	//if (m_libraryLoadedMesh) myMeshHandler->ExportAdvancedMesh("BattleMageAdv.bin", meshes[0]);
	//if (m_libraryLoadedMesh) m_libraryLoadedMesh = myAdvancedMesh->ReadInAdvancedMeshFromBinaryFile(myD3DClass->GetDevice(), "BattleMageAdv.bin");

	if (m_libraryLoadedMesh) m_libraryLoadedMesh = myMeshHandler->LoadAdvancedMeshFBX("Teddy_Idle.fbx", meshes);
	if (m_libraryLoadedMesh) myMeshHandler->ExportAdvancedMesh("Teddy_Idle.bin", meshes[0]);
	if (m_libraryLoadedMesh) m_libraryLoadedMesh = myAdvancedMesh->ReadInAdvancedMeshFromBinaryFile(myD3DClass->GetDevice(), "Teddy_Idle.bin");
	
	if (myAnimationHandler->Initialize())	myAnimationHandler->LoadAnimationFBX("Teddy_Idle.fbx", animClip, skelJoints);

	// Scale the model down
	for (size_t i = 0; i < skelJoints.size(); i++)
	{
		skelJoints[i].globalTransformArray[12] *= 0.02f;
		skelJoints[i].globalTransformArray[13] *= 0.02f;
		skelJoints[i].globalTransformArray[14] *= 0.02f;

		skelJoints[i].globalTransform4x4[3][0] *= 0.02f;
		skelJoints[i].globalTransform4x4[3][1] *= 0.02f;
		skelJoints[i].globalTransform4x4[3][2] *= 0.02f;
	
		jointMatrices.push_back(XMMATRIX(skelJoints[i].globalTransformArray));
	}
	
	// Scale the animation down as well
	for (size_t i = 0; i < animClip.frames.size(); i++)
	{
		for (size_t j = 0; j < animClip.frames[i].joints.size(); j++)
		{
			animClip.frames[i].joints[j].globalTransformArray[12] *= 0.02f;
			animClip.frames[i].joints[j].globalTransformArray[13] *= 0.02f;
			animClip.frames[i].joints[j].globalTransformArray[14] *= 0.02f;

			animClip.frames[i].joints[j].globalTransform4x4[3][0] *= 0.02f;
			animClip.frames[i].joints[j].globalTransform4x4[3][1] *= 0.02f;
			animClip.frames[i].joints[j].globalTransform4x4[3][2] *= 0.02f;
		}
	}

	//myAdvancedMesh->ObjectChangePosition(0.f, -2.f, -5.f);

	Tessellation();

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

	myD3DClass->GetDevice()->CreateSamplerState(&samplerDesc, m_samplerState.GetAddressOf());
}

float SceneManager::GetTimeBetweenFrames()
{
	return m_timeBetweenFrames;
}

Camera * SceneManager::GetCamera()
{
	return myCamera;
}

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

	myGInput->GetState(G_KEY_P, returnValue);
	if (returnValue) {
		m_cameraState = cameraDefault;
	}

	myGInput->GetState(G_KEY_T, returnValue);
	if (returnValue) {
		m_cameraState = turnToCube;
	}

	myGInput->GetState(G_KEY_Y, returnValue);
	if (returnValue) {
		m_cameraState = turnToMesh;
	}

	myGInput->GetState(G_KEY_K, returnValue);
	if (returnValue) {
		m_cameraState = lookAtCube;
	}

	myGInput->GetState(G_KEY_L, returnValue);
	if (returnValue) {
		m_cameraState = lookAtMesh;
	}

	myGInput->GetState(G_KEY_O, returnValue);
	if (returnValue) {
		m_cameraState = lookAtOrigin;
	}

	myGInput->GetState(G_KEY_R, returnValue);
	if (returnValue) {
		m_rotate = !m_rotate;
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
		std::vector<MaterialComponents::Material> m_VecMaterials;
		//bool result = myMaterialHandler->LoadMaterialsBinary("BattleMage.bin", m_VecMaterials);
		bool res = myMaterialHandler->LoadMaterialFBX("Teddy_Idle.fbx", m_VecMaterials);

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
					m_PPVStuff.m_materialsSRVs.push_back(tempSRV);
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
		{ "UVS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMALS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	HRESULT hr = myD3DClass->GetDevice()->CreateInputLayout(vertexDesc, ARRAYSIZE(vertexDesc), bytecode2, byteCodeSize2, m_PPVStuff.m_IL.GetAddressOf());
	delete[] bytecode2;

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
	VertexPositionColor vert01 = { XMFLOAT4(0.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) };
	VertexPositionColor vert02 = { XMFLOAT4(2.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) };
	for (unsigned i = 1; i < skelJoints.size(); i++)
	{
		XMStoreFloat4(&vert01.position, jointMatrices[skelJoints[i].parentIndex].r[3]);
		XMStoreFloat4(&vert02.position, jointMatrices[i].r[3]);
		myDebugRenderer->AddLine(&vert01, &vert02);
	}
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