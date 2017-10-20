#pragma once
#include "SceneManager.h"
using namespace DirectX;

typedef bool(*MYFUNCPOINT01)(const char*, std::vector<BFMesh>&);		// bool LoadMeshFromFBXFile(const char* _fileName, std::vector<BFMesh> & _outVector)
typedef void(*MYFUNCPOINT02)(const char*, BFMesh);						// void ExportMeshToBinaryFile(const char* _filePath, BFMesh _mesh)
typedef bool(*funcReadInMaterialsFromBinaryFile)(const char*, std::vector<MaterialComponents::Material>&);

SceneManager::SceneManager()
{
	myCube = new Object();
	myCamera = new Camera();
	radians = 0.0001f;
	mouseMove = false;
	m_cameraState = lookAtOrigin;
	timeBetweenFrames = 0.f;
	timer.Restart();
}

SceneManager::~SceneManager()
{
	myCube->Shutdown();
	myCamera->Shutdown();
}

void SceneManager::InitViewport(D3D11_VIEWPORT & _viewport)
{
	_viewport.Width = WIDTH;
	_viewport.Height = HEIGHT;
	_viewport.MinDepth = 0.0f;
	_viewport.MaxDepth = 1.0f;
	_viewport.TopLeftX = 0;
	_viewport.TopLeftY = 0;
	m_imedContext->RSSetViewports(1, &_viewport);
}

void SceneManager::InitDepthBuffer(ComPtr<ID3D11Texture2D>& _depthBuffer)
{
	CD3D11_TEXTURE2D_DESC depthStencilDesc(DXGI_FORMAT_D32_FLOAT, WIDTH, HEIGHT, 1, 0, D3D11_BIND_DEPTH_STENCIL, D3D11_USAGE_DEFAULT, 0, 1, 0);
	// DXGI_FORMAT_D24_UNORM_S8_UINT or DXGI_FORMAT_D32_FLOAT... must match depth view
	m_device->CreateTexture2D(&depthStencilDesc, nullptr, _depthBuffer.GetAddressOf());
}

void SceneManager::InitDepthState(ComPtr<ID3D11DepthStencilState>& _depthState)
{
	CD3D11_DEPTH_STENCIL_DESC depthStencilStateDesc = CD3D11_DEPTH_STENCIL_DESC(CD3D11_DEFAULT());
	m_device->CreateDepthStencilState(&depthStencilStateDesc, _depthState.GetAddressOf());
}

void SceneManager::InitDepthView(ComPtr<ID3D11DepthStencilView>& _depthView)
{
	CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D, DXGI_FORMAT_D32_FLOAT, 0);
	// DXGI_FORMAT_D24_UNORM_S8_UINT or DXGI_FORMAT_D32_FLOAT... must match depth buffer
	m_device->CreateDepthStencilView(m_defaultPipeline.depthStencilBuffer.Get(), nullptr, _depthView.GetAddressOf());
}

void SceneManager::InitRasterState(ComPtr<ID3D11RasterizerState>& _rasterState)
{
	CD3D11_RASTERIZER_DESC rasterStateDesc = CD3D11_RASTERIZER_DESC(CD3D11_DEFAULT());
	//rasterStateDesc.CullMode = D3D11_CULL_NONE;
	m_device->CreateRasterizerState(&rasterStateDesc, _rasterState.GetAddressOf());
}

void SceneManager::InitConstantBuffer(ComPtr<ID3D11Buffer>& _buffer)
{
	CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ModelViewProjectionConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
	m_device->CreateBuffer(&constantBufferDesc, nullptr, _buffer.GetAddressOf());
}

