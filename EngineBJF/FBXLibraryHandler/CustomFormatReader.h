#pragma once
/***************************
* Filename: CustomFormatReader.h
***************************/
#ifndef _CUSTOMFORMATREADER_H_
#define _CUSTOMFORMATREADER_H_

/***************************
* INCLUDES
***************************/
#include <fstream>
#include "MeshComponents.h"
#include "MaterialComponents.h"
#include "AnimationComponents.h"

class CustomFormatReader {
public:
	bool ReadInBasicBinaryMeshFile(const char * _fileName, MeshComponentsBasic::OutInformation& _objectToFill, float _scaleAmount = 1.f);
	bool ReadInMaterialsFromBinaryFile(const char* _filePath, std::vector<MaterialComponents::Material>& _materials);
	void PrintMaterialProperties(std::vector<MaterialComponents::Material>& _materials);
	bool ReadInAdvancedBinaryMeshFile(const char * _fileName, MeshComponentsAdvanced::OutInformation& _objectToFill, float _scaleAmount = 1.f);
	bool ReadInAdvancedMeshWithSkinnedAnimationFromBinaryFile(const char* _fileName, MeshComponentsAnimation::OutInformation & _objectToFill,
		AnimationComponents::BindPose& _bindPose, AnimationComponents::AnimationClip& _animationClip, std::vector<AnimationComponents::SkeletonJoints>& _skelJoints);
};

#endif // !_CUSTOMFORMATREADER_H_