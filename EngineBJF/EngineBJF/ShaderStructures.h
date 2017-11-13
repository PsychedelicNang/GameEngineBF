#pragma once
#include <DirectXMath.h>

struct ModelViewProjectionConstantBuffer {
	DirectX::XMFLOAT4X4 model;
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 projection;
};

struct VertexPositionColor {
	DirectX::XMFLOAT4 position;
	DirectX::XMFLOAT4 color;
};

struct SimpleVertex
{
	DirectX::XMFLOAT3 position;
};

struct VertexPositionColorUVNormal {
	DirectX::XMFLOAT4 position;
	DirectX::XMFLOAT4 color;
	DirectX::XMFLOAT4 uv;
	DirectX::XMFLOAT4 normal;
};

struct VertexAnimation {
	DirectX::XMFLOAT4 position;
	DirectX::XMFLOAT4 color;
	DirectX::XMFLOAT4 uv;
	DirectX::XMFLOAT4 normal;
	DirectX::XMFLOAT4 joint;
	DirectX::XMFLOAT4 weight;
};