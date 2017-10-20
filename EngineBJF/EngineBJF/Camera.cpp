#include "Camera.h"
Camera::Camera()
{
	m_viewportWidth = 1024;
	m_viewportHeight = 768;
	m_cameraZoom = 70.0f;
	m_nearPlane = 0.1f;
	m_farPlane = 10000.0f;
	m_eye = { 0.0f, 2.f, -10.f, 1.0f };
	m_at = { 0.0f, 0.f, 0.f, 1.0f };
	m_up = { 0.0f, 1.0f, 0.0f, 1.0f };
}

Camera::~Camera()
{
	Shutdown();
}

void Camera::Initialize()
{
	CreateCamera(m_eye, m_at, m_up);
	CreateViewAndPerspectiveMatrix(m_viewportWidth, m_viewportHeight);
}

void Camera::Initialize(float _viewportWidth, float _viewportHeight)
{
	CreateCamera(m_eye, m_at, m_up);
	CreateViewAndPerspectiveMatrix(_viewportWidth, _viewportHeight);
}

void Camera::Initialize(float _viewportWidth, float _viewportHeight, float _zoomAmount)
{
	m_cameraZoom = _zoomAmount;
	CreateCamera(m_eye, m_at, m_up);
	CreateViewAndPerspectiveMatrix(_viewportWidth, _viewportHeight);
}

void Camera::Initialize(float _viewportWidth, float _viewportHeight, float _nearPlane, float _farPlane)
{
	m_nearPlane = _nearPlane;
	m_farPlane = _farPlane;
	CreateCamera(m_eye, m_at, m_up);
	CreateViewAndPerspectiveMatrix(_viewportWidth, _viewportHeight);
}

void Camera::Initialize(float _viewportWidth, float _viewportHeight, float _nearPlane, float _farPlane, float _zoomAmount)
{
	m_nearPlane = _nearPlane;
	m_farPlane = _farPlane;
	m_cameraZoom = _zoomAmount;
	CreateCamera(m_eye, m_at, m_up);
	CreateViewAndPerspectiveMatrix(_viewportWidth, _viewportHeight);
}

void Camera::Initialize(float _viewportWidth, float _viewportHeight, float _nearPlane, float _farPlane, float _zoomAmount, XMVECTOR _eye, XMVECTOR _at, XMVECTOR _up)
{
	m_nearPlane = _nearPlane;
	m_farPlane = _farPlane;
	m_cameraZoom = _zoomAmount;
	m_eye = _eye;
	m_at = _at;
	m_up = _up;
	CreateCamera(_eye, _at, _up);
	CreateViewAndPerspectiveMatrix(_viewportWidth, _viewportHeight);
}

void Camera::Shutdown()
{
}

void Camera::CreateCamera(XMVECTOR _eye, XMVECTOR _at, XMVECTOR _up)
{
	XMStoreFloat4x4(&m_camera, CameraLookAt(_eye, _at, _up));
}

void Camera::CreateViewAndPerspectiveMatrix(float _viewportWidth, float _viewportHeight)
{
	m_viewportWidth = _viewportWidth;
	m_viewportHeight = _viewportHeight;

 	float fovAngleY = m_cameraZoom * XM_PI / 180.0f;
	float aspectRatio = m_viewportWidth / m_viewportHeight;
	XMMATRIX perspectiveMatrix = XMMatrixPerspectiveFovLH(fovAngleY, aspectRatio, m_nearPlane, m_farPlane);
	
	XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixIdentity());

	XMStoreFloat4x4(&m_constantBufferData.projection, perspectiveMatrix);
	XMStoreFloat4x4(&m_constantBufferData.view, XMMatrixInverse(nullptr, XMLoadFloat4x4(&m_camera)));
}

void Camera::CameraTranslation(XMVECTOR _traslationAmount)
{
	XMStoreFloat4x4(&m_camera, XMMatrixMultiply(XMLoadFloat4x4(&m_camera), XMMatrixTranslationFromVector(_traslationAmount)));
}

void Camera::CameraTranslation(float _xDelta, float _yDelta, float _zDelta)
{
	XMStoreFloat4x4(&m_camera, XMMatrixMultiply(XMLoadFloat4x4(&m_camera), XMMatrixTranslation(_xDelta, _yDelta, _zDelta)));
}

void Camera::CameraTranslationX(float _xDelta)
{
	XMStoreFloat4x4(&m_camera, XMMatrixMultiply(XMLoadFloat4x4(&m_camera), XMMatrixTranslation(_xDelta, 0.f, 0.f)));
}

void Camera::CameraTranslationY(float _yDelta)
{
	XMStoreFloat4x4(&m_camera, XMMatrixMultiply(XMLoadFloat4x4(&m_camera), XMMatrixTranslation(0.f, _yDelta, 0.f)));
}

void Camera::CameraTranslationZ(float _zDelta)
{
	XMStoreFloat4x4(&m_camera, XMMatrixMultiply(XMLoadFloat4x4(&m_camera), XMMatrixTranslation(0.f, 0.f, _zDelta)));
}

void Camera::CameraTranslationEyePosition(float _x, float _y, float _z)
{
	m_eye.m128_f32[0] += _x;
	m_eye.m128_f32[1] += _y;
	m_eye.m128_f32[2] += _z;
	m_eye.m128_f32[3] = 1.f;
}

