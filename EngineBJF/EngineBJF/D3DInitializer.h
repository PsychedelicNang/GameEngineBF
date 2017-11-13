#pragma once
/***************************
 * Filename: D3DInitializer.h
***************************/
#ifndef _D3DINITIALIZER_H_
#define _D3DINITIALIZER_H_

/***************************
 * LINKING
/***************************/
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

/***************************
 * INCLUDES
***************************/
#include "IncludesBJF.h"
#include <dxgi.h>
#include <d3d11.h>
#include <DirectXMath.h>	// XMFLOAT & XMMATRIX

using namespace DirectX;
class D3DInitializer {
public:
	D3DInitializer();
	~D3DInitializer();

	bool Initialize(int _screenWidth, int _screenHeight, bool _vsync, HWND _hwnd, bool _fullscreen,
		float _screenDepth, float _screenNear);

	void BeginScene(float _red, float _green, float _blue, float _alpha);
	void BeginScene(float _color[4]);

	void EnableZBuffer();
	void DisableZBuffer();

	void EndScene();

	void Shutdown();

	ComPtr<ID3D11Device> GetDevice();
	ComPtr<ID3D11DeviceContext> GetDeviceContext();

	XMMATRIX GetProjectionMatrix();
	XMMATRIX GetWorldMatrix();
	XMMATRIX GetOrthographicMatrix();

	void GetVideoCardInfo(char* _cardName, int& _amountOfMemory);
private:
	bool m_vsync_enabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];

	ComPtr<IDXGISwapChain>				m_swapChain;
	ComPtr<ID3D11Device>				m_device;
	ComPtr<ID3D11DeviceContext>			m_deviceContext;
	ComPtr<ID3D11RenderTargetView>		m_renderTargetView;
	ComPtr<ID3D11Texture2D>				m_depthStencilBuffer;
	ComPtr<ID3D11DepthStencilState>		m_depthStencilState;
	ComPtr<ID3D11DepthStencilState>		m_depthDisabledStencilState;
	ComPtr<ID3D11DepthStencilView>		m_depthStencilView;
	ComPtr<ID3D11RasterizerState>		m_rasterState;
	D3D11_VIEWPORT						m_viewport;
	XMMATRIX m_projectionMatrix;
	XMMATRIX m_worldMatrix;
	XMMATRIX m_orthographicMatrix;
	// View matrix is inside of Camera.h

private:
	bool InitializeVideoCardInformation(int _screenWidth, int _screenHeight, unsigned& _refreshRateNumerator, unsigned& _refreshRateDenominator);
	bool InitializeDeviceAndSwapChain(int _screenWidth, int _screenHeight, unsigned _refreshRateNumerator, unsigned _refreshRateDenominator, HWND _hwnd, bool _fullscreen);
	bool InitializeDepthBufferViewAndState(int _screenWidth, int _screenHeight);
	bool InitializeRenderTargetView();
	bool InitializeRasterizerState();
	bool InitializeViewport(int _screenWidth, int _screenHeight);
	bool InitializeClassMatrices(int _screenWidth, int _screenHeight, float _screenFar, float _screenNear);

	void ShutdownComponents();
};

#endif // !_D3DINITIALIZER_H_