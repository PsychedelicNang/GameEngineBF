#pragma once
/***************************
* Filename: CustomFormatReader.h
***************************/
#ifndef _CUSTOMFORMATREADER_H_
#define _CUSTOMFORMATREADER_H_

/***************************
* INCLUDES
***************************/
#include <fstream>
#include <array>
#include <vector>
#include <string>
#include <map>

struct alignas(16) float4 : std::array<float, 4> { using std::array<float, 4>::array;  };

namespace MaterialComponents {
	struct Material {
		enum properties { EMISSIVE = 0, AMBIENT, DIFFUSE, NORMAL, BUMP, TRANSPARENCY, DISPLACEMENT, VECTOR_DISPLACEMENT, SPECULAR, SHININESS, REFLECTION, COUNT };

		enum materialType { PHONG = 0, LAMBERT } m_materialType;

		struct properties_t {
			std::string filePath;	// "WasNotGiven" if there is not file path
			float4 value;			// any value which is -1 represents no valid value or N/A (meaing -1,-1,-1,.5f would represent the data type is a single floating point value)
		};
		std::map<properties*, properties_t*> m_mapPropValues;
		std::map<properties*, properties_t*>::iterator m_mapPropValuesIter;
	};
}

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
		float weights[4];
		int joints[4];
	};
	struct OutInformation {
		std::vector<unsigned> indices;
		std::vector<VertexAdvanced> vertices;
	};
}

namespace AnimationComponents {
	struct SkeletonJoint {
		float globalTransformArray[16];
		int parentIndex;
		std::string jointName;
	};

	struct Keyframe {
		double time;
		std::vector<SkeletonJoint> joints;
	};

	struct AnimationClip {
		double duration;
		std::vector<Keyframe> frames;
	};

	struct BindPose {
		std::vector<SkeletonJoint> joints;
		struct BindPoseJoints {
			float globalTransformArray[16];
			int parentIndex;
			std::string jointName;
		};
	};
}

// for changing coordinate system:
// ...for any positions: pos.x = -pos.x (ALL POSITIONS)
// ...axes: yAxis.x = -yAxis.x, zAxis.x = -zAxis.x, xAxis.y = -xAxis.y, xAxis.z = -xAxis.z
// ...also change uv values: uv.v = 1 - uv.v


class CustomFormatReader {
public:
	bool ReadInBasicBinaryMeshFile(const char * _fileName, MeshComponentsBasic::OutInformation& _objectToFill, float _scaleAmount = 1.f);
	bool ReadInMaterialsFromBinaryFile(const char* _filePath, std::vector<MaterialComponents::Material>& _materials);
	void PrintMaterialProperties(std::vector<MaterialComponents::Material>& _materials);
	bool ReadInAdvancedBinaryMeshFile(const char * _fileName, MeshComponentsAdvanced::OutInformation& _objectToFill, float _scaleAmount = 1.f);
	bool ReadInAdvancedMeshWithSkinnedAnimationFromBinaryFile(const char* _fileName, MeshComponentsAnimation::OutInformation & _objectToFill,
		AnimationComponents::BindPose& _bindPose, AnimationComponents::AnimationClip& _animationClip, std::vector<AnimationComponents::SkeletonJoint>& _skelJoints);
};

#endif // !_CUSTOMFORMATREADER_H_