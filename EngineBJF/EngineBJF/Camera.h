#pragma once
///////////////////////
// Filename: Camera.h
///////////////////////
#ifndef _CAMERA_H_
#define _CAMERA_H_

///////////////////////
// INCLUDES
///////////////////////
#include <d3d11.h>			// ID3D11 & D3D11
#pragma comment(lib, "d3d11.lib")
#include <DirectXMath.h>	// XMFLOAT
#include <Windows.h>		// For ComPtr
#include <wrl.h>			// For ComPtr

using namespace DirectX;
using namespace Microsoft::WRL;

class Camera {
	struct ModelViewProjectionConstantBuffer {
		XMFLOAT4X4 model;
		XMFLOAT4X4 view;
		XMFLOAT4X4 projection;
	};
public:
	Camera();
	~Camera();

	void Initialize();
	void Initialize(float _viewportWidth, float _viewportHeight);
	void Initialize(float _viewportWidth, float _viewportHeight, float _zoomAmount);
	void Initialize(float _viewportWidth, float _viewportHeight, float _nearPlane, float _farPlane);
	void Initialize(float _viewportWidth, float _viewportHeight, float _nearPlane, float _farPlane, float _zoomAmount);
	void Initialize(float _viewportWidth, float _viewportHeight, float _nearPlane, float _farPlane, float _zoomAmount, XMVECTOR _eye, XMVECTOR _at, XMVECTOR _up);

	void CameraTranslation(XMVECTOR _traslationAmount);
	void CameraTranslation(float _xDelta, float _yDelta, float _zDelta);
	void CameraTranslationX(float _xDelta);
	void CameraTranslationY(float _yDelta);
	void CameraTranslationZ(float _zDelta);
	void CameraTranslationEyePosition(float _x, float _y, float _z);
	XMMATRIX CameraLookAt(XMVECTOR _viewerPos, XMVECTOR _targetPos, XMVECTOR _localUp);
	XMMATRIX CameraTurnTo(XMMATRIX _viewerMatrix, XMVECTOR _targetPos, float _speed);
	XMFLOAT4X4 CameraMouseLook(XMFLOAT4X4 _viewerMatrix, float _xDelta, float _yDelta);

	void SetCamera(XMFLOAT4X4 _camera);

	XMFLOAT4X4 GetCamera();
	XMVECTOR GetCameraEye();
	XMVECTOR GetCameraAt();
	XMVECTOR GetCameraUp();
	ModelViewProjectionConstantBuffer m_constantBufferData;

	void Shutdown();
private:
	float m_viewportWidth;
	float m_viewportHeight;
	float m_nearPlane;
	float m_farPlane;
	XMFLOAT4X4 m_camera;
	float m_cameraZoom;
	XMVECTOR m_eye;
	XMVECTOR m_at;
	XMVECTOR m_up;

	void CreateCamera(XMVECTOR _eye, XMVECTOR _at, XMVECTOR _up);
	void CreateViewAndPerspectiveMatrix(float _viewportWidth, float _viewportHeight);
};

#endif // !_CAMERA_H_

//
//case WM_MOUSEMOVE:
//	if (sceneManager->mouseMove)
//	{
//		float delta_time = sceneManager->timeBetweenFrames;
//		GetCursorPos(&sceneManager->currCursorPos);
//		ScreenToClient(hWnd, &sceneManager->currCursorPos);
//		//sceneManager->CameraMouseLook(sceneManager->m_camera, (sceneManager->currCursorPos.x - sceneManager->prevCursorPos.x) * delta_time * 7.f, (sceneManager->currCursorPos.y - sceneManager->prevCursorPos.y) * delta_time * 7.f);
//		sceneManager->prevCursorPos = sceneManager->currCursorPos;
//	}
//	GetCursorPos(&sceneManager->prevCursorPos);
//	ScreenToClient(hWnd, &sceneManager->prevCursorPos);
//	break;
//case WM_RBUTTONDOWN:
//	sceneManager->mouseMove = true;
//	break;
//case WM_RBUTTONUP:
//	sceneManager->mouseMove = false;
//	break;
//case WM_KEYDOWN:
//	if (VK_ESCAPE == wParam) {
//		PostQuitMessage(0);
//		break;
//	}
//	sceneManager->CheckUserInput(wParam);
//	break;