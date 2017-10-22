#include "FbxLibraryDLLMaterialHandler.h"

FbxLibraryDLLMaterialHandler::FbxLibraryDLLMaterialHandler()
{
}

FbxLibraryDLLMaterialHandler::~FbxLibraryDLLMaterialHandler()
{
}

bool FbxLibraryDLLMaterialHandler::Initialize()
{
	if (!InitializeLibrary()) return false;

	return true;
}

bool FbxLibraryDLLMaterialHandler::LoadMaterialFBX(const char * _fileName, std::vector<MaterialComponents::Material>& _material)
{
	if (!LoadMaterialFBXFromFile(_fileName, _material)) return false;
	
	return true;
}

void FbxLibraryDLLMaterialHandler::ExportMaterialsBinary(const char * _filePath, std::vector<MaterialComponents::Material> _materials)
{
	ExportMaterialsToBinraryFile(_filePath, _materials);
}

bool FbxLibraryDLLMaterialHandler::LoadMaterialsBinary(const char * _filePath, std::vector<MaterialComponents::Material>& _materials)
{
	if (!LoadMaterialsBinaryFromFile(_filePath, _materials)) return false;
	return true;
}

void FbxLibraryDLLMaterialHandler::DisplayMaterialPropertiesInText(std::vector<MaterialComponents::Material>& _materials)
{
	DisplayMaterialPropertiesInTextToScreen(_materials);
}

bool FbxLibraryDLLMaterialHandler::InitializeLibrary()
{
	hinstLib = LoadLibrary(L"FbxLibraryDLL.dll");
		
	if (!hinstLib) return false;

	funcHandleLoadMaterialFromFBXFile = (funcReadInMaterialsFromBinaryFile)GetProcAddress(hinstLib, "LoadMaterialFromFBXFile");
	funcHandleExportMaterialsToBinaryFile = (funcExportMaterialsToBinaryFile)GetProcAddress(hinstLib, "ExportMaterialsToBinaryFile");
	funcHandleReadInMaterialsFromBinaryFile = (funcReadInMaterialsFromBinaryFile)GetProcAddress(hinstLib, "ReadInMaterialsFromBinaryFile");
	funcHandleDisplayMaterialPropertiesText = (funcDisplayMaterialPropertiesText)GetProcAddress(hinstLib, "DisplayMaterialPropertiesText");

	if (!funcHandleLoadMaterialFromFBXFile || !funcHandleExportMaterialsToBinaryFile || !funcHandleReadInMaterialsFromBinaryFile || !funcHandleDisplayMaterialPropertiesText) return false;

	return true;
}

bool FbxLibraryDLLMaterialHandler::LoadMaterialFBXFromFile(const char * _fileName, std::vector<MaterialComponents::Material>& _material)
{
	if (!((funcHandleLoadMaterialFromFBXFile)(_fileName, _material))) return false;

	return true;
}

void FbxLibraryDLLMaterialHandler::ExportMaterialsToBinraryFile(const char * _filePath, std::vector<MaterialComponents::Material> _materials)
{
	(funcHandleExportMaterialsToBinaryFile)(_filePath, _materials);
}

bool FbxLibraryDLLMaterialHandler::LoadMaterialsBinaryFromFile(const char * _filePath, std::vector<MaterialComponents::Material>& _materials)
{
	if (!((funcHandleReadInMaterialsFromBinaryFile)(_filePath, _materials))) return false;

	return true;
}

void FbxLibraryDLLMaterialHandler::DisplayMaterialPropertiesInTextToScreen(std::vector<MaterialComponents::Material>& _materials)
{
	(funcHandleDisplayMaterialPropertiesText)(_materials);
}
