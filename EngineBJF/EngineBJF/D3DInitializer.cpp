#include "D3DInitializer.h"

D3DInitializer::D3DInitializer()
{
	m_swapChain				= nullptr;
	m_device				= nullptr;
	m_deviceContext			= nullptr;
	m_renderTargetView		= nullptr;
	m_depthStencilBuffer	= nullptr;
	m_depthStencilState		= nullptr;
	m_depthStencilView		= nullptr;
	m_rasterState			= nullptr;
}

D3DInitializer::~D3DInitializer()
{
	Shutdown();
}

// Initializes all D3D11 components
// Returns false if ANY of the components fail to be created
bool D3DInitializer::Initialize(int _screenWidth, int _screenHeight, bool _vsync, HWND _hwnd, bool _fullscreen, float _screenFar, float _screenNear)
{
	unsigned refreshRateNumerator, refreshRateDenominator;

	// Store the vsync setting.
	m_vsync_enabled = _vsync;

	// Gets the users video card information and figures out the refresh rate of the montior (which are the refreshRate Num and Denom OUT parameters)
	if (!InitializeVideoCardInformation(_screenWidth, _screenHeight, refreshRateNumerator, refreshRateDenominator))							return false;

	// Creates the device and swap chain
	if (!InitializeDeviceAndSwapChain(_screenWidth, _screenHeight, refreshRateNumerator, refreshRateDenominator, _hwnd, _fullscreen))		return false;

	// Creates the Render Target View
	if (!InitializeRenderTargetView())																										return false;

	// Creates the depth buffer, depth view, and depth state.
	if (!InitializeDepthBufferViewAndState(_screenWidth, _screenHeight))																	return false;

	// Creates the rasterizer state
	if (!InitializeRasterizerState())																										return false;

	// Creates the viewport
	if (!InitializeViewport(_screenWidth, _screenHeight))																					return false;

	// Creates the World, Projection, and an Orthogonal matrix (for HUD and 2D text information) for this class.
	if (!InitializeClassMatrices(_screenWidth, _screenHeight, _screenFar, _screenNear))													return false;

	return true;
}

void D3DInitializer::Shutdown()
{
	ShutdownComponents();
}

