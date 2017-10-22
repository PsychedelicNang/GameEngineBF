#pragma once
/***************************
* Filename: FbxLibraryDLLMaterialHandler.h
***************************/
#ifndef _FBXLIBRARYDLLMATERIALHANDLER_H_
#define _FBXLIBRARYDLLMATERIALHANDLER_H_

/***************************
* INCLUDES
***************************/
#include "IncludesBJF.h"
#include "MaterialComponents.h"

class FbxLibraryDLLMaterialHandler {
public:
	FbxLibraryDLLMaterialHandler();
	~FbxLibraryDLLMaterialHandler();

	bool Initialize();
	bool LoadMaterialFBX(const char* _fileName, std::vector<MaterialComponents::Material>& _material);
	void ExportMaterialsBinary(const char* _filePath, std::vector<MaterialComponents::Material> _materials);
	bool LoadMaterialsBinary(const char* _filePath, std::vector<MaterialComponents::Material>& _materials);
	void DisplayMaterialPropertiesInText(std::vector<MaterialComponents::Material>& _materials);
private:
	HINSTANCE hinstLib;
	typedef bool (*funcLoadMaterialFromFBXFile)(const char*, std::vector<MaterialComponents::Material>&);		// bool LoadMaterialFromFBXFile(const char* _fileName, std::vector<MaterialComponents::Material>& _material);
	typedef void(*funcExportMaterialsToBinaryFile)(const char*, std::vector<MaterialComponents::Material>);		// void ExportMaterialsToBinaryFile(const char* _filePath, std::vector<MaterialComponents::Material> _materials);
	typedef bool(*funcReadInMaterialsFromBinaryFile)(const char*, std::vector<MaterialComponents::Material>&);	// bool ReadInMaterialsFromBinaryFile(const char* _filePath, std::vector<MaterialComponents::Material>& _materials);
	typedef void(*funcDisplayMaterialPropertiesText)(std::vector<MaterialComponents::Material>&);				// void DisplayMaterialPropertiesText(std::vector<MaterialComponents::Material>& _materials);

	funcLoadMaterialFromFBXFile			funcHandleLoadMaterialFromFBXFile;										// Pointer to LoadMaterialFromFBXFile function
	funcExportMaterialsToBinaryFile		funcHandleExportMaterialsToBinaryFile;									// Pointer to ExportMaterialsToBinaryFile function
	funcReadInMaterialsFromBinaryFile	funcHandleReadInMaterialsFromBinaryFile;								// Pointer to ReadInMaterialsFromBinaryFile function
	funcDisplayMaterialPropertiesText	funcHandleDisplayMaterialPropertiesText;								// Pointer to DisplayMaterialPropertiesText function

private:
	bool InitializeLibrary();
	bool LoadMaterialFBXFromFile(const char* _fileName, std::vector<MaterialComponents::Material>& _material);
	void ExportMaterialsToBinraryFile(const char* _filePath, std::vector<MaterialComponents::Material> _materials);
	bool LoadMaterialsBinaryFromFile(const char* _filePath, std::vector<MaterialComponents::Material>& _materials);
	void DisplayMaterialPropertiesInTextToScreen(std::vector<MaterialComponents::Material>& _materials);
};

#endif // !_FBXLIBRARYDLLMATERIALHANDLER_H_