void SceneManager::InitShadersAndInputLayout(ComPtr<ID3D11PixelShader>& _PS, ComPtr<ID3D11VertexShader>& _VS, ComPtr<ID3D11InputLayout>& _IL)
{
	char* bytecode = nullptr;
	size_t byteCodeSize = 0;
	LoadCompiledShaderData(&bytecode, byteCodeSize, "PS_Standard.cso");
	m_device->CreatePixelShader(bytecode, byteCodeSize, nullptr, _PS.GetAddressOf());
	delete[] bytecode;

	char* bytecode2 = nullptr;
	size_t byteCodeSize2 = 0;
	LoadCompiledShaderData(&bytecode2, byteCodeSize2, "VS_Standard.cso");
	m_device->CreateVertexShader(bytecode2, byteCodeSize2, nullptr, _VS.GetAddressOf());
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	HRESULT hr = m_device->CreateInputLayout(vertexDesc, ARRAYSIZE(vertexDesc), bytecode2, byteCodeSize2, _IL.GetAddressOf());
	delete[] bytecode2;
}

void SceneManager::SetPipelineStates(PipelineState& _pipeState)
{
	m_imedContext->IASetInputLayout(_pipeState.input_layout.Get());
	m_imedContext->VSSetShader(_pipeState.vertex_shader.Get(), NULL, 0);
	m_imedContext->PSSetShader(_pipeState.pixel_shader.Get(), NULL, 0);
}

void SceneManager::CreateWindowResources(HWND& _hWnd)
{
	DXGI_SWAP_CHAIN_DESC swapDesc;
	ZeroMemory(&swapDesc, sizeof(swapDesc));
	swapDesc.BufferCount = 1;
	swapDesc.BufferDesc.Width = WIDTH;
	swapDesc.BufferDesc.Height = HEIGHT;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = _hWnd;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;
	swapDesc.Windowed = TRUE;

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
		D3D11_SDK_VERSION, &swapDesc, &m_swapChain, &m_device, NULL, &m_imedContext);

	ID3D11Texture2D *m_BackBuffer;
	CD3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc(D3D11_RTV_DIMENSION_TEXTURE2D);
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_BackBuffer);
	m_device->CreateRenderTargetView(m_BackBuffer, &renderTargetViewDesc, m_defaultPipeline.render_target.GetAddressOf());

	m_BackBuffer->Release();
}

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

