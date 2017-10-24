#pragma once

#ifdef FBXLIBRARYDLL_EXPORTS
#define FBXLIBRARY_API __declspec(dllexport)
#else
#define FBXLIBRARY_API __declspec(dllimport)
#endif

#include <fbxsdk.h>
#include <fstream>
#include "MaterialComponents.h"
#include "MeshComponents.h"

extern "C" {
	namespace FbxLibraryDLL
	{
		FBXLIBRARY_API bool LoadMeshFromFBXFile(const char* _fileName, std::vector<MeshComponents::BFMesh> & _outVector);
		FBXLIBRARY_API void ExportMeshToBinaryFile(const char* _filePath, MeshComponents::BFMesh _mesh);
		FBXLIBRARY_API bool ReadInBinaryMeshFile(const char * _fileName, MeshComponents::OutInformation& _objectToFill);
		
		FBXLIBRARY_API bool LoadMaterialFromFBXFile(const char* _fileName, std::vector<MaterialComponents::Material>& _material);
		FBXLIBRARY_API void ExportMaterialsToBinaryFile(const char* _filePath, std::vector<MaterialComponents::Material> _materials);
		FBXLIBRARY_API bool ReadInMaterialsFromBinaryFile(const char* _filePath, std::vector<MaterialComponents::Material>& _materials);
		FBXLIBRARY_API void DisplayMaterialPropertiesText(std::vector<MaterialComponents::Material>& _materials);

		FBXLIBRARY_API bool LoadAdvancedMeshFromFBXFile(const char* _fileName, std::vector<MeshComponentsAdvanced::OutInformationAdvanced>& _outVector);
		FBXLIBRARY_API void ExportAdvancedMeshToBinaryFile(const char* _filePath, MeshComponentsAdvanced::OutInformationAdvanced & _mesh);
		FBXLIBRARY_API bool ReadInAdvancedBinaryMeshFile(const char * _fileName, MeshComponentsAdvanced::OutInformationAdvanced& _objectToFill);
	}
}