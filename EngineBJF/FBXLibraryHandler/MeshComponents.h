#pragma once
#include <vector>
namespace MeshComponentsBasic {
	struct Vector4 {
		float x, y, z, w;
	};

	struct Mesh {
		std::vector<unsigned> indexBuffer;
		std::vector<Vector4> verticesBuffer;
	};

	struct VertexPositionColor {
		float position[4];
		float color[4];
	};

	struct OutInformation {
		std::vector<unsigned> indices;
		std::vector<VertexPositionColor> vertices;
	};
}

namespace MeshComponentsAdvanced {
	struct VertexAdvanced {
		float position[4];
		float normals[4];
		float uvs[2];
		//Tangents?
	};
	struct OutInformation {
		std::vector<unsigned> indices;
		std::vector<VertexAdvanced> vertices;
	};
}

namespace MeshComponentsAnimation {
	struct VertexAdvanced {
		float position[4];
		float normals[4];
		float uvs[2];
		float padding[2];
		float weights[4];
		int joints[4];
	};
	struct OutInformation {
		std::vector<unsigned> indices;
		std::vector<VertexAdvanced> vertices;
	};
}