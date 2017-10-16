#pragma once
#include <vector>
#include <string>

struct Vector4 {
	float x, y, z, w;
};

struct BFMesh {
	std::vector<int> indexBuffer;
	std::vector<Vector4> verticesBuffer;
};