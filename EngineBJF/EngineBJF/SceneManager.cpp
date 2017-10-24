#include "SceneManager.h"

SceneManager::SceneManager()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(452);
	libraryLoadedMaterial = false;
	libraryLoadedMesh = false;

	myCube				= new Object();
	myCamera			= new Camera();
	myTerrain			= new Terrain();
	myDebugRenderer		= new DebugRenderer();
	myD3DClass			= new D3DInitializer();
	myAdvancedMesh		= new Object();
	myMaterialHandler	= new FbxLibraryDLLMaterialHandler();
	myMeshHandler		= new FbxLibraryDLLMeshHandler();
	mouseMove = false;
	m_cameraState = lookAtOrigin;
	timeBetweenFrames = 0.f;
	timer.Restart();
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
	timer.Signal();
	timeBetweenFrames = (float)timer.Delta();
#pragma region states
	//switch (m_cameraState)
	//{
	//case SceneManager::cameraDefault:
	//{
	//	VertexPositionColor vert01 = { XMFLOAT4(XMLoadFloat4x4(&m_cube.matrix).r[3].m128_f32), XMFLOAT4(1.f, 1.f, 0.f, 0.f) };
	//	VertexPositionColor vert02 = { XMFLOAT4(XMLoadFloat4x4(&m_cube02.matrix).r[3].m128_f32), XMFLOAT4(1.f, 1.f, 0.f, 0.f) };

	//	m_debugRenderer.AddLine(vert01, vert02);
	//}
	//break;
	//case SceneManager::lookAtOrigin:
	//{
	//	XMStoreFloat4x4(&m_camera, CameraLookAt(XMLoadFloat4x4(&m_camera).r[3], at, up));
	//	m_cameraState = cameraDefault;

	//	VertexPositionColor vert01 = { XMFLOAT4(XMLoadFloat4x4(&m_cube.matrix).r[3].m128_f32), XMFLOAT4(1.f, 1.f, 0.f, 0.f) };
	//	VertexPositionColor vert02 = { XMFLOAT4(XMLoadFloat4x4(&m_cube02.matrix).r[3].m128_f32), XMFLOAT4(1.f, 1.f, 0.f, 0.f) };

	//	m_debugRenderer.AddLine(vert01, vert02);
	//}
	//break;
	//case SceneManager::lookAtCube1:
	//	XMStoreFloat4x4(&m_camera, CameraLookAt(XMLoadFloat4x4(&m_camera).r[3], XMLoadFloat4x4(&m_cube.matrix).r[3], up));
	//	m_cameraState = cameraDefault;
	//	break;
	//case SceneManager::lookAtCube2:
	//	XMStoreFloat4x4(&m_camera, CameraLookAt(XMLoadFloat4x4(&m_camera).r[3], XMLoadFloat4x4(&m_cube02.matrix).r[3], up));
	//	m_cameraState = cameraDefault;
	//	break;
	//case SceneManager::turnToCube1:
	//{
	//	XMStoreFloat4x4(&m_camera, CameraTurnTo(XMLoadFloat4x4(&m_camera), XMLoadFloat4x4(&m_cube.matrix).r[3], timeBetweenFrames * 5.f));

	//	VertexPositionColor vert01 = { XMFLOAT4(XMLoadFloat4x4(&m_cube.matrix).r[3].m128_f32), XMFLOAT4(1.f, 1.f, 0.f, 0.f) };
	//	VertexPositionColor vert02 = { XMFLOAT4(XMLoadFloat4x4(&m_cube02.matrix).r[3].m128_f32), XMFLOAT4(1.f, 1.f, 0.f, 0.f) };

	//	m_debugRenderer.AddLine(vert01, vert02);
	//}
	//	break;
	//case SceneManager::turnToCube2:
	//{
	//	XMStoreFloat4x4(&m_camera, CameraTurnTo(XMLoadFloat4x4(&m_camera), XMLoadFloat4x4(&m_cube02.matrix).r[3], timeBetweenFrames * 5.f));

	//	VertexPositionColor vert01 = { XMFLOAT4(XMLoadFloat4x4(&m_cube.matrix).r[3].m128_f32), XMFLOAT4(1.f, 1.f, 0.f, 0.f) };
	//	VertexPositionColor vert02 = { XMFLOAT4(XMLoadFloat4x4(&m_cube02.matrix).r[3].m128_f32), XMFLOAT4(1.f, 1.f, 0.f, 0.f) };

	//	m_debugRenderer.AddLine(vert01, vert02);
	//}
	//	break;
	//default:
	//	break;
	//}
