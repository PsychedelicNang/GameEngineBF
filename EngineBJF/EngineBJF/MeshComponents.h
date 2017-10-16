#pragma once
#include <vector>
namespace MeshComponents {
	struct Vector4 {
		float x, y, z, w;
	};

	struct BFMesh {
		std::vector<int> indexBuffer;
		std::vector<Vector4> verticesBuffer;
	};

	struct VertexPositionColor {
		float position[4];
		float color[4];
	};

	struct OutInformation {
		std::vector<unsigned> oi_indices;
		std::vector<VertexPositionColor> oi_vertices;
	};
}

namespace MeshComponentsAdvanced {
	struct VertexAdvanced {
		float position[4];
		float normals[4];
		float uvs[2];
		//Tangents?
	};
	struct OutInformationAdvanced {
		std::vector<int> indices;
		std::vector<VertexAdvanced> vertices;
	};
}