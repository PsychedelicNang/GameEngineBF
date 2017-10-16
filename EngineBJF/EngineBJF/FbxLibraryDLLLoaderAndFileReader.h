#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include <fstream>

namespace FbxLibraryHandle
{
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
	typedef bool(*MYFUNCPOINT01)(const char*, std::vector<BFMesh>&);		// bool LoadMeshFromFBXFile(const char* _fileName, std::vector<BFMesh> & _outVector)
	typedef void(*MYFUNCPOINT02)(const char*, BFMesh);						// void ExportMeshToBinaryFile(const char* _filePath, BFMesh _mesh)

	bool RunFbxLoader(const char* _fbxFile, const char* _writeOutFile);
	bool ReadInBinaryMeshFile(const char* _fileName, OutInformation& _objectToFill);
}