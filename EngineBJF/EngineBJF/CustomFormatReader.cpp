#include "CustomFormatReader.h"

bool CustomFormatReader::ReadInBasicBinaryMeshFile(const char * _fileName, MeshComponentsBasic::OutInformation & _objectToFill, float _scaleAmount)
{
	std::fstream file;
	file.open(_fileName, std::ios_base::binary | std::ios_base::in);

	if (file.is_open())
	{
		unsigned numOfIndices;
		unsigned numOfVertices;

		file.read((char*)&numOfIndices, 4);

		for (unsigned i = 0; i < numOfIndices; i++) {
			unsigned num = 0;
			file.read((char*)(&num), sizeof(unsigned));
			_objectToFill.indices.push_back(num);
		}

		file.read((char*)&numOfVertices, 4);

		MeshComponentsBasic::VertexPositionColor vert;

		for (unsigned i = 0; i < numOfVertices; i++)
		{
			file.read((char*)(&vert.position[0]), sizeof(float));
			file.read((char*)(&vert.position[1]), sizeof(float));
			file.read((char*)(&vert.position[2]), sizeof(float));
			file.read((char*)(&vert.position[3]), sizeof(float));

			// fill out the color as a ratio from the current vertice to the total number of vertices
			float amount = (float)i / numOfVertices;
			vert.color[0] = amount;
			vert.color[1] = amount;
			vert.color[2] = amount;
			vert.color[3] = 1.f;
			_objectToFill.vertices.push_back(vert);
		}

		for (unsigned i = 0; i < numOfVertices; i++)
			_objectToFill.vertices[i].position[3] = 1.f;

		if (_scaleAmount != 1.f)
		{
			for (size_t i = 0; i < numOfVertices; i++)
			{
				_objectToFill.vertices[i].position[0] *= _scaleAmount;
				_objectToFill.vertices[i].position[1] *= _scaleAmount;
				_objectToFill.vertices[i].position[2] *= _scaleAmount;
			}
		}

		file.close();
		return true;
	}

	// returns false if the file did not exist
	return false;
}
//
//bool CustomFormatReader::ReadInMaterialsFromBinaryFile(const char * _filePath, std::vector<MaterialComponents::Material>& _materials)
//{
//	std::fstream fileIn;
//	fileIn.open(_filePath, std::ios_base::binary | std::ios_base::in);
//	if (fileIn.is_open())
//	{
//		unsigned numOfMaterials;
//		fileIn.read((char*)&numOfMaterials, 4);
//
//		for (unsigned i = 0; i < numOfMaterials; i++)
//		{
//			MaterialComponents::Material currMaterial;
//			fileIn.read((char*)&currMaterial.m_materialType, 4);
//
//			unsigned numOfPropsInMap;
//			fileIn.read((char*)&numOfPropsInMap, 4);
//
//			for (unsigned j = 0; j < numOfPropsInMap; j++)
//			{
//				MaterialComponents::Material::properties ePropValue;
//				fileIn.read((char*)&ePropValue, 4);
//
//				unsigned filePathLength;
//				fileIn.read((char*)&filePathLength, 4);
//				char * cFilePath = new char[filePathLength];
//				fileIn.read(cFilePath, filePathLength);
//				std::string strFilePath = std::string(cFilePath);
//				delete[] cFilePath;
//
//				MaterialComponents::Material::properties_t tempProp_t;
//				tempProp_t.filePath = strFilePath;
//
//				fileIn.read((char*)&tempProp_t.value[0], 4);
//				fileIn.read((char*)&tempProp_t.value[1], 4);
//				fileIn.read((char*)&tempProp_t.value[2], 4);
//				fileIn.read((char*)&tempProp_t.value[3], 4);
//
//				currMaterial.m_mapPropValues[ePropValue] = tempProp_t;
//			}
//			_materials.push_back(currMaterial);
//		}
//		fileIn.close();
//		return true;
//	}
//
//	// returns false if the file did not exist
//	return false;
//}
//
//void CustomFormatReader::PrintMaterialProperties(std::vector<MaterialComponents::Material>& _materials)
//{
//	printf("New Object's Material...\n");
//	for (unsigned i = 0; i < _materials.size(); i++)
//	{
//		printf("Material %u:\n", i + 1);
//		MaterialComponents::Material::materialType mType = _materials[i].m_materialType;
//		switch (mType)
//		{
//		case MaterialComponents::Material::PHONG:
//			printf("PHONG:\n");
//			break;
//		case MaterialComponents::Material::LAMBERT:
//			printf("LAMBERT:\n");
//			break;
//		default:
//			printf("NO MATERIAL TYPE:\n");
//			break;
//		}
//		for (_materials[i].m_mapPropValuesIter = _materials[i].m_mapPropValues.begin(); _materials[i].m_mapPropValuesIter != _materials[i].m_mapPropValues.end(); _materials[i].m_mapPropValuesIter++)
//		{
//			MaterialComponents::Material::properties prop = _materials[i].m_mapPropValuesIter->first;
//			switch (prop)
//			{
//			case MaterialComponents::Material::EMISSIVE:
//				printf("EMISSIVE: ");
//				break;
//			case MaterialComponents::Material::AMBIENT:
//				printf("AMBIENT: ");
//				break;
//			case MaterialComponents::Material::DIFFUSE:
//				printf("DIFFUSE: ");
//				break;
//			case MaterialComponents::Material::NORMAL:
//				printf("NORMAL: ");
//				break;
//			case MaterialComponents::Material::BUMP:
//				printf("BUMP: ");
//				break;
//			case MaterialComponents::Material::TRANSPARENCY:
//				printf("TRANSPARENCY: ");
//				break;
//			case MaterialComponents::Material::DISPLACEMENT:
//				printf("DISPLACEMENT: ");
//				break;
//			case MaterialComponents::Material::VECTOR_DISPLACEMENT:
//				printf("VECTOR_DISPLACEMENT: ");
//				break;
//			case MaterialComponents::Material::SPECULAR:
//				printf("SPECULAR: ");
//				break;
//			case MaterialComponents::Material::SHININESS:
//				printf("SHININESS: ");
//				break;
//			case MaterialComponents::Material::REFLECTION:
//				printf("REFLECTION: ");
//				break;
//			case MaterialComponents::Material::COUNT:
//				printf("COUNT...NOT SUPPOSED TO HAPPEN: ");
//				break;
//			default:
//				printf("NO PROPERTY: ");
//				break;
//			}
//			printf("%f, %f, %f, %f\n", _materials[i].m_mapPropValuesIter->second.value[0], _materials[i].m_mapPropValuesIter->second.value[1], _materials[i].m_mapPropValuesIter->second.value[2], _materials[i].m_mapPropValuesIter->second.value[3]);
//			printf("File Path: ");
//			printf(_materials[i].m_mapPropValuesIter->second.filePath.c_str());
//			printf("\n\n");
//		}
//		printf("\n");
//	}
//}

