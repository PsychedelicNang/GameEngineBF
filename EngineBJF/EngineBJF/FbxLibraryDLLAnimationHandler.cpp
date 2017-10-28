#include "FbxLibraryDLLAnimationHandler.h"

FbxLibraryDLLAnimationHandler::FbxLibraryDLLAnimationHandler()
{
}

FbxLibraryDLLAnimationHandler::~FbxLibraryDLLAnimationHandler()
{
}

bool FbxLibraryDLLAnimationHandler::Initialize()
{
	if (!InitializeLibrary()) return false;
	return true;
}

bool FbxLibraryDLLAnimationHandler::LoadAnimationFBX(const char * _fileName, AnimationComponents::AnimationClip & _animationClip)
{
	if (!LoadAnimationFromFBXFile(_fileName, _animationClip)) return false;
	return true;
}

bool FbxLibraryDLLAnimationHandler::InitializeLibrary()
{
	hinstLib = LoadLibrary(L"FbxLibraryDLL.dll");

	if (!hinstLib) return false;

	funcHandleLoadAnimationFromFBXFile = (funcLoadAnimationFromFBXFile)GetProcAddress(hinstLib, "LoadAnimationFromFBXFile");
	
	if (!funcHandleLoadAnimationFromFBXFile) return false;

	return true;
}

bool FbxLibraryDLLAnimationHandler::LoadAnimationFromFBXFile(const char * _fileName, AnimationComponents::AnimationClip & _animationClip)
{
	if (!((funcHandleLoadAnimationFromFBXFile)(_fileName, _animationClip))) return false;
	return true;
}