#pragma endregion

	RunDebuggerTask();

	myCube->ObjectRotationY(0.50f * timeBetweenFrames);
	myAdvancedMesh->ObjectRotationY(0.5f * timeBetweenFrames);
}

void SceneManager::Render(void)
{
	float RGBA[4] = { .25f, .5f, 1.f, 1.f };
	myD3DClass->BeginScene(RGBA);

	//SetPipelineStates(m_defaultPipeline);
	ComPtr<ID3D11DeviceContext> m_deviceContext = myD3DClass->GetDeviceContext();
	ComPtr<ID3D11Device> m_device = myD3DClass->GetDevice();

	m_deviceContext->IASetInputLayout(m_PPVStuff.m_IL.Get());
	m_deviceContext->VSSetShader(m_PPVStuff.m_VS.Get(), NULL, 0);
	m_deviceContext->PSSetShader(m_PPVStuff.m_PS.Get(), NULL, 0);
	
	if (libraryLoadedMesh && libraryLoadedMesh)
	{
		m_deviceContext->PSSetShaderResources(0, 1, &m_PPVStuff.m_materialsSRVs.data()[1]); // 1, 0, 3 because of the input from shaders... diffuse, emissive, specular
		m_deviceContext->PSSetShaderResources(1, 1, &m_PPVStuff.m_materialsSRVs.data()[0]);	// Skip [2] because we are not using normal mapping right now
		m_deviceContext->PSSetShaderResources(2, 1, &m_PPVStuff.m_materialsSRVs.data()[3]);
	}

	// also, should I just do 	ComPtr<ID3D11DeviceContext> m_deviceContext = myD3DClass->GetDeviceContext() & ComPtr<ID3D11Device> m_device = myD3DClass->GetDevice();
	// when I first make the class or do I need to update the device and context because it changes?

	UpdateConstantBuffer(myCube->GetObjectMatrix());
	myCube->Render(m_deviceContext);

	if (libraryLoadedMesh) {
		UpdateConstantBuffer(myAdvancedMesh->GetObjectMatrix());
		myAdvancedMesh->Render(m_deviceContext);
	}

	SetPipelineStates(m_defaultPipeline);
	UpdateConstantBuffer(XMMatrixIdentity());
	myTerrain->Render(m_deviceContext);

	myDebugRenderer->CreateVertexBuffer(m_device);
	myDebugRenderer->Render(m_device, m_deviceContext);

	m_deviceContext.Reset();
	m_device.Reset();

	myD3DClass->EndScene();
}

void SceneManager::UpdateConstantBuffer(XMMATRIX _modelsMatrix)
{
	XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(_modelsMatrix));
	XMStoreFloat4x4(&m_constantBufferData.view, XMMatrixTranspose(XMLoadFloat4x4(&myCamera->m_constantBufferData.view)));
	XMStoreFloat4x4(&m_constantBufferData.projection, XMMatrixTranspose(XMLoadFloat4x4(&myCamera->m_constantBufferData.projection)));
	myD3DClass->GetDeviceContext()->UpdateSubresource(m_constantBuffer.Get(), 0, NULL, &m_constantBufferData, 0, 0);
	myD3DClass->GetDeviceContext()->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
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
	InitConstantBuffer(m_constantBuffer);
	InitShadersAndInputLayout(m_defaultPipeline.pixel_shader, m_defaultPipeline.vertex_shader, m_defaultPipeline.input_layout);
	
	myCube->Initialize(myD3DClass->GetDevice());
	myCamera->Initialize();
	myTerrain->Initialize(myD3DClass->GetDevice());

	RunTaskForPPV();

	libraryLoadedMesh = myMeshHandler->Initialize();

	std::vector<MeshComponentsAdvanced::OutInformationAdvanced> meshes;
	if (libraryLoadedMesh) libraryLoadedMesh = myMeshHandler->LoadAdvancedMeshFBX("BattleMage.fbx", meshes);
	if (libraryLoadedMesh) myMeshHandler->ExportAdvancedMesh("BattleMageAdv.bin", meshes[0]);
	if (libraryLoadedMesh) libraryLoadedMesh = myAdvancedMesh->ReadInAdvancedMeshFromBinaryFile(myD3DClass->GetDevice(), "BattleMageAdv.bin");

	myAdvancedMesh->ObjectChangePosition(0.f, -2.f, -5.f);
}