void D3DInitializer::BeginScene(float _red, float _green, float _blue, float _alpha)
{
	float color[4];

	// Setup the color to clear the buffer to.
	color[0] = _red;
	color[1] = _green;
	color[2] = _blue;
	color[3] = _alpha;

	// Clear the back buffer.
	m_deviceContext->ClearRenderTargetView(m_renderTargetView.Get(), color);

	// Clear the depth buffer.
	m_deviceContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void D3DInitializer::BeginScene(float _color[4])
{
	// Clear the back buffer.
	m_deviceContext->ClearRenderTargetView(m_renderTargetView.Get(), _color);

	// Clear the depth buffer.
	m_deviceContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void D3DInitializer::EndScene()
{
	// Present the back buffer to the screen since rendering is complete.
	if (m_vsync_enabled)
	{
		// Lock to screen refresh rate.
		m_swapChain->Present(1, 0);
	}
	else
	{
		// Present as fast as possible.
		m_swapChain->Present(0, 0);
	}

	return;
}

ComPtr<ID3D11Device> D3DInitializer::GetDevice()
{
	return m_device;
}

ComPtr<ID3D11DeviceContext> D3DInitializer::GetDeviceContext()
{
	return m_deviceContext;
}

XMMATRIX D3DInitializer::GetProjectionMatrix()
{
	return m_projectionMatrix;
}

XMMATRIX D3DInitializer::GetWorldMatrix()
{
	return m_worldMatrix;
}

XMMATRIX D3DInitializer::GetOrthographicMatrix()
{
	return m_orthographicMatrix;
}

void D3DInitializer::GetVideoCardInfo(char* _cardName, int& _amountOfMemory)
{
	strcpy_s(_cardName, 128, m_videoCardDescription);
	_amountOfMemory = m_videoCardMemory;
}

bool D3DInitializer::InitializeVideoCardInformation(int _screenWidth, int _screenHeight, unsigned& _refreshRateNumerator, unsigned& _refreshRateDenominator)
{
	HRESULT result;
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	int error;
	DXGI_MODE_DESC* displayModeList;
	DXGI_ADAPTER_DESC adapterDesc;
	size_t length;
	unsigned int numberOfModes;

	// Create a DirectX graphics interface factory.
	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(result))
	{
		return false;
	}

	// Use the factory to create an adapter for the primary graphics interface (video card).
	result = factory->EnumAdapters(0, &adapter);
	if (FAILED(result))
	{
		return false;
	}

	// Enumerate the primary adapter output (monitor).
	result = adapter->EnumOutputs(0, &adapterOutput);
	if (FAILED(result))
	{
		return false;
	}

	// Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numberOfModes, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Create a list to hold all the possible display modes for this monitor/video card combination.
	displayModeList = new DXGI_MODE_DESC[numberOfModes];
	if (!displayModeList)
	{
		return false;
	}

	// Now fill the display mode list structures.
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numberOfModes, displayModeList);
	if (FAILED(result))
	{
		return false;
	}

	// Now go through all the display modes and find the one that matches the screen width and height.
	// When a match is found store the numerator and denominator of the refresh rate for that monitor.
	for (unsigned i = 0; i< numberOfModes; i++)
	{
		if (displayModeList[i].Width == (unsigned int)_screenWidth)
		{
			if (displayModeList[i].Height == (unsigned int)_screenHeight)
			{
				_refreshRateNumerator = displayModeList[i].RefreshRate.Numerator;
				_refreshRateDenominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	// Get the adapter (video card) description.
	result = adapter->GetDesc(&adapterDesc);
	if (FAILED(result))
	{
		return false;
	}

	// Store the dedicated video card memory in megabytes.
	m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	// Convert the name of the video card to a character array and store it.
	error = wcstombs_s(&length, m_videoCardDescription, 128, adapterDesc.Description, 128);
	if (error != 0)
	{
		return false;
	}

	// Release the display mode list.
	delete[] displayModeList;
	displayModeList = nullptr;

	// Release the adapter output.
	adapterOutput->Release();
	adapterOutput = nullptr;

	// Release the adapter.
	adapter->Release();
	adapter = nullptr;

	// Release the factory.
	factory->Release();
	factory = nullptr;

	return true;
}

bool D3DInitializer::InitializeDeviceAndSwapChain(int _screenWidth, int _screenHeight, unsigned _refreshRateNumerator, unsigned _refreshRateDenominator, HWND _hwnd, bool _fullscreen)
{
	HRESULT result;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;

	// Initialize the swap chain description.
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// Set to a single back buffer.
	swapChainDesc.BufferCount = 1;

	// Set the width and height of the back buffer.
	swapChainDesc.BufferDesc.Width = _screenWidth;
	swapChainDesc.BufferDesc.Height = _screenHeight;

	// Set regular 32-bit surface for the back buffer.
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Set the refresh rate of the back buffer.
	if (m_vsync_enabled)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = _refreshRateNumerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = _refreshRateDenominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	// Set the usage of the back buffer.
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// Set the handle for the window to render to.
	swapChainDesc.OutputWindow = _hwnd;

	// Turn multisampling off.
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	// Set to full screen or windowed mode.
	if (_fullscreen)
	{
		swapChainDesc.Windowed = false;
	}
	else
	{
		swapChainDesc.Windowed = true;
	}

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// Set the scan line ordering and scaling to unspecified.
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Discard the back buffer contents after presenting.
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// Don't set the advanced flags.
	swapChainDesc.Flags = 0;

	// Create the swap chain, Direct3D device, and Direct3D device context.
	result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
		D3D11_SDK_VERSION, &swapChainDesc, m_swapChain.GetAddressOf(), m_device.GetAddressOf(), NULL, m_deviceContext.GetAddressOf());
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool D3DInitializer::InitializeDepthBufferViewAndState(int _screenWidth, int _screenHeight)
{
	HRESULT result;
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;

	// Initialize the description of the depth buffer.
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	// Set up the description of the depth buffer.
	depthBufferDesc.Width = _screenWidth;
	depthBufferDesc.Height = _screenHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	// Create the texture for the depth buffer using the filled out description.
	result = m_device->CreateTexture2D(&depthBufferDesc, NULL, m_depthStencilBuffer.GetAddressOf());
	if (FAILED(result))
	{
		return false;
	}

	// Initialize the description of the stencil state.
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	// Set up the description of the stencil state.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the depth stencil state.
	result = m_device->CreateDepthStencilState(&depthStencilDesc, m_depthStencilState.GetAddressOf());
	if (FAILED(result))
	{
		return false;
	}
	// Set the depth stencil state.
	m_deviceContext->OMSetDepthStencilState(m_depthStencilState.Get(), 1);

	// Initailze the depth stencil view.
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	// Create the depth stencil view.
	result = m_device->CreateDepthStencilView(m_depthStencilBuffer.Get(), &depthStencilViewDesc, m_depthStencilView.GetAddressOf());
	if (FAILED(result))
	{
		return false;
	}

	// Bind the render target view and depth stencil buffer to the output render pipeline.
	m_deviceContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());

	return true;
}

bool D3DInitializer::InitializeRenderTargetView()
{
	HRESULT result;
	ID3D11Texture2D* backBufferPtr;

	// Get the pointer to the back buffer.
	result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
	if (FAILED(result))
	{
		return false;
	}

	// Create the render target view with the back buffer pointer.
	CD3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc(D3D11_RTV_DIMENSION_TEXTURE2D);
	result = m_device->CreateRenderTargetView(backBufferPtr, &renderTargetViewDesc, m_renderTargetView.GetAddressOf());
	if (FAILED(result))
	{
		return false;
	}

	// Release pointer to the back buffer as we no longer need it.
	backBufferPtr->Release();
	backBufferPtr = 0;

	return true;
}

bool D3DInitializer::InitializeRasterizerState()
{
	HRESULT result;
	D3D11_RASTERIZER_DESC rasterDesc;

	// Setup the raster description which will determine how and what polygons will be drawn.
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state from the description we just filled out.
	result = m_device->CreateRasterizerState(&rasterDesc, m_rasterState.GetAddressOf());
	if (FAILED(result))
	{
		return false;
	}

	// Now set the rasterizer state.
	m_deviceContext->RSSetState(m_rasterState.Get());

	return true;
}

bool D3DInitializer::InitializeViewport(int _screenWidth, int _screenHeight)
{
	// Setup the viewport for rendering.
	m_viewport.Width = (float)_screenWidth;
	m_viewport.Height = (float)_screenHeight;
	m_viewport.MinDepth = 0.0f;
	m_viewport.MaxDepth = 1.0f;
	m_viewport.TopLeftX = 0.0f;
	m_viewport.TopLeftY = 0.0f;

	// Create the viewport.
	m_deviceContext->RSSetViewports(1, &m_viewport);

	return true;
}

bool D3DInitializer::InitializeClassMatrices(int _screenWidth, int _screenHeight, float _screenFar, float _screenNear)
{
	float fieldOfView, screenAspect;
	// Setup the projection matrix.
	fieldOfView = (float)XM_PI / 4.0f;
	screenAspect = (float)_screenWidth / (float)_screenHeight;

	// Create the projection matrix for 3D rendering.
	m_projectionMatrix = XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, _screenNear, _screenFar);
	m_worldMatrix = XMMatrixIdentity();

	// Create an orthographic projection matrix for 2D rendering.
	m_orthographicMatrix = XMMatrixOrthographicLH((float)_screenWidth, (float)_screenHeight, _screenNear, _screenFar);

	return true;
}

void D3DInitializer::ShutdownComponents()
{
	m_swapChain.Reset();
	m_device.Reset();
	m_deviceContext.Reset();
	m_renderTargetView.Reset();
	m_depthStencilBuffer.Reset();
	m_depthStencilState.Reset();
	m_depthStencilView.Reset();
	m_rasterState.Reset();
}
