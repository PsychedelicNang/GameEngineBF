#include "FbxLibraryDLLMeshHandler.h"

FbxLibraryDLLMeshHandler::FbxLibraryDLLMeshHandler()
{
}

FbxLibraryDLLMeshHandler::~FbxLibraryDLLMeshHandler()
{
}

bool FbxLibraryDLLMeshHandler::Initialize()
{
	if (!InitializeLibrary()) return false;

	return true;
}

bool FbxLibraryDLLMeshHandler::LoadMeshFBX(const char * _FBXFileName, std::vector<MeshComponents::BFMesh>& _outVector)
{
	if (!LoadMeshFBXFromFile(_FBXFileName,  _outVector)) return false;

	return true;
}

void FbxLibraryDLLMeshHandler::ExportMesh(const char * _fileName, MeshComponents::BFMesh _mesh)
{
	ExportMeshToBinFile(_fileName, _mesh);
}

bool FbxLibraryDLLMeshHandler::LoadMeshBinary(const char * _fileName, MeshComponents::OutInformation & _objectToFill)
{
	if (!LoadMeshBinaryFromFile(_fileName, _objectToFill)) return false;
	
	return true;
}

bool FbxLibraryDLLMeshHandler::LoadAdvancedMeshFBX(const char * _fileName, std::vector<MeshComponentsAdvanced::OutInformationAdvanced>& _outVector)
{
	if (!LoadAdvancedMeshFBXFromFile(_fileName, _outVector)) return false;
	
	return true;
}

void FbxLibraryDLLMeshHandler::ExportAdvancedMesh(const char * _filePath, MeshComponentsAdvanced::OutInformationAdvanced & _mesh)
{
	ExportAdvancedMeshToBinFile(_filePath, _mesh);
}

bool FbxLibraryDLLMeshHandler::LoadAdvancedMeshBinary(const char * _fileName, MeshComponentsAdvanced::OutInformationAdvanced & _objectToFill)
{
	if (!LoadAdvancedMeshBinaryFromFile(_fileName, _objectToFill)) return false;

	return true;
}

bool FbxLibraryDLLMeshHandler::InitializeLibrary()
{
	hinstLib = LoadLibrary(L"FbxLibraryDLL.dll");
	
	if (!hinstLib) return false;
	
	funcHandleLoadMeshFromFBXFile = (funcLoadMeshFromFBXFile)GetProcAddress(hinstLib, "LoadMeshFromFBXFile");
	funcHandleExportMeshToBinaryFile = (funcExportMeshToBinaryFile)GetProcAddress(hinstLib, "ExportMeshToBinaryFile");
	funcHandleReadInBinaryMeshFile = (funcReadInBinaryMeshFile)GetProcAddress(hinstLib, "ReadInBinaryMeshFile");
	funcHandLoadAdvancedMeshFromFBXFile = (funcLoadAdvancedMeshFromFBXFile)GetProcAddress(hinstLib, "LoadAdvancedMeshFromFBXFile");
	funcHandExportAdvancedMeshToBinaryFile = (funcExportAdvancedMeshToBinaryFile)GetProcAddress(hinstLib, "ExportAdvancedMeshToBinaryFile");
	funcHandReadInAdvancedBinaryMeshFile = (funcReadInAdvancedBinaryMeshFile)GetProcAddress(hinstLib, "ReadInAdvancedBinaryMeshFile");

	if (!funcHandleLoadMeshFromFBXFile || !funcHandleExportMeshToBinaryFile || !funcHandleReadInBinaryMeshFile
		|| !funcHandLoadAdvancedMeshFromFBXFile || !funcHandExportAdvancedMeshToBinaryFile || !funcHandReadInAdvancedBinaryMeshFile) return false;

	return true;
}

bool FbxLibraryDLLMeshHandler::LoadMeshFBXFromFile(const char * _FBXFileName, std::vector<MeshComponents::BFMesh>& _outVector)
{
	if(!((funcHandleLoadMeshFromFBXFile)(_FBXFileName, _outVector))) return false;

	return true;
}

void FbxLibraryDLLMeshHandler::ExportMeshToBinFile(const char * _fileName, MeshComponents::BFMesh _mesh)
{
	(funcHandleExportMeshToBinaryFile)(_fileName, _mesh);
}

bool FbxLibraryDLLMeshHandler::LoadMeshBinaryFromFile(const char * _fileName, MeshComponents::OutInformation & _objectToFill)
{
	if (!(funcHandleReadInBinaryMeshFile)(_fileName, _objectToFill)) return false;

	return true;
}

bool FbxLibraryDLLMeshHandler::LoadAdvancedMeshFBXFromFile(const char * _fileName, std::vector<MeshComponentsAdvanced::OutInformationAdvanced>& _outVector)
{
	if (!((funcHandLoadAdvancedMeshFromFBXFile)(_fileName, _outVector))) return false;
	return true;
}

void FbxLibraryDLLMeshHandler::ExportAdvancedMeshToBinFile(const char * _filePath, MeshComponentsAdvanced::OutInformationAdvanced & _mesh)
{
	(funcHandExportAdvancedMeshToBinaryFile)(_filePath, _mesh);
}

bool FbxLibraryDLLMeshHandler::LoadAdvancedMeshBinaryFromFile(const char * _fileName, MeshComponentsAdvanced::OutInformationAdvanced & _objectToFill)
{
	if (!((funcHandReadInAdvancedBinaryMeshFile)(_fileName, _objectToFill))) return false;

	return true;
}