bool CustomFormatReader::ReadInAdvancedBinaryMeshFile(const char * _fileName, MeshComponentsAdvanced::OutInformation & _objectToFill, float _scaleAmount)
{
	std::fstream file;
	file.open(_fileName, std::ios_base::binary | std::ios_base::in);

	if (file.is_open())
	{
		unsigned numOfIndices;
		unsigned numOfVertices;

		file.read((char*)&numOfIndices, 4);

		for (unsigned i = 0; i < numOfIndices; i++) {
			unsigned num = 0;
			file.read((char*)(&num), sizeof(4));
			_objectToFill.indices.push_back(num);
		}

		file.read((char*)&numOfVertices, 4);

		MeshComponentsAdvanced::VertexAdvanced vert;

		for (unsigned i = 0; i < numOfVertices; i++)
		{
			file.read((char*)(&vert.position[0]), sizeof(4));
			file.read((char*)(&vert.position[1]), sizeof(4));
			file.read((char*)(&vert.position[2]), sizeof(4));
			file.read((char*)(&vert.position[3]), sizeof(4));

			file.read((char*)(&vert.normals[0]), sizeof(4));
			file.read((char*)(&vert.normals[1]), sizeof(4));
			file.read((char*)(&vert.normals[2]), sizeof(4));
			file.read((char*)(&vert.normals[3]), sizeof(4));

			file.read((char*)(&vert.uvs[0]), sizeof(4));
			file.read((char*)(&vert.uvs[1]), sizeof(4));

			_objectToFill.vertices.push_back(vert);
		}

		for (unsigned i = 0; i < numOfVertices; i++)
			_objectToFill.vertices[i].position[3] = 1.f;

		if (_scaleAmount != 1.f)
		{
			for (size_t i = 0; i < numOfVertices; i++)
			{
				_objectToFill.vertices[i].position[0] *= _scaleAmount;
				_objectToFill.vertices[i].position[1] *= _scaleAmount;
				_objectToFill.vertices[i].position[2] *= _scaleAmount;
			}
		}

		file.close();
		return true;
	}

	// returns false if the file did not exist
	return false;
}

