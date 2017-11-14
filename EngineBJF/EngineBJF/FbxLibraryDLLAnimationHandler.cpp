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

bool FbxLibraryDLLAnimationHandler::LoadAnimationFBX(const char * _fileName, AnimationComponents::AnimationClip & _animationClip, std::vector<AnimationComponents::SkeletonJoints>& _skelJoints, float _scaleAmount)
{
	if (!LoadAnimationFromFBXFile(_fileName, _animationClip, _skelJoints, _scaleAmount)) return false;
	return true;
}

bool FbxLibraryDLLAnimationHandler::LoadFBX(const char * _fileName, std::vector<MeshComponentsAnimation::OutInformationAdvanced>& _outVector, AnimationComponents::AnimationClip & _animationClip, std::vector<AnimationComponents::SkeletonJoints>& _skelJoints, float _scaleAmount)
{
	if (!((funcHandLoadFBX(_fileName, _outVector, _animationClip, _skelJoints, _scaleAmount)))) return false;

	return true;
}

bool FbxLibraryDLLAnimationHandler::InitializeLibrary()
{
	hinstLib = LoadLibrary(L"FbxLibraryDLL.dll");

	if (!hinstLib) return false;

	funcHandleLoadAnimationFromFBXFile = (funcLoadAnimationFromFBXFile)GetProcAddress(hinstLib, "LoadAnimationFromFBXFile");
	funcHandLoadFBX = (funcLoadFBX)GetProcAddress(hinstLib, "LoadAnimation");
	if (!funcHandleLoadAnimationFromFBXFile || !funcHandLoadFBX) return false;

	return true;
}

bool FbxLibraryDLLAnimationHandler::LoadAnimationFromFBXFile(const char * _fileName, AnimationComponents::AnimationClip & _animationClip, std::vector<AnimationComponents::SkeletonJoints>& _skelJoints, float _scaleAmount)
{
	if (!((funcHandleLoadAnimationFromFBXFile)(_fileName, _animationClip, _skelJoints, _scaleAmount))) return false;
	return true;
}
