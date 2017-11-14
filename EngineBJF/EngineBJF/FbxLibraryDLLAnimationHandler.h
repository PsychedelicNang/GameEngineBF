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
#include "MeshComponents.h"

class FbxLibraryDLLAnimationHandler {
public:
	FbxLibraryDLLAnimationHandler();
	~FbxLibraryDLLAnimationHandler();

	bool Initialize();
	bool LoadAnimationFBX(const char* _fileName, AnimationComponents::AnimationClip& _animationClip, std::vector<AnimationComponents::SkeletonJoints>& _skelJoints, float _scaleAmount = 1);
	bool LoadFBX(const char * _fileName, std::vector<MeshComponentsAnimation::OutInformationAdvanced>& _outVector, AnimationComponents::BindPose& _bindPose, AnimationComponents::AnimationClip & _animationClip, std::vector<AnimationComponents::SkeletonJoints>& _skelJoints, float _scaleAmount = 1);
private:
	HINSTANCE hinstLib;
	typedef bool(*funcLoadAnimationFromFBXFile)(const char*, AnimationComponents::AnimationClip&, std::vector<AnimationComponents::SkeletonJoints>&, float);		//  bool LoadAnimationFromFBXFile(const char* _fileName, AnimationComponents::AnimationClip& _animationClip, std::vector<AnimationComponents::SkeletonJoints>& _skelJoints, float _scaleAmount = 1);
	typedef bool(*funcLoadFBX)(const char *, std::vector<MeshComponentsAnimation::OutInformationAdvanced>&, AnimationComponents::BindPose&, AnimationComponents::AnimationClip&, std::vector<AnimationComponents::SkeletonJoints>&, float);

	funcLoadAnimationFromFBXFile funcHandleLoadAnimationFromFBXFile;																						// Pointer to LoadAnimationFromFBXFile function
	funcLoadFBX funcHandLoadFBX;
	//bool LoadAnimation(const char * _fileName, std::vector<MeshComponentsAnimation::OutInformationAdvanced>& _outVector, AnimationComponents::AnimationClip & _animationClip, std::vector<AnimationComponents::SkeletonJoints>& _skelJoints, float _scaleAmount)
private:
	bool InitializeLibrary();
	bool LoadAnimationFromFBXFile(const char* _fileName, AnimationComponents::AnimationClip& _animationClip, std::vector<AnimationComponents::SkeletonJoints>& _skelJoints, float _scaleAmount = 1);
};

#endif // !_FBXLIBRARYDLLANIMATIONHANDLER_H_