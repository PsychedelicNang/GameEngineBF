#pragma once
#include "SceneManager.h"
using namespace DirectX;

typedef bool(*MYFUNCPOINT01)(const char*, std::vector<BFMesh>&);		// bool LoadMeshFromFBXFile(const char* _fileName, std::vector<BFMesh> & _outVector)
typedef void(*MYFUNCPOINT02)(const char*, BFMesh);						// void ExportMeshToBinaryFile(const char* _filePath, BFMesh _mesh)
typedef bool(*funcReadInMaterialsFromBinaryFile)(const char*, std::vector<MaterialComponents::Material>&);

SceneManager::SceneManager()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(203);
	myCube = new Object();
	myCamera = new Camera();
	myTerrain = new Terrain();
	myDebugRenderer = new DebugRenderer();
	myD3DClass = new D3DInitializer();
	radians = 0.0001f;
	mouseMove = false;
	m_cameraState = lookAtOrigin;
	timeBetweenFrames = 0.f;
	timer.Restart();
}

SceneManager::~SceneManager()
{
	myCube->Shutdown();
	//myCamera->Shutdown();
	myTerrain->Shutdown();
	myD3DClass->Shutdown();
	//myDebugRenderer->Shutdown();
	//if (myCube) delete myCube;
	//delete myCamera;
	//delete myTerrain;
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
	LoadCompiledShaderData(&bytecode, byteCodeSize, "PS_Standard.cso");
	myD3DClass->GetDevice()->CreatePixelShader(bytecode, byteCodeSize, nullptr, _PS.GetAddressOf());
	delete[] bytecode;

	char* bytecode2 = nullptr;
	size_t byteCodeSize2 = 0;
	LoadCompiledShaderData(&bytecode2, byteCodeSize2, "VS_Standard.cso");
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
	timeBetweenFrames = timer.Delta();
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

void SceneManager::Render(void)
{
	float RGBA[4] = { .25f, .5f, 1.f, 1.f };
	myD3DClass->BeginScene(RGBA);

	SetPipelineStates(m_defaultPipeline);

	UpdateConstantBuffer(myCube->GetObjectMatrix());
	myCube->Render(myD3DClass->GetDeviceContext());

	UpdateConstantBuffer(XMMatrixIdentity());
	myTerrain->Render(myD3DClass->GetDeviceContext());

	myDebugRenderer->CreateVertexBuffer(myD3DClass->GetDevice());
	myDebugRenderer->Render(myD3DClass->GetDevice(), myD3DClass->GetDeviceContext());

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
	bool result = myD3DClass->Initialize(_screenWidth, _screenHeight, _vsync, _hwnd, _fullscreen, _screenFar, _screenNear);
	InitConstantBuffer(m_constantBuffer);
	InitShadersAndInputLayout(m_defaultPipeline.pixel_shader, m_defaultPipeline.vertex_shader, m_defaultPipeline.input_layout);
	
	myCube->Initialize(myD3DClass->GetDevice());
	myCamera->Initialize();
	myTerrain->Initialize(myD3DClass->GetDevice());
	
	/*const char* iFilename01 = "terrain.fbx";
	const char* oFilePath = "terrain.mesh";

	const char* iFileName02 = "terrain.mesh";
	FbxLibraryHandle::OutInformation outObject;
	if (FbxLibraryHandle::RunFbxLoader(iFilename01, oFilePath)) {
		if (FbxLibraryHandle::ReadInBinaryMeshFile(iFileName02, outObject)) { std::cout << "File load success";
		
		D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
		indexBufferData.pSysMem = outObject.oi_indices.data();
		indexBufferData.SysMemPitch = 0;
		indexBufferData.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC indexBufferDesc(sizeof(unsigned) * outObject.oi_indices.size(), D3D11_BIND_INDEX_BUFFER);
		m_device->CreateBuffer(&indexBufferDesc, &indexBufferData, m_mesh.m_indexBuffer.GetAddressOf());

		m_mesh.m_indexCount = outObject.oi_indices.size();

		D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
		vertexBufferData.pSysMem = outObject.oi_vertices.data();
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(VertexPositionColor) * outObject.oi_vertices.size(), D3D11_BIND_VERTEX_BUFFER);
		m_device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, m_mesh.m_vertexBuffer.GetAddressOf());

		m_mesh.matrix = DirectX::XMFLOAT4X4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

		m_objectsToRender.push_back(&m_mesh);
		}
		else std::cout << "File load failed";
	}
	RunTaskForPPV();
	RunTaskForAdvancedMesh();*/
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
		break;*/
	/*case 'O':
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
	//	ObjectTranslation(m_cube, -1.f, 0.f, 0.f);
	//	//RunDebugMessage();
	//	break;
	//case 'D':
	//	ObjectTranslation(m_cube, 1.f, 0.f, 0.f);
	//	//RunDebugMessage();
	//	break;
	//case 'W':
	//	ObjectTranslation(m_cube, 0.f, 0.f, 1.f);
	//	//RunDebugMessage();
	//	break;
	//case 'S':
	//	ObjectTranslation(m_cube, 0.f, 0.f, -1.f);
	//	//RunDebugMessage();
	//	break;
	default:
		break;
	}
}
//
//void SceneManager::RunDebugMessage(void)
//{
//	std::cout << "Cube:   " << m_cube.matrix._41 << ", " << m_cube.matrix._42 << ", " << m_cube.matrix._43 << ", " << m_cube.matrix._44 << "\n";
//	std::cout << "Cube02: " << m_cube02.matrix._41 << ", " << m_cube02.matrix._42 << ", " << m_cube02.matrix._43 << ", " << m_cube02.matrix._44 << "\n\n";
//
//	std::cout << "Camera: " << m_camera._11 << ", " << m_camera._12 << ", " << m_camera._13 << ", " << m_camera._14 << "\n";
//	std::cout << "        " << m_camera._21 << ", " << m_camera._22 << ", " << m_camera._23 << ", " << m_camera._24 << "\n";
//	std::cout << "        " << m_camera._31 << ", " << m_camera._32 << ", " << m_camera._33 << ", " << m_camera._34 << "\n";
//	std::cout << "        " << m_camera._41 << ", " << m_camera._42 << ", " << m_camera._43 << ", " << m_camera._44 << "\n\n";
//}

//bool SceneManager::RunFbxLoader(void)
//{
//	HINSTANCE hinstLib; //Handle to the DLL
//	FbxLibraryHandle::MYFUNCPOINT01 ProcAddress01; //Pointer to the function
//	FbxLibraryHandle::MYFUNCPOINT02 ProcAddress02; //Pointer to the function
//
//	hinstLib = LoadLibrary(L"FbxLibraryDLL.dll");
//
//	if (!hinstLib) return false;
//
//	ProcAddress01 = (FbxLibraryHandle::MYFUNCPOINT01)GetProcAddress(hinstLib, "LoadMeshFromFBXFile");
//	ProcAddress02 = (FbxLibraryHandle::MYFUNCPOINT02)GetProcAddress(hinstLib, "ExportMeshToBinaryFile");
//
//	if (!ProcAddress01 || !ProcAddress01) return false;
//
//	const char* lFilename = "terrain.fbx";
//	std::vector<FbxLibraryHandle::BFMesh> meshes;
//
//	bool rtrnVal = (ProcAddress01)(lFilename, meshes);
//
//	const char* lFilePath = "terrain.mesh";
//
//	if (rtrnVal) {
//		printf("Mesh was loaded successfully.\n");
//		(ProcAddress02)(lFilePath, meshes[0]);
//	}
//	return true;
//}
//
//bool SceneManager::RunTaskForPPV(void)
//{
//	HINSTANCE hinstLib; //Handle to the DLL
//	funcReadInMaterialsFromBinaryFile funcPointRIMFBF;
//	hinstLib = LoadLibrary(L"FbxLibraryDLL.dll");
//	
//	if (!hinstLib) return false;
//	
//	funcPointRIMFBF = (funcReadInMaterialsFromBinaryFile)GetProcAddress(hinstLib, "ReadInMaterialsFromBinaryFile");
//	if (!funcPointRIMFBF) return false;
//	
//	std::vector<MaterialComponents::Material> m_VecMaterials;
//	bool rtvValue = funcPointRIMFBF("BattleMage.bin", m_VecMaterials);
//	if (!rtvValue) return false;
//
//	//for each (MaterialComponents::Material mat in m_VecMaterials)
//	//{
//	//	for (mat.m_mapPropValuesIter = mat.m_mapPropValues.begin(); mat.m_mapPropValuesIter != mat.m_mapPropValues.end(); ++mat.m_mapPropValuesIter)
//	//	{
//	//		MaterialComponents::Material::properties prop = mat.m_mapPropValuesIter->first;
//	//		MaterialComponents::Material::properties_t prop_t = mat.m_mapPropValuesIter->second;
//	//		if (prop_t.filePath.compare("WasNotGiven") != 0)	// if we have a file path, get the file path
//	//		{
//	//			ID3D11ShaderResourceView * tempSRV;
//	//			std::wstring widestr = std::wstring(prop_t.filePath.begin(), prop_t.filePath.end());
//	//			const wchar_t* szName = widestr.c_str();
//	//			CreateWICTextureFromFile(m_device.Get(), nullptr, szName, nullptr, &tempSRV, 0);
//	//			m_PPVStuff.m_materialsSRVs.push_back(tempSRV);
//	//		}
//	//	}
//	//}
//
//	ID3D11ShaderResourceView * tempSRV01;
//	CreateWICTextureFromFile(m_device.Get(), nullptr, L"BattleMage.fbm/PPG_3D_Player_D.png", nullptr, &tempSRV01, 0);
//	m_PPVStuff.m_materialsSRVs.push_back(tempSRV01);
//
//	ID3D11ShaderResourceView * tempSRV02;
//	CreateWICTextureFromFile(m_device.Get(), nullptr, L"BattleMage.fbm/PPG_3D_Player_emissive.png", nullptr, &tempSRV02, 0);
//	m_PPVStuff.m_materialsSRVs.push_back(tempSRV02);
//
//	ID3D11ShaderResourceView * tempSRV03;
//	CreateWICTextureFromFile(m_device.Get(), nullptr, L"BattleMage.fbm/PPG_3D_Player_spec.png", nullptr, &tempSRV03, 0);
//	m_PPVStuff.m_materialsSRVs.push_back(tempSRV03);
//
//	char* bytecode = nullptr;
//	size_t byteCodeSize = 0;
//	LoadCompiledShaderData(&bytecode, byteCodeSize, "../x64/Debug/PS_Material.cso");
//	m_device->CreatePixelShader(bytecode, byteCodeSize, nullptr, m_PPVStuff.m_PS.GetAddressOf());
//	delete[] bytecode;
//
//	char* bytecode2 = nullptr;
//	size_t byteCodeSize2 = 0;
//	LoadCompiledShaderData(&bytecode2, byteCodeSize2, "../x64/Debug/VS_Material.cso");
//	m_device->CreateVertexShader(bytecode2, byteCodeSize2, nullptr, m_PPVStuff.m_VS.GetAddressOf());
//	D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
//		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		{ "UVS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		{ "NORMALS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//	};
//	HRESULT hr = m_device->CreateInputLayout(vertexDesc, ARRAYSIZE(vertexDesc), bytecode2, byteCodeSize2, m_PPVStuff.m_IL.GetAddressOf());
//	delete[] bytecode2;
//
//	printf("Task Complete");
//	return true;
//}
//
//bool SceneManager::RunTaskForAdvancedMesh(void)
//{
//	HINSTANCE hinstLib; //Handle to the DLL
//	funcReadInMaterialsFromBinaryFile funcPointRIMFBF;
//	hinstLib = LoadLibrary(L"FbxLibraryDLL.dll");
//
//	if (!hinstLib) return false;
//
//	typedef bool(*funcLoadAdvancedMeshFromFBXFile)(const char*, std::vector<MeshComponentsAdvanced::OutInformationAdvanced>&);
//	typedef void(*funcExportAdvancedMeshToBinaryFile)(const char*, MeshComponentsAdvanced::OutInformationAdvanced &);
//	//typedef bool(*funcReadInAdvancedBinaryMeshFile)(const char *, MeshComponentsAdvanced::OutInformationAdvanced&);
//
//	funcLoadAdvancedMeshFromFBXFile		funcHandLoadAdvancedMeshFromFBXFile;
//	funcExportAdvancedMeshToBinaryFile	funcHandExportAdvancedMeshToBinaryFile;
//	//funcReadInAdvancedBinaryMeshFile	funcHandReadInAdvancedBinaryMeshFile;
//
//	funcHandLoadAdvancedMeshFromFBXFile = (funcLoadAdvancedMeshFromFBXFile)GetProcAddress(hinstLib, "LoadAdvancedMeshFromFBXFile");
//	funcHandExportAdvancedMeshToBinaryFile = (funcExportAdvancedMeshToBinaryFile)GetProcAddress(hinstLib, "ExportAdvancedMeshToBinaryFile");
//	//funcHandReadInAdvancedBinaryMeshFile = (funcReadInAdvancedBinaryMeshFile)GetProcAddress(hinstLib, "ReadInAdvancedBinaryMeshFile");
//
//	std::vector<MeshComponentsAdvanced::OutInformationAdvanced> meshes;
//	MeshComponentsAdvanced::OutInformationAdvanced inMesh;
//
//	const char* fileFbx = "BattleMage.fbx";
//	const char* fileIO = "BattleMageAdv.bin";
//
//	if (funcHandLoadAdvancedMeshFromFBXFile)
//		if (funcHandLoadAdvancedMeshFromFBXFile(fileFbx, meshes)) printf("File was loaded\n");
//
//	if (funcHandExportAdvancedMeshToBinaryFile)
//	{
//		funcHandExportAdvancedMeshToBinaryFile(fileIO, meshes[0]);
//		printf("Exported\n");
//	}
//
//	//if (funcHandReadInAdvancedBinaryMeshFile)
//	//	if (funcHandReadInAdvancedBinaryMeshFile(fileIO, inMesh)) printf("File was read\n");
//
//	if (ReadInAdvancedBinaryMeshFile(fileIO, m_advancedMesh)) printf("\nSuccess\n");
//	else printf("\nObject did not load\n");
//
//	char* bytecode = nullptr;
//	size_t byteCodeSize = 0;
//	LoadCompiledShaderData(&bytecode, byteCodeSize, "../x64/Debug/PS_AdvancedMesh.cso");
//	m_device->CreatePixelShader(bytecode, byteCodeSize, nullptr, m_AdvancedMeshStuff.m_PS.GetAddressOf());
//	delete[] bytecode;
//
//	char* bytecode2 = nullptr;
//	size_t byteCodeSize2 = 0;
//	LoadCompiledShaderData(&bytecode2, byteCodeSize2, "../x64/Debug/VS_AdvancedMesh.cso");
//	m_device->CreateVertexShader(bytecode2, byteCodeSize2, nullptr, m_AdvancedMeshStuff.m_VS.GetAddressOf());
//	D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
//		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		{ "UVS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		{ "NORMALS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//	};
//	HRESULT hr = m_device->CreateInputLayout(vertexDesc, ARRAYSIZE(vertexDesc), bytecode2, byteCodeSize2, m_AdvancedMeshStuff.m_IL.GetAddressOf());
//	delete[] bytecode2;
//
//	printf("Input Layout for Advanced Mesh Created");
//	return true;
//}
//
//bool SceneManager::ReadInBinaryMeshFile(Object& _fillOutObject)
//{
//	std::fstream file;
//	file.open("terrain.mesh", std::ios_base::binary | std::ios_base::in);
//
//	if (file.is_open())
//	{
//		unsigned numOfIndices;
//		unsigned numOfVertices;
//
//		file.read((char*)&numOfIndices, 4);
//
//		unsigned* indices = new unsigned[numOfIndices];
//
//		_fillOutObject.m_indexCount = numOfIndices;
//
//		for (unsigned i = 0; i < numOfIndices; i++)
//			file.read((char*)(&indices[i]), sizeof(4));
//
//		D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
//		indexBufferData.pSysMem = indices;
//		indexBufferData.SysMemPitch = 0;
//		indexBufferData.SysMemSlicePitch = 0;
//		CD3D11_BUFFER_DESC indexBufferDesc(sizeof(unsigned) * numOfIndices, D3D11_BIND_INDEX_BUFFER);
//		m_device->CreateBuffer(&indexBufferDesc, &indexBufferData, _fillOutObject.m_indexBuffer.GetAddressOf());
//
//		delete[] indices;
//
//		file.read((char*)&numOfVertices, 4);
//
//		VertexPositionColor* vertices = new VertexPositionColor[numOfVertices];
//
//		for (unsigned i = 0; i < numOfVertices; i++)
//		{
//			file.read((char*)(&vertices[i].pos.x), sizeof(4));
//			file.read((char*)(&vertices[i].pos.y), sizeof(4));
//			file.read((char*)(&vertices[i].pos.z), sizeof(4));
//			file.read((char*)(&vertices[i].pos.w), sizeof(4));
//			//vertices[i].color = XMFLOAT4(1.f, 1.f, 1.f, 1.f);
//			vertices[i].color = XMFLOAT4(((float)i) / numOfVertices, ((float)i) / numOfVertices, ((float)i) / numOfVertices, 1.f);
//		}
//
//		for (unsigned i = 0; i < numOfVertices; i++)
//			vertices[i].pos.w = 1.f;
//
//		D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
//		vertexBufferData.pSysMem = vertices;
//		vertexBufferData.SysMemPitch = 0;
//		vertexBufferData.SysMemSlicePitch = 0;
//		CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(VertexPositionColor) * numOfVertices, D3D11_BIND_VERTEX_BUFFER);
//		m_device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, _fillOutObject.m_vertexBuffer.GetAddressOf());
//
//		_fillOutObject.matrix = DirectX::XMFLOAT4X4(
//			1, 0, 0, 0,
//			0, 1, 0, 0,
//			0, 0, 1, 0,
//			0, 0, 0, 1);
//
//		m_objectsToRender.push_back(&_fillOutObject);
//		
//		delete[] vertices;
//
//		file.close();
//		return true;
//	}
//	return false;
//}
//
//bool SceneManager::ReadInAdvancedBinaryMeshFile(const char* _fileName, Object & _fillOutObject)
//{
//	std::fstream file;
//	file.open(_fileName, std::ios_base::binary | std::ios_base::in);
//
//	if (file.is_open())
//	{
//		unsigned numOfIndices;
//		unsigned numOfVertices;
//
//		file.read((char*)&numOfIndices, 4);
//
//		unsigned* indices = new unsigned[numOfIndices];
//
//		_fillOutObject.m_indexCount = numOfIndices;
//
//		for (unsigned i = 0; i < numOfIndices; i++)
//			file.read((char*)(&indices[i]), sizeof(4));
//
//		D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
//		indexBufferData.pSysMem = indices;
//		indexBufferData.SysMemPitch = 0;
//		indexBufferData.SysMemSlicePitch = 0;
//		CD3D11_BUFFER_DESC indexBufferDesc(sizeof(unsigned) * numOfIndices, D3D11_BIND_INDEX_BUFFER);
//		m_device->CreateBuffer(&indexBufferDesc, &indexBufferData, _fillOutObject.m_indexBuffer.GetAddressOf());
//
//		delete[] indices;
//
//		file.read((char*)&numOfVertices, 4);
//
//		VertexPositionColorUVNormal* vertices = new VertexPositionColorUVNormal[numOfVertices];
//
//		for (unsigned i = 0; i < numOfVertices; i++)
//		{
//			file.read((char*)(&vertices[i].pos.x), sizeof(4));
//			file.read((char*)(&vertices[i].pos.y), sizeof(4));
//			file.read((char*)(&vertices[i].pos.z), sizeof(4));
//			file.read((char*)(&vertices[i].pos.w), sizeof(4));
//			//vertices[i].color = XMFLOAT4(.5f, 1.f, 1.f, 1.f);
//			vertices[i].color = XMFLOAT4(((float)i) / numOfVertices, ((float)i) / numOfVertices, ((float)i) / numOfVertices, 1.f);
//			
//			file.read((char*)(&vertices[i].normal.x), sizeof(4));
//			file.read((char*)(&vertices[i].normal.y), sizeof(4));
//			file.read((char*)(&vertices[i].normal.z), sizeof(4));
//			file.read((char*)(&vertices[i].normal.w), sizeof(4));
//
//			file.read((char*)(&vertices[i].uv.x), sizeof(4));
//			file.read((char*)(&vertices[i].uv.y), sizeof(4));
//			vertices[i].uv.z = 0.f;
//			vertices[i].uv.w = 0.f;
//		}
//
//		for (unsigned i = 0; i < numOfVertices; i++)
//			vertices[i].pos.w = 1.f;
//
//		D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
//		vertexBufferData.pSysMem = vertices;
//		vertexBufferData.SysMemPitch = 0;
//		vertexBufferData.SysMemSlicePitch = 0;
//		CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(VertexPositionColorUVNormal) * numOfVertices, D3D11_BIND_VERTEX_BUFFER);
//		m_device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, _fillOutObject.m_vertexBuffer.GetAddressOf());
//
//		_fillOutObject.matrix = DirectX::XMFLOAT4X4(
//			1, 0, 0, 0,
//			0, 1, 0, 0,
//			0, 0, 1, 0,
//			0, 0, 0, 1);
//
//		m_objectsToRender.push_back(&_fillOutObject);
//
//		delete[] vertices;
//
//		file.close();
//		return true;
//	}
//	return false;
//}
//
//
//SceneManager::PPVStuff::~PPVStuff()
//{
//	for (unsigned i = 0; i < m_materialsSRVs.size(); i++)
//	{
//		m_materialsSRVs[i]->Release();
//	}
//}