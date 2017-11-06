#pragma once
#pragma once
/***************************
* Filename: FbxLibraryDLLAnimationlHandler.h
***************************/
#ifndef _FBXLIBRARYDLLANIMATIONHANDLER_H_
#define _FBXLIBRARYDLLANIMATIONHANDLER_H_

/***************************
* INCLUDES
***************************/
#include <Windows.h>
#include "AnimationComponents.h"

class FbxLibraryDLLAnimationHandler {
public:
	FbxLibraryDLLAnimationHandler();
	~FbxLibraryDLLAnimationHandler();

	bool Initialize();
	bool LoadAnimationFBX(const char* _fileName, AnimationComponents::AnimationClip& _animationClip, std::vector<AnimationComponents::SkeletonJoints>& _skelJoints, float _scaleAmount = 1);

private:
	HINSTANCE hinstLib;
	typedef bool(*funcLoadAnimationFromFBXFile)(const char*, AnimationComponents::AnimationClip&, std::vector<AnimationComponents::SkeletonJoints>&, float);		//  bool LoadAnimationFromFBXFile(const char* _fileName, AnimationComponents::AnimationClip& _animationClip, std::vector<AnimationComponents::SkeletonJoints>& _skelJoints, float _scaleAmount = 1);

	funcLoadAnimationFromFBXFile funcHandleLoadAnimationFromFBXFile;																						// Pointer to LoadAnimationFromFBXFile function

private:
	bool InitializeLibrary();
	bool LoadAnimationFromFBXFile(const char* _fileName, AnimationComponents::AnimationClip& _animationClip, std::vector<AnimationComponents::SkeletonJoints>& _skelJoints, float _scaleAmount = 1);
};

#endif // !_FBXLIBRARYDLLANIMATIONHANDLER_H_