XMMATRIX Camera::CameraLookAt(XMVECTOR _viewerPos, XMVECTOR _targetPos, XMVECTOR _localUp)
{
	//Input: Viewer position(V), Target position(T), Local Up(U)

	//Calculate a new Z - Axis(Z) that points from V towards T.
	XMVECTOR zAxis = XMVectorSubtract(_targetPos, _viewerPos);
	//XMVECTOR zAxis = XMVectorSubtract(_viewerPos, _targetPos);

	//Calculate a new X - Axis(X) that is orthogonal to U and Z.
	XMVECTOR xAxis = XMVector3Cross(_localUp, zAxis);

	//Calculate a new Y - Axis(Y) that is orthogonal to Z and X.
	XMVECTOR yAxis = XMVector3Cross(zAxis, xAxis);

	//Normalize these new axes.
	xAxis = XMVector4Normalize(xAxis);
	yAxis = XMVector4Normalize(yAxis);
	zAxis = XMVector4Normalize(zAxis);

	// Error check for linear Z
	_viewerPos.m128_f32[3] = 1.f;

	XMMATRIX output;
	output.r[0] = xAxis;
	output.r[1] = yAxis;
	output.r[2] = zAxis;
	output.r[3] = _viewerPos;

	// Output : A new 4x4 matrix positioned at V and looking at T 
	//XMStoreFloat4x4(&m_camera, output);
	return output;
}

XMMATRIX Camera::CameraTurnTo(XMMATRIX _viewerMatrix, XMVECTOR _targetPos, float _speed)
{
	XMVECTOR xAxis = _viewerMatrix.r[0];
	XMVECTOR yAxis = _viewerMatrix.r[1];
	XMVECTOR zAxis = _viewerMatrix.r[2];
	zAxis = XMVector4Normalize(zAxis);
	XMVECTOR viewerPos = _viewerMatrix.r[3];
	XMVECTOR worldUp = { 0.f, 1.f, 0.f };

	//Input : Viewer 4x4 matrix(M), Target position(T), Speed scalar(s) 
	XMVECTOR vector = XMVectorSubtract(_targetPos, viewerPos);
	vector = XMVector4Normalize(vector);

	float yRate = vector.m128_f32[0] * xAxis.m128_f32[0] + vector.m128_f32[1] * xAxis.m128_f32[1] + vector.m128_f32[2] * xAxis.m128_f32[2];
	XMMATRIX output = XMMatrixMultiply(XMMatrixRotationY(yRate*_speed), _viewerMatrix);
	//XMMATRIX output = XMMatrixMultiply(XMMatrixRotationY(yRate), _viewerMatrix);

	float xRate = vector.m128_f32[0] * yAxis.m128_f32[0] + vector.m128_f32[1] * yAxis.m128_f32[1] + vector.m128_f32[2] * yAxis.m128_f32[2];
	XMMATRIX output2 = XMMatrixMultiply(XMMatrixRotationX(-xRate*_speed), output);
	//XMMATRIX output2 = XMMatrixMultiply(XMMatrixRotationX(-xRate), output);

	//output = XMMatrixMultiply(output2, output);

	XMVECTOR xAxisForOut = XMVector3Cross(worldUp, output2.r[2]);
	xAxisForOut = XMVector4Normalize(xAxisForOut);

	XMVECTOR yAxisForOut = XMVector3Cross(output2.r[2], xAxisForOut);
	yAxisForOut = XMVector4Normalize(yAxisForOut);

	output2.r[0] = xAxisForOut;
	output2.r[1] = yAxisForOut;

	//Output : A new 4x4 matrix to replace M, rotated partially towards T
	//XMStoreFloat4x4(&m_camera, output2);
	return output2;
}

XMFLOAT4X4 Camera::CameraMouseLook(XMFLOAT4X4 _viewerMatrix, float _xDelta, float _yDelta)
{
	XMFLOAT4 pos = XMFLOAT4(_viewerMatrix._41, _viewerMatrix._42, _viewerMatrix._43, _viewerMatrix._44);
	_viewerMatrix._41 = 0;
	_viewerMatrix._42 = 0;
	_viewerMatrix._43 = 0;

	//Rotate the matrix M about its X - Axis by dY 
	XMMATRIX rotX = XMMatrixRotationX(_yDelta);

	//Rotate the matrix M about its Y - Axis by dX 
	XMMATRIX rotY = XMMatrixRotationY(_xDelta);

	XMMATRIX temp_camera = XMLoadFloat4x4(&_viewerMatrix);
	temp_camera = XMMatrixMultiply(rotX, temp_camera);
	temp_camera = XMMatrixMultiply(temp_camera, rotY);

	XMVECTOR xAxisForOut = XMVector3Cross(m_up, temp_camera.r[2]);
	xAxisForOut = XMVector4Normalize(xAxisForOut);

	XMVECTOR yAxisForOut = XMVector3Cross(temp_camera.r[2], xAxisForOut);
	yAxisForOut = XMVector4Normalize(yAxisForOut);

	temp_camera.r[0] = xAxisForOut;
	temp_camera.r[1] = yAxisForOut;

	//XMStoreFloat4x4(&m_camera, temp_camera);

	m_camera._41 = pos.x;
	m_camera._42 = pos.y;
	m_camera._43 = pos.z;

	//Output : A new 4x4 matrix
	return m_camera;
}

void Camera::SetCamera(XMFLOAT4X4 _camera)
{
	m_camera = _camera;
}

XMFLOAT4X4 Camera::GetCamera()
{
	return m_camera;
}

XMVECTOR Camera::GetCameraEye()
{
	return m_eye;
}

XMVECTOR Camera::GetCameraAt()
{
	return m_at;
}

XMVECTOR Camera::GetCameraUp()
{
	return m_up;
}