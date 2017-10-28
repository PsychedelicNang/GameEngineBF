#pragma once
/***************************
* Filename: FbxLibraryDLLMeshHandler.h
***************************/
#ifndef _FBXLIBRARYDLLMESHHANDLER_H_
#define _FBXLIBRARYDLLMESHHANDLER_H_

/***************************
* INCLUDES
***************************/
#include <Windows.h>
#include "MeshComponents.h"

class FbxLibraryDLLMeshHandler {
public:
	FbxLibraryDLLMeshHandler();
	~FbxLibraryDLLMeshHandler();

	bool Initialize();
	bool LoadMeshFBX(const char* _FBXFileName, std::vector<MeshComponents::BFMesh> & _outVector);										// Standard meshes
	void ExportMesh(const char* _fileName, MeshComponents::BFMesh _mesh);																// Standard meshes
	bool LoadMeshBinary(const char * _fileName, MeshComponents::OutInformation& _objectToFill);											// Standard meshes

	bool LoadAdvancedMeshFBX(const char* _fileName, std::vector<MeshComponentsAdvanced::OutInformationAdvanced>& _outVector);			// Advanced meshes
	void ExportAdvancedMesh(const char* _filePath, MeshComponentsAdvanced::OutInformationAdvanced & _mesh);								// Advanced meshes
	bool LoadAdvancedMeshBinary(const char * _fileName, MeshComponentsAdvanced::OutInformationAdvanced& _objectToFill);					// Advanced meshes

private:
	HINSTANCE hinstLib;
	typedef bool(*funcLoadMeshFromFBXFile)(const char*, std::vector<MeshComponents::BFMesh>&);											// bool LoadMeshFromFBXFile(const char* _fileName, std::vector<BFMesh> & _outVector)
	typedef void(*funcExportMeshToBinaryFile)(const char*, MeshComponents::BFMesh);														// void ExportMeshToBinaryFile(const char* _filePath, BFMesh _mesh)
	typedef bool(*funcReadInBinaryMeshFile)(const char *, MeshComponents::OutInformation&);												// bool ReadInBinaryMeshFile(const char * _fileName, MeshComponents::OutInformation& _objectToFill);

	typedef bool(*funcLoadAdvancedMeshFromFBXFile)(const char*, std::vector<MeshComponentsAdvanced::OutInformationAdvanced>&);			// bool LoadAdvancedMeshFromFBXFile(const char* _fileName, std::vector<MeshComponentsAdvanced::OutInformationAdvanced>& _outVector);
	typedef void(*funcExportAdvancedMeshToBinaryFile)(const char*, MeshComponentsAdvanced::OutInformationAdvanced &);					// void ExportAdvancedMeshToBinaryFile(const char* _filePath, MeshComponentsAdvanced::OutInformationAdvanced & _mesh);
	typedef bool(*funcReadInAdvancedBinaryMeshFile)(const char*, MeshComponentsAdvanced::OutInformationAdvanced&);						// bool ReadInAdvancedBinaryMeshFile(const char * _fileName, MeshComponentsAdvanced::OutInformationAdvanced& _objectToFill);

	funcLoadMeshFromFBXFile				funcHandleLoadMeshFromFBXFile;																	// Pointer to LoadMeshFromFBXFile function
	funcExportMeshToBinaryFile			funcHandleExportMeshToBinaryFile;																// Pointer to ExportMeshToBinaryFile function
	funcReadInBinaryMeshFile			funcHandleReadInBinaryMeshFile;																	// Pointer to ReadInBinaryMeshFile function

	funcLoadAdvancedMeshFromFBXFile		funcHandLoadAdvancedMeshFromFBXFile;															// Pointer to LoadAdvancedMeshFromFBXFile function
	funcExportAdvancedMeshToBinaryFile	funcHandExportAdvancedMeshToBinaryFile;															// Pointer to ExportAdvancedMeshToBinaryFile function
	funcReadInAdvancedBinaryMeshFile	funcHandReadInAdvancedBinaryMeshFile;															// Pointer to ReadInAdvancedBinaryMeshFile function

private:
	bool InitializeLibrary();
	
	bool LoadMeshFBXFromFile(const char* _FBXFileName, std::vector<MeshComponents::BFMesh> & _outVector);								// Standard meshes
	void ExportMeshToBinFile(const char* _fileName, MeshComponents::BFMesh _mesh);														// Standard meshes	
	bool LoadMeshBinaryFromFile(const char * _fileName, MeshComponents::OutInformation& _objectToFill);									// Standard meshes

	bool LoadAdvancedMeshFBXFromFile(const char* _fileName, std::vector<MeshComponentsAdvanced::OutInformationAdvanced>& _outVector);	// Advanced meshes
	void ExportAdvancedMeshToBinFile(const char* _filePath, MeshComponentsAdvanced::OutInformationAdvanced & _mesh);					// Advanced meshes
	bool LoadAdvancedMeshBinaryFromFile(const char * _fileName, MeshComponentsAdvanced::OutInformationAdvanced& _objectToFill);			// Advanced meshes
};

#endif // !_FBXLIBRARYDLLMESHHANDLER_H_