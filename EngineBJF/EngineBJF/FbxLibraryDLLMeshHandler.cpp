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

bool FbxLibraryDLLMeshHandler::LoadAdvancedMeshWithSkinnedAnimationFBX(const char * _filePath, std::vector<MeshComponentsAnimation::OutInformationAdvanced>& _outVector)
{
	if (!LoadAdvancedMeshWithSkinnedAnimationFBXFromFile(_filePath, _outVector)) return false;

	return true;
}

void FbxLibraryDLLMeshHandler::ExportAdvancedMeshWithSkinnedAnimationBinary(const char * _filePath, MeshComponentsAnimation::OutInformationAdvanced & _mesh)
{
	ExportAdvancedMeshWithSkinnedAnimationToBinaryFile(_filePath, _mesh);
}

bool FbxLibraryDLLMeshHandler::LoadAdvancedMeshWithSkinnedAnimationBinary(const char * _fileName, MeshComponentsAnimation::OutInformationAdvanced & _objectToFill)
{
	if (!LoadAdvancedMeshWithSkinnedAnimationFromBinaryFile(_fileName, _objectToFill)) return false;

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

	funcHandLoadAdvancedMeshWithSkinnedAnimationFromFBXFile = (funcLoadAdvancedMeshWithSkinnedAnimationFromFBXFile)GetProcAddress(hinstLib, "LoadAdvancedMeshWithSkinnedAnimationFromFBXFile");
	funcHandExportAdvancedMeshWithSkinnedAnimationBinary = (funcExportAdvancedMeshWithSkinnedAnimationBinary)GetProcAddress(hinstLib, "ExportAdvancedMeshWithSkinnedAnimationToBinaryFile");
	funcHandLoadAdvancedMeshWithSkinnedAnimationBinary = (funcLoadAdvancedMeshWithSkinnedAnimationBinary)GetProcAddress(hinstLib, "ReadInAdvancedMeshWithSkinnedAnimationFromBinaryFile");

	if (!funcHandleLoadMeshFromFBXFile || !funcHandleExportMeshToBinaryFile || !funcHandleReadInBinaryMeshFile
		|| !funcHandLoadAdvancedMeshFromFBXFile || !funcHandExportAdvancedMeshToBinaryFile || !funcHandReadInAdvancedBinaryMeshFile
		|| !funcHandLoadAdvancedMeshWithSkinnedAnimationFromFBXFile || !funcHandExportAdvancedMeshWithSkinnedAnimationBinary || !funcHandLoadAdvancedMeshWithSkinnedAnimationBinary) return false;

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

bool FbxLibraryDLLMeshHandler::LoadAdvancedMeshWithSkinnedAnimationFBXFromFile(const char * _fileName, std::vector<MeshComponentsAnimation::OutInformationAdvanced>& _outVector)
{
	if (!((funcHandLoadAdvancedMeshWithSkinnedAnimationFromFBXFile)(_fileName, _outVector))) return false;

	return true;
}

void FbxLibraryDLLMeshHandler::ExportAdvancedMeshWithSkinnedAnimationToBinaryFile(const char * _filePath, MeshComponentsAnimation::OutInformationAdvanced & _mesh)
{
	(funcHandExportAdvancedMeshWithSkinnedAnimationBinary)(_filePath, _mesh);
}

bool FbxLibraryDLLMeshHandler::LoadAdvancedMeshWithSkinnedAnimationFromBinaryFile(const char * _fileName, MeshComponentsAnimation::OutInformationAdvanced & _objectToFill)
{
	if (!((funcHandLoadAdvancedMeshWithSkinnedAnimationBinary)(_fileName, _objectToFill))) return false;

	return true;
}
