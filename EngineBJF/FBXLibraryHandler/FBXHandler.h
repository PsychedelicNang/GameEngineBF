#pragma once
/***************************
* Filename: FBXHandler.h
***************************/
#ifndef _FBXHANDLER_H_
#define _FBXHANDLER_H_

/***************************
* INCLUDES
***************************/
#include <fbxsdk.h>
#include <fstream>
#include "MeshComponents.h"
#include "MaterialComponents.h"
#include "AnimationComponents.h"

class FBXHandler {
	struct MyFBXJoint {
		FbxNode* node;
		int parentIndex;
		MyFBXJoint() {
			node = nullptr;
			parentIndex = 0;
		}
		MyFBXJoint(FbxNode* _node, int _parentIndex) {
			node = _node;
			parentIndex = _parentIndex;
		}
	};
	std::vector<MyFBXJoint*> fbxJoints;
	std::vector<MaterialComponents::Material> m_materials;
	std::vector<AnimationComponents::SkeletonJoints> m_skelJoints;

public:
	enum FrameRate {
		frame24 = 0,
		frame30,
		frame60
	};

	bool LoadBasicMeshFromFBXFile(const char* _fileName, std::vector<MeshComponentsBasic::Mesh>& _outVector);
	void ExportBasicMeshToBinaryFile(const char* _filePath, MeshComponentsBasic::Mesh _mesh);
	bool ReadInBasicBinaryMeshFile(const char * _fileName, MeshComponentsBasic::OutInformation& _objectToFill, float _scaleAmount = 1.f);

	bool LoadMaterialFromFBXFile(const char* _fileName, std::vector<MaterialComponents::Material>& _material);
	void ExportMaterialsToBinaryFile(const char* _filePath, std::vector<MaterialComponents::Material> _materials);
	bool ReadInMaterialsFromBinaryFile(const char* _filePath, std::vector<MaterialComponents::Material>& _materials);
	void PrintMaterialProperties(std::vector<MaterialComponents::Material>& _materials);

	bool LoadAdvancedMeshFromFBXFile(const char* _fileName, std::vector<MeshComponentsAdvanced::OutInformation>& _outVector);
	void ExportAdvancedMeshToBinaryFile(const char* _filePath, MeshComponentsAdvanced::OutInformation & _mesh);
	bool ReadInAdvancedBinaryMeshFile(const char * _fileName, MeshComponentsAdvanced::OutInformation& _objectToFill, float _scaleAmount = 1.f);

	bool LoadAdvancedMeshWithSkinnedAndSkeletalAnimationFromFBXFile(const char* _fileName, std::vector<MeshComponentsAnimation::OutInformation>& _outVector,
		AnimationComponents::BindPose& _bindPose, AnimationComponents::AnimationClip& _animationClip, std::vector<AnimationComponents::SkeletonJoints>& _skelJoints, FrameRate _frameRate, float _scaleAmount = 1.f);

	void ExportAdvancedMeshWithSkinnedAnimationToBinaryFile(const char* _filePath, MeshComponentsAnimation::OutInformation & _mesh);
	void ExportAdvancedMeshWithSkinnedAnimationToBinaryFile(const char* _fileName, MeshComponentsAnimation::OutInformation & _mesh,
		AnimationComponents::BindPose& _bindPose, AnimationComponents::AnimationClip& _animationClip, std::vector<AnimationComponents::SkeletonJoints>& _skelJoints);
	
	bool ReadInAdvancedMeshWithSkinnedAnimationFromBinaryFile(const char * _fileName, MeshComponentsAnimation::OutInformation& _objectToFill);
	bool ReadInAdvancedMeshWithSkinnedAnimationFromBinaryFile(const char* _fileName, MeshComponentsAnimation::OutInformation & _objectToFill,
		AnimationComponents::BindPose& _bindPose, AnimationComponents::AnimationClip& _animationClip, std::vector<AnimationComponents::SkeletonJoints>& _skelJoints);
};
#endif // !_FBXHANDLER_H_