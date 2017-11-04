#include "FbxLibraryDLL.h"

namespace FbxLibraryDLL
{
	std::vector<MaterialComponents::Material> m_materials;
	MaterialComponents::Material::properties_t PropertyHelper(MaterialComponents::Material& _material, FbxProperty& _property, MaterialComponents::Material::properties _eValue);

	FBXLIBRARY_API bool LoadMeshFromFBXFile(const char* _fileName, std::vector<MeshComponents::BFMesh> & _outVector) {
		// Initialize the SDK manager. This object handles all our memory management.
		FbxManager* lSdkManager = FbxManager::Create();

		// Create the IO settings object.
		FbxIOSettings *ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
		lSdkManager->SetIOSettings(ios);

		// Create an importer using the SDK manager.
		FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");

		// Use the first argument as the filename for the importer.
		if (!lImporter->Initialize(_fileName, -1, lSdkManager->GetIOSettings())) {
			return false;
		}

		// Create a new scene so that it can be populated by the imported file.
		FbxScene* lScene = FbxScene::Create(lSdkManager, "myScene");

		// Import the contents of the file into the scene.
		lImporter->Import(lScene);

		// The file is imported; so get rid of the importer.
		lImporter->Destroy();

		FbxNode* lRootNode = lScene->GetRootNode();
		if (lRootNode)
		{
			for (int i = 0; i < lRootNode->GetChildCount(); i++)
			{
				FbxNode* tNode = lRootNode->GetChild(i);
				FbxGeometry* geometry = (FbxGeometry*)tNode->GetNodeAttribute();
				FbxNodeAttribute::EType geoNodeType = geometry->GetAttributeType();
				if (FbxNodeAttribute::eMesh == geoNodeType)
				{
					//then we have a mesh
					//// Misleading name, returns index array as int*
					//int* verts = theMesh->GetPolygonVertices();

					//// Total number of unique vertex positions
					//int numOfUniqueVertPos = geometry->GetControlPointsCount();

					//// Returns unique vertex positions array as FbxVector4*
					//FbxVector4* uniqueVertsPos = geometry->GetControlPoints();

					//FbxMesh* theMesh = FbxMesh::Create(geometry, "mesh");	// doesn't work??
					FbxMesh* theMesh = (FbxMesh*)geometry;
					MeshComponents::BFMesh meshInst;
					int indexCount = theMesh->GetPolygonVertexCount();
					meshInst.indexBuffer.resize(indexCount);

					int* verts = theMesh->GetPolygonVertices();
					for (int i = 0; i < indexCount; i++)
						meshInst.indexBuffer[i] = verts[i];

					for (int j = 0; j < geometry->GetControlPointsCount(); j++)
					{
						MeshComponents::Vector4 currPos;
						currPos.x = (float)theMesh->GetControlPoints()[j][0];
						currPos.y = (float)theMesh->GetControlPoints()[j][1];
						currPos.z = (float)theMesh->GetControlPoints()[j][2];
						currPos.w = (float)theMesh->GetControlPoints()[j][3];
						meshInst.verticesBuffer.push_back(currPos);
					}
					_outVector.push_back(meshInst);
				}
			}
		}
		// Destroy the SDK manager and all the other objects it was handling.
		lSdkManager->Destroy();
		return true;
	}

	FBXLIBRARY_API void ExportMeshToBinaryFile(const char* _filePath, MeshComponents::BFMesh _mesh) {
		std::fstream file;
		file.open(_filePath, std::ios_base::binary | std::ios_base::out);

		unsigned numOfIndices = (unsigned)_mesh.indexBuffer.size();
		file.write((char*)&numOfIndices, sizeof(numOfIndices));

		for (int i = 0; i < _mesh.indexBuffer.size(); i++)
			file.write((char*)(&_mesh.indexBuffer[i]), sizeof(_mesh.indexBuffer[i]));

		unsigned numOfVertices = (unsigned)_mesh.verticesBuffer.size();
		file.write((char*)&numOfVertices, sizeof(numOfVertices));

		for (int i = 0; i < _mesh.verticesBuffer.size(); i++)
		{
			file.write((char*)(&_mesh.verticesBuffer[i].x), sizeof(_mesh.verticesBuffer[i].x));
			file.write((char*)(&_mesh.verticesBuffer[i].y), sizeof(_mesh.verticesBuffer[i].y));
			file.write((char*)(&_mesh.verticesBuffer[i].z), sizeof(_mesh.verticesBuffer[i].z));
			file.write((char*)(&_mesh.verticesBuffer[i].w), sizeof(_mesh.verticesBuffer[i].w));
		}

		file.close();
	}