void SceneManager::CheckUserInput(WPARAM wParam)
{
	switch (wParam)
	{
	/*case VK_LEFT:
		CameraTranslation(-1.f, 0.f, 0.f);
		RunDebugMessage();
		m_cameraState = cameraDefault;
		break;
	case VK_RIGHT:
		CameraTranslation(1.f, 0.f, 0.f);
		m_cameraState = cameraDefault;
		RunDebugMessage();
		break;
	case VK_UP:
		CameraTranslation(0.f, 1.f, 0.f);
		m_cameraState = cameraDefault;
		RunDebugMessage();
		break;
	case VK_DOWN:
		CameraTranslation(0.f, -1.f, 0.f);
		m_cameraState = cameraDefault;
		RunDebugMessage();
		break;
	case 'O':
		rotateObjects = true;
		break;
	case 'P':
		rotateObjects = false;
		break;*/
	case 'T':
		m_cameraState = turnToCube1;
		break;
	case 'Y':
		m_cameraState = turnToCube2;
		break;
	case 'K':
		m_cameraState = lookAtCube1;
		break;
	case 'L':
		m_cameraState = lookAtCube2;
		break;
	//case 'A':
	//	myCamera->MoveCameraLocalLeft(timeBetweenFrames, 20.f);
	//	break;
	//case 'D':
	//	myCamera->MoveCameraLocalRight(timeBetweenFrames, 20.f);
	//	break;
	//case 'W':
	//	myCamera->MoveCameraLocalForward(timeBetweenFrames, 20.f);
	//	break;
	//case 'S':
	//	myCamera->MoveCameraLocalBackward(timeBetweenFrames, 20.f);
	//	break;
	default:
		break;
	}
}

void SceneManager::RunDebugMessage(void)
{
	//printf();
}

bool SceneManager::RunTaskForPPV(void)
{
	libraryLoadedMaterial = myMaterialHandler->Initialize();

	if (libraryLoadedMaterial)
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
	VertexPositionColor vert01 = { XMFLOAT4(0.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) };
	XMStoreFloat4(&vert01.position, XMVector4Transform(XMLoadFloat4(&vert01.position), myCube->GetObjectMatrix()));

	VertexPositionColor vert02 = { XMFLOAT4(2.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) };
	XMStoreFloat4(&vert02.position, XMVector4Transform(XMLoadFloat4(&vert02.position), myCube->GetObjectMatrix()));

	VertexPositionColor vert03 = { XMFLOAT4(0.f, 0.f, 0.f, 1.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f) };
	XMStoreFloat4(&vert03.position, XMVector4Transform(XMLoadFloat4(&vert03.position), myCube->GetObjectMatrix()));

	VertexPositionColor vert04 = { XMFLOAT4(0.f, 2.f, 0.f, 1.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f) };
	XMStoreFloat4(&vert04.position, XMVector4Transform(XMLoadFloat4(&vert04.position), myCube->GetObjectMatrix()));

	VertexPositionColor vert05 = { XMFLOAT4(0.f, 0.f, 0.f, 1.f), XMFLOAT4(0.f, 0.f, 1.f, 0.f) };
	XMStoreFloat4(&vert05.position, XMVector4Transform(XMLoadFloat4(&vert05.position), myCube->GetObjectMatrix()));

	VertexPositionColor vert06 = { XMFLOAT4(0.f, 0.f, 2.f, 1.f), XMFLOAT4(0.f, 0.f, 1.f, 0.f) };
	XMStoreFloat4(&vert06.position, XMVector4Transform(XMLoadFloat4(&vert06.position), myCube->GetObjectMatrix()));

	myDebugRenderer->AddLine(&vert01, &vert02);
	myDebugRenderer->AddLine(&vert03, &vert04);
	myDebugRenderer->AddLine(&vert05, &vert06);
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