void SceneManager::CreateCube(Object* _name, float _xPos, float _yPos, float _zPos)
{
	ComPtr<ID3D11Buffer> tempVertexBuffer;
	ComPtr<ID3D11Buffer> tempIndexBuffer;

	// Load mesh vertices. Each vertex has a position and a color.
	VertexPositionColor cubeVertices[] =
	{
		{ XMFLOAT4(-1.0f, 1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 0.f, 0.f) },
		{ XMFLOAT4(1.0f,  1.0f, -1.0f, 1.0f)  , XMFLOAT4(1.f, 0.f, 0.f, 0.f) },
		{ XMFLOAT4(1.0f,  1.0f,  1.0f, 1.0f)  , XMFLOAT4(0.f, 1.f, 0.f, 0.f) },
		{ XMFLOAT4(-1.0f,  1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 1.f, 0.f, 0.f) },
		{ XMFLOAT4(-1.0f, -1.0f, -1.0f, 1.0f) , XMFLOAT4(0.f, 0.f, 1.f, 0.f) },
		{ XMFLOAT4(1.0f, -1.0f, -1.0f, 1.0f)  , XMFLOAT4(0.f, 0.f, 1.f, 0.f) },
		{ XMFLOAT4(1.0f, -1.0f,  1.0f, 1.0f)  , XMFLOAT4(0.f, 0.f, 0.f, 1.f) },
		{ XMFLOAT4(-1.0f, -1.0f,  1.0f, 1.0f) , XMFLOAT4(0.f, 0.f, 0.f, 1.f) },
	};

	//	-X / +X : Cyan / Red
	//	 - Y / +Y : Magenta / Green
	// - Z / +Z : Yellow / Blue

	D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
	vertexBufferData.pSysMem = cubeVertices;
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(cubeVertices), D3D11_BIND_VERTEX_BUFFER);
	m_device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, tempVertexBuffer.GetAddressOf());

	static const unsigned cubeIndices[] =
	{
		3, 1, 0,
		2, 1, 3,

		0, 5, 4,
		1, 5, 0,

		3, 4, 7,
		0, 4, 3,

		1, 6, 5,
		2, 6, 1,

		2, 7, 6,
		3, 7, 2,

		6, 4, 5,
		7, 4, 6,
	};

	D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
	indexBufferData.pSysMem = cubeIndices;
	indexBufferData.SysMemPitch = 0;
	indexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC indexBufferDesc(sizeof(cubeIndices), D3D11_BIND_INDEX_BUFFER);
	m_device->CreateBuffer(&indexBufferDesc, &indexBufferData, tempIndexBuffer.GetAddressOf());

	DirectX::XMFLOAT4X4 temp = DirectX::XMFLOAT4X4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		_xPos, _yPos, _zPos, 1);

	_name->Initialize(tempVertexBuffer, tempIndexBuffer, ARRAYSIZE(cubeIndices), sizeof(VertexPositionColor), DXGI_FORMAT_R32_UINT, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void SceneManager::Update(void)
{
	timer.Signal();
	timeBetweenFrames = timer.Delta();

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

	// Vertices
		//VertexPositionColor vert01 = { XMFLOAT4(0.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) };
		//XMStoreFloat4(&vert01.pos, XMVector4Transform(XMLoadFloat4(&vert01.pos), XMLoadFloat4x4(&m_cube.matrix)));

		//VertexPositionColor vert02 = { XMFLOAT4(2.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) };
		//XMStoreFloat4(&vert02.pos, XMVector4Transform(XMLoadFloat4(&vert02.pos), XMLoadFloat4x4(&m_cube.matrix)));

		//VertexPositionColor vert03 = { XMFLOAT4(0.f, 0.f, 0.f, 1.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f) };
		//XMStoreFloat4(&vert03.pos, XMVector4Transform(XMLoadFloat4(&vert03.pos), XMLoadFloat4x4(&m_cube.matrix)));

		//VertexPositionColor vert04 = { XMFLOAT4(0.f, 2.f, 0.f, 1.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f) };
		//XMStoreFloat4(&vert04.pos, XMVector4Transform(XMLoadFloat4(&vert04.pos), XMLoadFloat4x4(&m_cube.matrix)));

		//VertexPositionColor vert05 = { XMFLOAT4(0.f, 0.f, 0.f, 1.f), XMFLOAT4(0.f, 0.f, 1.f, 0.f) };
		//XMStoreFloat4(&vert05.pos, XMVector4Transform(XMLoadFloat4(&vert05.pos), XMLoadFloat4x4(&m_cube.matrix)));

		//VertexPositionColor vert06 = { XMFLOAT4(0.f, 0.f, 2.f, 1.f), XMFLOAT4(0.f, 0.f, 1.f, 0.f) };
		//XMStoreFloat4(&vert06.pos, XMVector4Transform(XMLoadFloat4(&vert06.pos), XMLoadFloat4x4(&m_cube.matrix)));

		//VertexPositionColor vert07 = { XMFLOAT4(0.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) };
		//XMStoreFloat4(&vert07.pos, XMVector4Transform(XMLoadFloat4(&vert07.pos), XMLoadFloat4x4(&m_cube02.matrix)));

		//VertexPositionColor vert08 = { XMFLOAT4(2.f, 0.f, 0.f, 1.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f) };
		//XMStoreFloat4(&vert08.pos, XMVector4Transform(XMLoadFloat4(&vert08.pos), XMLoadFloat4x4(&m_cube02.matrix)));

		//VertexPositionColor vert09 = { XMFLOAT4(0.f, 0.f, 0.f, 1.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f) };
		//XMStoreFloat4(&vert09.pos, XMVector4Transform(XMLoadFloat4(&vert09.pos), XMLoadFloat4x4(&m_cube02.matrix)));

		//VertexPositionColor vert10 = { XMFLOAT4(0.f, 2.f, 0.f, 1.f), XMFLOAT4(0.f, 1.f, 0.f, 0.f) };
		//XMStoreFloat4(&vert10.pos, XMVector4Transform(XMLoadFloat4(&vert10.pos), XMLoadFloat4x4(&m_cube02.matrix)));

		//VertexPositionColor vert11 = { XMFLOAT4(0.f, 0.f, 0.f, 1.f), XMFLOAT4(0.f, 0.f, 1.f, 0.f) };
		//XMStoreFloat4(&vert11.pos, XMVector4Transform(XMLoadFloat4(&vert11.pos), XMLoadFloat4x4(&m_cube02.matrix)));

		//VertexPositionColor vert12 = { XMFLOAT4(0.f, 0.f, 2.f, 1.f), XMFLOAT4(0.f, 0.f, 1.f, 0.f) };
		//XMStoreFloat4(&vert12.pos, XMVector4Transform(XMLoadFloat4(&vert12.pos), XMLoadFloat4x4(&m_cube02.matrix)));

		//m_debugRenderer.AddLine(vert01, vert02);
		//m_debugRenderer.AddLine(vert03, vert04);
		//m_debugRenderer.AddLine(vert05, vert06);
		//m_debugRenderer.AddLine(vert07, vert08);
		//m_debugRenderer.AddLine(vert09, vert10);
		//m_debugRenderer.AddLine(vert11, vert12);

	//if (rotateObjects) {
	//	for (unsigned i = 0; i < m_objectsToRender.size(); i++)
	//	{
	//		//XMStoreFloat4x4(&m_objectsToRender[i]->matrix, XMMatrixMultiply(XMMatrixRotationX(radians), XMLoadFloat4x4(&m_objectsToRender[i]->matrix)));
	//		XMStoreFloat4x4(&m_objectsToRender[i]->matrix, XMMatrixMultiply(XMMatrixRotationY(radians), XMLoadFloat4x4(&m_objectsToRender[i]->matrix)));
	//	}
	//}
}

void SceneManager::Render(void)
{
	float RGBA[4] = { .25f, .5f, 1.f, 1.f };

	m_imedContext->OMSetRenderTargets(1, m_defaultPipeline.render_target.GetAddressOf(), m_defaultPipeline.depthStencilView.Get());
	m_imedContext->ClearRenderTargetView(m_defaultPipeline.render_target.Get(), RGBA);
	m_imedContext->ClearDepthStencilView(m_defaultPipeline.depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	SetPipelineStates(m_defaultPipeline);

	XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMLoadFloat4x4(&myCube->GetMatrix())));
	XMStoreFloat4x4(&m_constantBufferData.view, XMMatrixTranspose(XMLoadFloat4x4(&myCamera->m_constantBufferData.view)));
	XMStoreFloat4x4(&m_constantBufferData.projection, XMMatrixTranspose(XMLoadFloat4x4(&myCamera->m_constantBufferData.projection)));

	m_imedContext->UpdateSubresource(m_constantBuffer.Get(), 0, NULL, &m_constantBufferData, 0, 0);
	m_imedContext->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
	myCube->Render(m_imedContext);
	
	m_swapChain->Present(0, 0);
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

void SceneManager::RunTaskList(HWND& _hWnd)
{
	CreateWindowResources(_hWnd);
	InitViewport(m_viewport);
	InitConstantBuffer(m_constantBuffer);
	InitDepthBuffer(m_defaultPipeline.depthStencilBuffer);
	InitDepthState(m_defaultPipeline.depthStencilState);
	InitDepthView(m_defaultPipeline.depthStencilView);
	InitRasterState(m_defaultPipeline.rasterState);
	InitShadersAndInputLayout(m_defaultPipeline.pixel_shader, m_defaultPipeline.vertex_shader, m_defaultPipeline.input_layout);
	CreateCube(myCube, 0.f, 0.f, 0.f);
	myCamera->Initialize();
	
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

SceneManager::PPVStuff::~PPVStuff()
{
	for (unsigned i = 0; i < m_materialsSRVs.size(); i++)
	{
		m_materialsSRVs[i]->Release();
	}
}