bool CustomFormatReader::ReadInAdvancedMeshWithSkinnedAnimationFromBinaryFile(const char * _fileName, MeshComponentsAnimation::OutInformation & _objectToFill, AnimationComponents::BindPose & _bindPose, AnimationComponents::AnimationClip & _animationClip, std::vector<AnimationComponents::SkeletonJoint>& _skelJoints)
{
	std::fstream file;
	file.open(_fileName, std::ios_base::binary | std::ios_base::in);
	if (file.is_open())
	{
		unsigned numOfIndices;
		unsigned numOfVertices;

		file.read((char*)(&numOfIndices), sizeof(unsigned));

		for (unsigned i = 0; i < numOfIndices; i++) {
			unsigned num = 0;
			file.read((char*)(&num), sizeof(unsigned));
			_objectToFill.indices.push_back(num);
		}

		file.read((char*)&numOfVertices, sizeof(unsigned));

		MeshComponentsAnimation::VertexAdvanced vert;

		for (unsigned i = 0; i < numOfVertices; i++)
		{
			file.read((char*)(&vert.position[0]), sizeof(float));
			file.read((char*)(&vert.position[1]), sizeof(float));
			file.read((char*)(&vert.position[2]), sizeof(float));
			file.read((char*)(&vert.position[3]), sizeof(float));

			file.read((char*)(&vert.normals[0]), sizeof(float));
			file.read((char*)(&vert.normals[1]), sizeof(float));
			file.read((char*)(&vert.normals[2]), sizeof(float));
			file.read((char*)(&vert.normals[3]), sizeof(float));

			file.read((char*)(&vert.uvs[0]), sizeof(float));
			file.read((char*)(&vert.uvs[1]), sizeof(float));

			file.read((char*)&vert.weights[0], sizeof(float));
			file.read((char*)&vert.weights[1], sizeof(float));
			file.read((char*)&vert.weights[2], sizeof(float));
			file.read((char*)&vert.weights[3], sizeof(float));

			file.read((char*)&vert.joints[0], sizeof(int));
			file.read((char*)&vert.joints[1], sizeof(int));
			file.read((char*)&vert.joints[2], sizeof(int));
			file.read((char*)&vert.joints[3], sizeof(int));

			_objectToFill.vertices.push_back(vert);
		}

		for (unsigned i = 0; i < numOfVertices; i++)
			_objectToFill.vertices[i].position[3] = 1.f;

		unsigned bindPoseJointCount;
		file.read((char*)(&bindPoseJointCount), sizeof(unsigned));
		_bindPose.joints.resize(bindPoseJointCount);

		for (unsigned i = 0; i < bindPoseJointCount; i++)
		{
			file.read((char*)&_bindPose.joints[i].parentIndex, sizeof(unsigned));

			for (unsigned j = 0; j < 16; j++)
			{
				file.read((char*)(&_bindPose.joints[i].globalTransformArray[j]), sizeof(float));
			}

			unsigned filePathLength;
			file.read((char*)&filePathLength, sizeof(unsigned));
			char * cFilePath = new char[filePathLength];
			file.read(cFilePath, filePathLength);
			std::string strFilePath = std::string(cFilePath);
			delete[] cFilePath;

			_bindPose.joints[i].jointName = strFilePath;
		}

		file.read((char*)(&_animationClip.duration), sizeof(double));

		unsigned keyframeCount;
		file.read((char*)(&keyframeCount), sizeof(unsigned));
		_animationClip.frames.resize(keyframeCount);

		for (unsigned i = 0; i < keyframeCount; i++)
		{
			file.read((char*)(&_animationClip.frames[i].time), sizeof(double));

			unsigned animFramesJointsCount;
			file.read((char*)&animFramesJointsCount, sizeof(unsigned));

			_animationClip.frames[i].joints.resize(animFramesJointsCount);

			for (unsigned j = 0; j < animFramesJointsCount; j++)
			{
				file.read((char*)(&_animationClip.frames[i].joints[j].parentIndex), sizeof(unsigned));
				for (unsigned k = 0; k < 16; k++)
				{
					file.read((char*)&_animationClip.frames[i].joints[j].globalTransformArray[k], sizeof(float));
				}
				unsigned filePathLength;
				file.read((char*)&filePathLength, sizeof(unsigned));
				char * cFilePath = new char[filePathLength];
				file.read(cFilePath, filePathLength);
				std::string strFilePath = std::string(cFilePath);
				delete[] cFilePath;

				_animationClip.frames[i].joints[j].jointName = strFilePath;
			}
		}

		unsigned skelJointsCount;
		file.read((char*)&skelJointsCount, sizeof(unsigned));
		_skelJoints.resize(skelJointsCount);

		for (unsigned i = 0; i < skelJointsCount; i++)
		{
			file.read((char*)(&_skelJoints[i].parentIndex), sizeof(unsigned));

			for (unsigned j = 0; j < 16; j++)
			{
				file.read((char*)(&_skelJoints[i].globalTransformArray[j]), sizeof(float));
			}

			unsigned filePathLength;
			file.read((char*)&filePathLength, sizeof(unsigned));
			char * cFilePath = new char[filePathLength];
			file.read(cFilePath, filePathLength);
			std::string strFilePath = std::string(cFilePath);
			delete[] cFilePath;

			_skelJoints[i].jointName = strFilePath;
		}

		file.close();
		return true;
	}

	// returns false if the file did not exist
	return false;
}