	FBXLIBRARY_API bool ReadInBinaryMeshFile(const char * _fileName, MeshComponents::OutInformation& _objectToFill)
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
				_objectToFill.oi_indices.push_back(num);
			}

			file.read((char*)&numOfVertices, 4);

			MeshComponents::VertexPositionColor vert;

			for (unsigned i = 0; i < numOfVertices; i++)
			{
				file.read((char*)(&vert.position[0]), sizeof(float));
				file.read((char*)(&vert.position[1]), sizeof(float));
				file.read((char*)(&vert.position[2]), sizeof(float));
				file.read((char*)(&vert.position[3]), sizeof(float));
				float amount = (float)i / numOfVertices;
				vert.color[0] = amount;
				vert.color[1] = amount;
				vert.color[2] = amount;
				vert.color[3] = 1.f;
				_objectToFill.oi_vertices.push_back(vert);
			}

			for (unsigned i = 0; i < numOfVertices; i++)
				_objectToFill.oi_vertices[i].position[3] = 1.f;

			file.close();
			return true;
		}
		return false;
	}

	/*
	* Fills out values for the materials property, both of which are passed into the function.
	* The _eValue determines the key for the std::map with is being used inside of the Materials structure
	*/
	MaterialComponents::Material::properties_t PropertyHelper(MaterialComponents::Material& _material, FbxProperty& _property, MaterialComponents::Material::properties _eValue) {
		_material.m_mapPropValuesIter = _material.m_mapPropValues.find(_eValue);
		MaterialComponents::Material::properties_t tempProp;

		if (_material.m_mapPropValuesIter != _material.m_mapPropValues.end()) {		//if the key exists
			tempProp = _material.m_mapPropValues[_eValue];							// add to it
			if (_property.GetPropertyDataType().GetType() == eFbxDouble3) {
				FbxDouble3 val = _property.Get<FbxDouble3>();
				tempProp.value[0] = (float)val[0];
				tempProp.value[1] = (float)val[1];
				tempProp.value[2] = (float)val[2];
			}
			else if (_property.GetPropertyDataType().GetType() == eFbxDouble) {
				tempProp.value[3] = (float)_property.Get<FbxDouble>();
			}

			if (tempProp.filePath == "WasNotGiven")
			{
				FbxFileTexture* lFileTexture = _property.GetSrcObject<FbxFileTexture>();
				if (lFileTexture != nullptr)
				{
					const char * cName = lFileTexture->GetRelativeFileName();
					std::string sName = std::string(cName);
					tempProp.filePath = sName;
				}
				else tempProp.filePath = std::string("WasNotGiven");
			}
		}

		else {																		// if the key does not exist, create one
			if (_property.GetPropertyDataType().GetType() == eFbxDouble3) {
				FbxDouble3 val = _property.Get<FbxDouble3>();
				tempProp.value[0] = (float)val[0];
				tempProp.value[1] = (float)val[1];
				tempProp.value[2] = (float)val[2];
				tempProp.value[3] = -1;
			}
			else if (_property.GetPropertyDataType().GetType() == eFbxDouble) {
				tempProp.value[0] = -1;			// -1 represents no value
				tempProp.value[1] = -1;
				tempProp.value[2] = -1;
				tempProp.value[3] = (float)_property.Get<FbxDouble>();
			}

			FbxFileTexture* lFileTexture = _property.GetSrcObject<FbxFileTexture>();
			if (lFileTexture != nullptr)
			{
				const char * cName = lFileTexture->GetRelativeFileName();
				std::string sName = std::string(cName);
				tempProp.filePath = sName;
			}
			else tempProp.filePath = std::string("WasNotGiven");
		}
		return tempProp;
	}

	FBXLIBRARY_API bool LoadMaterialFromFBXFile(const char * _fileName, std::vector<MaterialComponents::Material>& _material)
	{
		FbxManager* lSdkManager = FbxManager::Create();

		FbxIOSettings *ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
		lSdkManager->SetIOSettings(ios);

		FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");

		if (!lImporter->Initialize(_fileName, -1, lSdkManager->GetIOSettings()))
			return false;

		FbxScene* lScene = FbxScene::Create(lSdkManager, "myScene");
		lImporter->Import(lScene);
		lImporter->Destroy();

		FbxNode* lRootNode = lScene->GetRootNode();
		FbxNode* lNode = nullptr;
		unsigned materialCount = 0;

		if (lRootNode) {
			for (int i = 0; i < lRootNode->GetChildCount(); i++) {
				FbxNode* tNode = lRootNode->GetChild(i);
				FbxGeometry* geometry = (FbxGeometry*)tNode->GetNodeAttribute();
				if (geometry) {
					lNode = geometry->GetNode();
					if (lNode) {
						materialCount = lScene->GetMaterialCount();
						materialCount++;
					}
				}
			}
		}

		for (unsigned i = 0; i < materialCount; i++)
		{
			MaterialComponents::Material m_tempMaterial;

			FbxSurfaceMaterial* currentMaterial = lScene->GetMaterial(i);
			if (!currentMaterial) break;
			if (currentMaterial->Is<FbxSurfacePhong>()) m_tempMaterial.m_materialType = MaterialComponents::Material::PHONG;
			else if (currentMaterial->Is<FbxSurfaceLambert>()) m_tempMaterial.m_materialType = MaterialComponents::Material::LAMBERT;
			// FbxString comparison returns 0 if the strings are equal

			FbxProperty lProperty = currentMaterial->GetFirstProperty();
			while (lProperty.IsValid())
			{
				FbxString fbxName = lProperty.GetName();
				
				const char * cPtr = fbxName.Buffer();
				std::string strName = std::string(cPtr);

				if (MaterialComponents::Material::PHONG == m_tempMaterial.m_materialType) {
					if ("SpecularColor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::SPECULAR] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::SPECULAR); }
					else if ("SpecularFactor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::SPECULAR] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::SPECULAR); }
					else if ("Shininess" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::SHININESS] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::SHININESS); }
					else if ("ReflectionColor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::REFLECTION] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::REFLECTION); }
					else if ("ReflectionFactor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::REFLECTION] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::REFLECTION); }
					else if ("EmissiveColor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::EMISSIVE] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::EMISSIVE); }
					else if ("EmissiveFactor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::EMISSIVE] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::EMISSIVE); }
					else if ("AmbientColor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::AMBIENT] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::AMBIENT); }
					else if ("AmbientFactor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::AMBIENT] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::AMBIENT); }
					else if ("DiffuseColor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::DIFFUSE] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::DIFFUSE); }
					else if ("DiffuseFactor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::DIFFUSE] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::DIFFUSE); }
					else if ("Bump" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::BUMP] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::BUMP); }
					else if ("BumpFactor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::BUMP] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::BUMP); }
					else if ("NormalMap" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::NORMAL] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::NORMAL); }
					else if ("TransparentColor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::TRANSPARENCY] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::TRANSPARENCY); }
					else if ("TransparencyFactor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::TRANSPARENCY] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::TRANSPARENCY); }
					else if ("ReflectionColor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::REFLECTION] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::REFLECTION); }
					else if ("ReflectionFactor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::REFLECTION] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::REFLECTION); }
					else if ("DisplacementColor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::DISPLACEMENT] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::DISPLACEMENT); }
					else if ("DisplacementFactor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::DISPLACEMENT] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::DISPLACEMENT); }
					else if ("VectorDisplacementColor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::VECTOR_DISPLACEMENT] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::VECTOR_DISPLACEMENT); }
					else if ("VectorDisplacementFactor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::VECTOR_DISPLACEMENT] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::VECTOR_DISPLACEMENT); }
				}

				else if (MaterialComponents::Material::LAMBERT == m_tempMaterial.m_materialType) {
					if ("EmissiveColor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::EMISSIVE] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::EMISSIVE); }
					else if ("EmissiveFactor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::EMISSIVE] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::EMISSIVE); }
					else if ("AmbientColor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::AMBIENT] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::AMBIENT); }
					else if ("AmbientFactor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::AMBIENT] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::AMBIENT); }
					else if ("DiffuseColor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::DIFFUSE] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::DIFFUSE); }
					else if ("DiffuseFactor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::DIFFUSE] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::DIFFUSE); }
					else if ("SpecularColor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::SPECULAR] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::SPECULAR); }
					else if ("SpecularFactor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::SPECULAR] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::SPECULAR); }
					else if ("Shininess" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::SHININESS] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::SHININESS); }
					else if ("Bump" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::BUMP] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::BUMP); }
					else if ("BumpFactor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::BUMP] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::BUMP); }
					else if ("NormalMap" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::NORMAL] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::NORMAL); }
					else if ("TransparentColor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::TRANSPARENCY] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::TRANSPARENCY); }
					else if ("TransparencyFactor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::TRANSPARENCY] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::TRANSPARENCY); }
					else if ("ReflectionColor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::REFLECTION] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::REFLECTION); }
					else if ("ReflectionFactor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::REFLECTION] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::REFLECTION); }
					else if ("DisplacementColor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::DISPLACEMENT] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::DISPLACEMENT); }
					else if ("DisplacementFactor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::DISPLACEMENT] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::DISPLACEMENT); }
					else if ("VectorDisplacementColor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::VECTOR_DISPLACEMENT] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::VECTOR_DISPLACEMENT); }
					else if ("VectorDisplacementFactor" == strName) { m_tempMaterial.m_mapPropValues[MaterialComponents::Material::VECTOR_DISPLACEMENT] = PropertyHelper(m_tempMaterial, lProperty, MaterialComponents::Material::VECTOR_DISPLACEMENT); }
				}
				lProperty = currentMaterial->GetNextProperty(lProperty);
			}
			_material.push_back(m_tempMaterial);
		}
		// Destroy the SDK manager and all the other objects it was handling.
		lSdkManager->Destroy();
		return true;
	}

	FBXLIBRARY_API void ExportMaterialsToBinaryFile(const char* _filePath, std::vector<MaterialComponents::Material> _materials)
	{
		std::fstream fileOut;
		fileOut.open(_filePath, std::ios_base::binary | std::ios_base::out);

		unsigned numOfMaterials = (unsigned)_materials.size();
		fileOut.write((char*)&numOfMaterials, sizeof(numOfMaterials));

		for (int i = 0; i < _materials.size(); i++)
		{
			int matType = _materials[i].m_materialType;
			fileOut.write((char*)&matType, sizeof(matType));

			unsigned numOfPropsInMap = (unsigned)_materials[i].m_mapPropValues.size();
			fileOut.write((char*)&numOfPropsInMap, sizeof(numOfPropsInMap));

			for (_materials[i].m_mapPropValuesIter = _materials[i].m_mapPropValues.begin(); _materials[i].m_mapPropValuesIter != _materials[i].m_mapPropValues.end(); _materials[i].m_mapPropValuesIter++)
			{
				int eVal = _materials[i].m_mapPropValuesIter->first;
				fileOut.write((char*)&eVal, sizeof(eVal));

				unsigned filePathLength = (unsigned)strlen(_materials[i].m_mapPropValuesIter->second.filePath.c_str()) + 1;
				fileOut.write((char*)&filePathLength, sizeof(filePathLength));

				const char * cPtrFilePath = _materials[i].m_mapPropValuesIter->second.filePath.c_str();
				fileOut.write(cPtrFilePath, filePathLength);

				float f0 = _materials[i].m_mapPropValuesIter->second.value[0];
				float f1 = _materials[i].m_mapPropValuesIter->second.value[1];
				float f2 = _materials[i].m_mapPropValuesIter->second.value[2];
				float f3 = _materials[i].m_mapPropValuesIter->second.value[3];

				fileOut.write((char*)&f0, sizeof(f0));
				fileOut.write((char*)&f1, sizeof(f1));
				fileOut.write((char*)&f2, sizeof(f2));
				fileOut.write((char*)&f3, sizeof(f3));
			}
		}
		fileOut.close();
	}

	FBXLIBRARY_API bool ReadInMaterialsFromBinaryFile(const char* _filePath, std::vector<MaterialComponents::Material>& _materials)
	{
		std::fstream fileIn;
		fileIn.open(_filePath, std::ios_base::binary | std::ios_base::in);
		if (fileIn.is_open())
		{
			unsigned numOfMaterials;
			fileIn.read((char*)&numOfMaterials, 4);

			for (unsigned i = 0; i < numOfMaterials; i++)
			{
				MaterialComponents::Material currMaterial;
				fileIn.read((char*)&currMaterial.m_materialType, 4);

				unsigned numOfPropsInMap;
				fileIn.read((char*)&numOfPropsInMap, 4);

				for (unsigned j = 0; j < numOfPropsInMap; j++)
				{
					MaterialComponents::Material::properties ePropValue;
					fileIn.read((char*)&ePropValue, 4);

					unsigned filePathLength;
					fileIn.read((char*)&filePathLength, 4);
					char * cFilePath = new char[filePathLength];
					fileIn.read(cFilePath, filePathLength);
					std::string strFilePath = std::string(cFilePath);
					delete[] cFilePath;

					MaterialComponents::Material::properties_t tempProp_t;
					tempProp_t.filePath = strFilePath;

					fileIn.read((char*)&tempProp_t.value[0], 4);
					fileIn.read((char*)&tempProp_t.value[1], 4);
					fileIn.read((char*)&tempProp_t.value[2], 4);
					fileIn.read((char*)&tempProp_t.value[3], 4);

					currMaterial.m_mapPropValues[ePropValue] = tempProp_t;
				}
				_materials.push_back(currMaterial);
			}
			fileIn.close();
			return true;
		}
		return false;
	}

	FBXLIBRARY_API void DisplayMaterialPropertiesText(std::vector<MaterialComponents::Material>& _materials)
	{
		for (unsigned i = 0; i < _materials.size(); i++)
		{
			MaterialComponents::Material::materialType mType = _materials[i].m_materialType;
			switch (mType)
			{
			case MaterialComponents::Material::PHONG:
				printf("PHONG:\n");
				break;
			case MaterialComponents::Material::LAMBERT:
				printf("LAMBERT:\n");
				break;
			default:
				printf("NO MATERIAL TYPE:\n");
				break;
			}
			for (_materials[i].m_mapPropValuesIter = _materials[i].m_mapPropValues.begin(); _materials[i].m_mapPropValuesIter != _materials[i].m_mapPropValues.end(); _materials[i].m_mapPropValuesIter++)
			{
				MaterialComponents::Material::properties prop = _materials[i].m_mapPropValuesIter->first;
				switch (prop)
				{
				case MaterialComponents::Material::EMISSIVE:
					printf("EMISSIVE: ");
					break;
				case MaterialComponents::Material::AMBIENT:
					printf("AMBIENT: ");
					break;
				case MaterialComponents::Material::DIFFUSE:
					printf("DIFFUSE: ");
					break;
				case MaterialComponents::Material::NORMAL:
					printf("NORMAL: ");
					break;
				case MaterialComponents::Material::BUMP:
					printf("BUMP: ");
					break;
				case MaterialComponents::Material::TRANSPARENCY:
					printf("TRANSPARENCY: ");
					break;
				case MaterialComponents::Material::DISPLACEMENT:
					printf("DISPLACEMENT: ");
					break;
				case MaterialComponents::Material::VECTOR_DISPLACEMENT:
					printf("VECTOR_DISPLACEMENT: ");
					break;
				case MaterialComponents::Material::SPECULAR:
					printf("SPECULAR: ");
					break;
				case MaterialComponents::Material::SHININESS:
					printf("SHININESS: ");
					break;
				case MaterialComponents::Material::REFLECTION:
					printf("REFLECTION: ");
					break;
				case MaterialComponents::Material::COUNT:
					printf("COUNT...NOT SUPPOSED TO HAPPEN: ");
					break;
				default:
					printf("NO PROPERTY: ");
					break;
				}
				printf("%f, %f, %f, %f\n", _materials[i].m_mapPropValuesIter->second.value[0], _materials[i].m_mapPropValuesIter->second.value[1], _materials[i].m_mapPropValuesIter->second.value[2], _materials[i].m_mapPropValuesIter->second.value[3]);
				printf("File Path: ");
				printf(_materials[i].m_mapPropValuesIter->second.filePath.c_str());
				printf("\n\n");
			}
		}
	}

	FBXLIBRARY_API bool LoadAdvancedMeshFromFBXFile(const char * _fileName, std::vector<MeshComponentsAdvanced::OutInformationAdvanced>& _outVector)
	{
		// Initialize the SDK manager. This object handles all our memory management.
		FbxManager* lSdkManager = FbxManager::Create();

		// Create the IO settings object.
		FbxIOSettings *ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
		lSdkManager->SetIOSettings(ios);

		// Create an importer using the SDK manager.
		FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");

		// Use the first argument as the filename for the importer.
		if (!lImporter->Initialize(_fileName, -1, lSdkManager->GetIOSettings())) {
			return false;
		}

		// Create a new scene so that it can be populated by the imported file.
		FbxScene* lScene = FbxScene::Create(lSdkManager, "myScene");

		// Import the contents of the file into the scene.
		lImporter->Import(lScene);

		// The file is imported; so get rid of the importer.
		lImporter->Destroy();

		FbxNode* lRootNode = lScene->GetRootNode();
		if (lRootNode)
		{
			for (int i = 0; i < lRootNode->GetChildCount(); i++)
			{
				FbxNode* tNode = lRootNode->GetChild(i);
				FbxGeometry* geometry = (FbxGeometry*)tNode->GetNodeAttribute();
				FbxNodeAttribute::EType geoNodeType = geometry->GetAttributeType();
				if (FbxNodeAttribute::eMesh == geoNodeType)
				{
					FbxMesh* theMesh = (FbxMesh*)geometry;
					MeshComponentsAdvanced::OutInformationAdvanced meshInst;

					int mPolygonCount = theMesh->GetPolygonCount();
					int mPolygonVertexCount = theMesh->GetControlPointsCount();

					bool mAllByControlPoint = true;
					bool mHasNormal = theMesh->GetElementNormalCount() > 0;
					bool mHasUV = theMesh->GetElementUVCount() > 0;

					FbxGeometryElement::EMappingMode mNormalMappingMode = FbxGeometryElement::eNone;
					FbxGeometryElement::EMappingMode mUVMappingMode = FbxGeometryElement::eNone;

					FbxLayerElementArrayTemplate<int>* lMaterialIndice = NULL;
					FbxGeometryElement::EMappingMode lMaterialMappingMode = FbxGeometryElement::eNone;
					struct SubMesh
					{
						SubMesh() : IndexOffset(0), TriangleCount(0) {}

						int IndexOffset;
						int TriangleCount;
					};
					FbxArray<SubMesh*> mSubMeshes;
					if (theMesh->GetElementMaterial())
					{
						lMaterialIndice = &theMesh->GetElementMaterial()->GetIndexArray();
						lMaterialMappingMode = theMesh->GetElementMaterial()->GetMappingMode();
						if (lMaterialIndice && lMaterialMappingMode == FbxGeometryElement::eByPolygon)
						{
							//FBX_ASSERT(lMaterialIndice->GetCount() == lPolygonCount);
							if (lMaterialIndice->GetCount() == mPolygonCount)
							{
								// Count the faces of each material
								for (int lPolygonIndex = 0; lPolygonIndex < mPolygonCount; ++lPolygonIndex)
								{
									const int lMaterialIndex = lMaterialIndice->GetAt(lPolygonIndex);
									if (mSubMeshes.GetCount() < lMaterialIndex + 1)
									{
										mSubMeshes.Resize(lMaterialIndex + 1);
									}
									if (mSubMeshes[lMaterialIndex] == NULL)
									{
										mSubMeshes[lMaterialIndex] = new SubMesh;
									}
									mSubMeshes[lMaterialIndex]->TriangleCount += 1;
								}

								// Make sure we have no "holes" (NULL) in the mSubMeshes table. This can happen
								// if, in the loop above, we resized the mSubMeshes by more than one slot.
								for (int i = 0; i < mSubMeshes.GetCount(); i++)
								{
									if (mSubMeshes[i] == NULL)
										mSubMeshes[i] = new SubMesh;
								}

								// Record the offset (how many vertex)
								const int lMaterialCount = mSubMeshes.GetCount();
								int lOffset = 0;
								for (int lIndex = 0; lIndex < lMaterialCount; ++lIndex)
								{
									mSubMeshes[lIndex]->IndexOffset = lOffset;
									lOffset += mSubMeshes[lIndex]->TriangleCount * 3;
									// This will be used as counter in the following procedures, reset to zero
									mSubMeshes[lIndex]->TriangleCount = 0;
								}
								//FBX_ASSERT(lOffset == lPolygonCount * 3);
							}
						}
					}

					// All faces will use the same material.
					if (mSubMeshes.GetCount() == 0)
					{
						mSubMeshes.Resize(1);
						mSubMeshes[0] = new SubMesh();
					}

					const int TRIANGLE_VERTEX_COUNT = 3;

					//// Four floats for every position.
					//const int VERTEX_STRIDE = 4;
					//// Three floats for every normal.
					//const int NORMAL_STRIDE = 3;
					//// Two floats for every UV.
					//const int UV_STRIDE = 2;

					if (mHasNormal)
					{
						mNormalMappingMode = theMesh->GetElementNormal(0)->GetMappingMode();
						if (mNormalMappingMode == FbxGeometryElement::eNone)
							mHasNormal = false;
						if (mHasNormal && mNormalMappingMode != FbxGeometryElement::eByControlPoint)
							mAllByControlPoint = false;
					}
					if (mHasUV)
					{
						mUVMappingMode = theMesh->GetElementUV(0)->GetMappingMode();
						if (mUVMappingMode == FbxGeometryElement::eNone)
							mHasUV = false;
						if (mHasUV && mUVMappingMode != FbxGeometryElement::eByControlPoint)
							mAllByControlPoint = false;
					}
					if (!mAllByControlPoint)
					{
						mPolygonVertexCount = mPolygonCount * TRIANGLE_VERTEX_COUNT;
					}

					FbxStringList mUVNames;
					theMesh->GetUVSetNames(mUVNames);
					const char * mUVName = NULL;
					if (mHasUV && mUVNames.GetCount())
					{
						mUVName = mUVNames[0];
					}

					int indexCount = theMesh->GetPolygonVertexCount();
					meshInst.indices.resize(mPolygonCount * TRIANGLE_VERTEX_COUNT);

					const FbxVector4 * mControlPoints = theMesh->GetControlPoints();
					FbxVector4 mCurrentVertex;
					FbxVector4 mCurrentNormal;
					FbxVector2 mCurrentUV;
					int mVertexCount = 0;
					for (int mPolygonIndex = 0; mPolygonIndex < mPolygonCount; ++mPolygonIndex)
					{
						int lMaterialIndex = 0;
						if (lMaterialIndice && lMaterialMappingMode == FbxGeometryElement::eByPolygon)
						{
							lMaterialIndex = lMaterialIndice->GetAt(mPolygonIndex);
						}

						// Where should I save the vertex attribute index, according to the material
						const int lIndexOffset = mSubMeshes[lMaterialIndex]->IndexOffset +
							mSubMeshes[lMaterialIndex]->TriangleCount * 3;
						for (int mVerticeIndex = 0; mVerticeIndex < TRIANGLE_VERTEX_COUNT; mVerticeIndex++)
						{
							const int mControlPointIndex = theMesh->GetPolygonVertex(mPolygonIndex, mVerticeIndex);

							if (mAllByControlPoint)
							{
								meshInst.indices[lIndexOffset + mVerticeIndex] = static_cast<unsigned int>(mControlPointIndex);
							}
							// Populate the array with vertex attribute, if by polygon vertex.
							else
							{
								MeshComponentsAdvanced::VertexAdvanced currVert;
								meshInst.indices[lIndexOffset + mVerticeIndex] = static_cast<unsigned int>(mVertexCount);

								mCurrentVertex = mControlPoints[mControlPointIndex];

								currVert.position[0] = static_cast<float>(mCurrentVertex[0]);
								currVert.position[1] = static_cast<float>(mCurrentVertex[1]);
								currVert.position[2] = static_cast<float>(mCurrentVertex[2]);
								currVert.position[3] = 1;

								if (mHasNormal)
								{
									theMesh->GetPolygonVertexNormal(mPolygonIndex, mVerticeIndex, mCurrentNormal);

									currVert.normals[0] = static_cast<float>(mCurrentNormal[0]);
									currVert.normals[1] = static_cast<float>(mCurrentNormal[1]);
									currVert.normals[2] = static_cast<float>(mCurrentNormal[2]);
									currVert.normals[3] = 1.f;
								}

								if (mHasUV)
								{
									bool lUnmappedUV;
									theMesh->GetPolygonVertexUV(mPolygonIndex, mVerticeIndex, mUVName, mCurrentUV, lUnmappedUV);
									currVert.uvs[0] = static_cast<float>(mCurrentUV[0]);
									currVert.uvs[1] = static_cast<float>(mCurrentUV[1]);
								}
								meshInst.vertices.push_back(currVert);
							}
							++mVertexCount;
						}
						mSubMeshes[lMaterialIndex]->TriangleCount += 1;
					}
					_outVector.push_back(meshInst);
					for (int i = 0; i < mSubMeshes.Size(); i++)
					{
						delete mSubMeshes[i];
					}
					mSubMeshes.Clear();
				}
			}
		}
		// Destroy the SDK manager and all the other objects it was handling.
		lSdkManager->Destroy();
		return true;
	}

	FBXLIBRARY_API void ExportAdvancedMeshToBinaryFile(const char * _filePath, MeshComponentsAdvanced::OutInformationAdvanced & _mesh)
	{
		std::fstream file;
		file.open(_filePath, std::ios_base::binary | std::ios_base::out);

		unsigned numOfIndices = (unsigned)_mesh.indices.size();
		file.write((char*)&numOfIndices, sizeof(numOfIndices));

		for (unsigned i = 0; i < _mesh.indices.size(); i++)
			file.write((char*)(&_mesh.indices[i]), sizeof(_mesh.indices[i]));

		unsigned numOfVertices = (unsigned)_mesh.vertices.size();
		file.write((char*)&numOfVertices, sizeof(numOfVertices));

		for (unsigned i = 0; i < _mesh.vertices.size(); i++)
		{
			file.write((char*)(&_mesh.vertices[i].position[0]), sizeof(_mesh.vertices[i].position[0]));
			file.write((char*)(&_mesh.vertices[i].position[1]), sizeof(_mesh.vertices[i].position[1]));
			file.write((char*)(&_mesh.vertices[i].position[2]), sizeof(_mesh.vertices[i].position[2]));
			file.write((char*)(&_mesh.vertices[i].position[3]), sizeof(_mesh.vertices[i].position[3]));

			file.write((char*)(&_mesh.vertices[i].normals[0]), sizeof(_mesh.vertices[i].normals[0]));
			file.write((char*)(&_mesh.vertices[i].normals[1]), sizeof(_mesh.vertices[i].normals[1]));
			file.write((char*)(&_mesh.vertices[i].normals[2]), sizeof(_mesh.vertices[i].normals[2]));
			file.write((char*)(&_mesh.vertices[i].normals[3]), sizeof(_mesh.vertices[i].normals[3]));

			file.write((char*)(&_mesh.vertices[i].uvs[0]), sizeof(_mesh.vertices[i].uvs[0]));
			file.write((char*)(&_mesh.vertices[i].uvs[1]), sizeof(_mesh.vertices[i].uvs[1]));
		}

		file.close();
	}

	FBXLIBRARY_API bool ReadInAdvancedBinaryMeshFile(const char * _fileName, MeshComponentsAdvanced::OutInformationAdvanced & _objectToFill)
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

			//for (unsigned i = 0; i < numOfVertices; i++)
			//	_objectToFill.vertices[i].position[3] = 1.f;

			file.close();
			return true;
		}
		return false;
	}

	FBXLIBRARY_API bool LoadAnimationFromFBXFile(const char * _fileName, AnimationComponents::AnimationClip& _animationClip, std::vector<AnimationComponents::SkeletonJoints>& _skelJoints)
	{
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
		//std::vector<AnimationComponents::SkeletonJoints*> skelJoints;
		//AnimationComponents::AnimationClip animClip = AnimationComponents::AnimationClip();

		// Initialize the SDK manager. This object handles all our memory management.
		FbxManager* lSdkManager = FbxManager::Create();

		// Create the IO settings object.
		FbxIOSettings *ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
		lSdkManager->SetIOSettings(ios);

		// Create an importer using the SDK manager.
		FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");

		// Use the first argument as the filename for the importer.
		if (!lImporter->Initialize(_fileName, -1, lSdkManager->GetIOSettings())) {
			return false;
		}

		// Create a new scene so that it can be populated by the imported file.
		FbxScene* lScene = FbxScene::Create(lSdkManager, "myScene");

		// Import the contents of the file into the scene.
		lImporter->Import(lScene);

		// The file is imported; so get rid of the importer.
		lImporter->Destroy();

		int poseCount = lScene->GetPoseCount();

		//for (int i = 0; i < poseCount; i++)
		//{
		// Get the root of the skeleton
		FbxPose* currentPose = lScene->GetPose(0);
		if (currentPose->IsBindPose())
		{
			int nodeCount = currentPose->GetCount();
			for (int j = 0; j < nodeCount; j++)
			{
				FbxNode* currentNode = currentPose->GetNode(j);
				FbxSkeleton* currentSkeleton = currentNode->GetSkeleton();
				if (currentSkeleton)
				{
					bool isSkeletonRoot = currentSkeleton->IsSkeletonRoot();
					if (isSkeletonRoot)
					{
						MyFBXJoint* rootSkelNode = new MyFBXJoint(currentNode, -1);
						fbxJoints.push_back(rootSkelNode);

						AnimationComponents::SkeletonJoints* rootSkelTransform = new AnimationComponents::SkeletonJoints();
						FbxMatrix currentMatrix = currentNode->EvaluateGlobalTransform();
						int count = 0;
						for (int y = 0; y < 4; y++)
						{
							for (int x = 0; x < 4; x++)
							{
								rootSkelTransform->globalTransformArray[count++] = (float)currentMatrix.GetRow(y)[x];
								rootSkelTransform->globalTransform4x4[y][x] = (float)currentMatrix.GetRow(y)[x];
							}
						}
						rootSkelTransform->parentIndex = -1;
						rootSkelTransform->jointName = std::string(currentNode->GetName());
						_skelJoints.push_back(*rootSkelTransform);
						delete rootSkelTransform;
					}
				}
			}
		}
		
		for (size_t k = 0; k < fbxJoints.size(); k++)
		{
			for (int l = 0; l < fbxJoints[k]->node->GetChildCount(); l++)
			{
				FbxNode* currentChild = fbxJoints[k]->node->GetChild(l);
				FbxSkeleton* currentChildSkeleton = currentChild->GetSkeleton();
				if (currentChildSkeleton)
				{
					MyFBXJoint* currentChildJoint = new MyFBXJoint(currentChild, (int)k);
					fbxJoints.push_back(currentChildJoint);

					AnimationComponents::SkeletonJoints* rootSkelTransform = new AnimationComponents::SkeletonJoints();
					FbxMatrix currentMatrix = fbxJoints[k]->node->EvaluateGlobalTransform();
					int count = 0;
					for (int y = 0; y < 4; y++)
					{
						for (int x = 0; x < 4; x++)
						{
							rootSkelTransform->globalTransformArray[count++] = (float)currentMatrix.GetRow(y)[x];
							rootSkelTransform->globalTransform4x4[y][x] = (float)currentMatrix.GetRow(y)[x];
						}
					}
					rootSkelTransform->parentIndex = (int)k;
					rootSkelTransform->jointName = std::string(currentChild->GetName());
					_skelJoints.push_back(*rootSkelTransform);
					delete rootSkelTransform;
				}
			}
		}

		FbxAnimStack* currentAnimStack = lScene->GetCurrentAnimationStack();

		FbxTimeSpan localTimeSpan = currentAnimStack->GetLocalTimeSpan();
		FbxTime animDuration = localTimeSpan.GetDuration();

		//FbxTime::EMode::eFrames24 gives 24 frames per second
		FbxLongLong frameCount = animDuration.GetFrameCount(FbxTime::EMode::eFrames24);
		_animationClip.duration = animDuration.GetSecondDouble();

		for (FbxLongLong i = 0; i < frameCount; i++)
		{
			// skip bind pose at frame number 0
			AnimationComponents::Keyframe currentKeyframe = AnimationComponents::Keyframe();

			currentKeyframe.joints.resize(_skelJoints.size());

			animDuration.SetFrame(i, FbxTime::EMode::eFrames24);
			currentKeyframe.time = animDuration.GetSecondDouble();
			int index = 0;
			for each (MyFBXJoint* theJoint in fbxJoints)
			{
				FbxMatrix currentMatrix = theJoint->node->EvaluateGlobalTransform(animDuration);
				int count = 0;
				for (int y = 0; y < 4; y++)
				{
					for (int x = 0; x < 4; x++)
					{
						currentKeyframe.joints[index].globalTransformArray[count] = (float)currentMatrix.GetRow(y)[x];
						currentKeyframe.joints[index].globalTransform4x4[y][x] = (float)currentMatrix.GetRow(y)[x];
						currentKeyframe.joints[index].jointName = _skelJoints[index].jointName;
						currentKeyframe.joints[index].parentIndex = _skelJoints[index].parentIndex;
						++count;
					}
				}
				++index;
			}
			_animationClip.frames.push_back(currentKeyframe);
		}

		for (size_t i = 0; i < fbxJoints.size(); i++)
		{
			delete fbxJoints[i];
		}
		fbxJoints.clear();

		// Destroy the SDK manager and all the other objects it was handling.
		lSdkManager->Destroy();
		return true;
	}
}