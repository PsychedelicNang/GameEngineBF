#include "FBXHandler.h"

#pragma region BasicMeshFunctions

bool FBXHandler::LoadBasicMeshFromFBXFile(const char * _fileName, std::vector<MeshComponentsBasic::Mesh>& _outVector)
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
				//then we have a mesh
				//// Misleading name, returns index array as int*
				//int* verts = theMesh->GetPolygonVertices();

				//// Total number of unique vertex positions
				//int numOfUniqueVertPos = geometry->GetControlPointsCount();

				//// Returns unique vertex positions array as FbxVector4*
				//FbxVector4* uniqueVertsPos = geometry->GetControlPoints();

				//FbxMesh* theMesh = FbxMesh::Create(geometry, "mesh");	// doesn't work??
				FbxMesh* theMesh = (FbxMesh*)geometry;
				MeshComponentsBasic::Mesh meshInst;
				int indexCount = theMesh->GetPolygonVertexCount();
				meshInst.indexBuffer.resize(indexCount);

				int* verts = theMesh->GetPolygonVertices();
				for (int i = 0; i < indexCount; i++)
					meshInst.indexBuffer[i] = verts[i];

				for (int j = 0; j < geometry->GetControlPointsCount(); j++)
				{
					MeshComponentsBasic::Vector4 currPos;
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

void FBXHandler::ExportBasicMeshToBinaryFile(const char * _filePath, MeshComponentsBasic::Mesh _mesh)
{
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

bool FBXHandler::ReadInBasicBinaryMeshFile(const char * _fileName, MeshComponentsBasic::OutInformation & _objectToFill, float _scaleAmount)
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

#pragma endregion

#pragma region MaterialFunctions

/*
* Fills out values for the materials property, both of which are passed into the function.
* The _eValue determines the key for the std::map with is being used inside of the Materials structure.
* This function should NEVER be called explicitly from a user.
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

bool FBXHandler::LoadMaterialFromFBXFile(const char * _fileName, std::vector<MaterialComponents::Material>& _material)
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

			// if this is a phong material, map figure out the values for each of the possible components and store their value inside of a map.
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

			// if this is a lambert material, map figure out the values for each of the possible components and store their value inside of a map.
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

void FBXHandler::ExportMaterialsToBinaryFile(const char * _filePath, std::vector<MaterialComponents::Material> _materials)
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

bool FBXHandler::ReadInMaterialsFromBinaryFile(const char * _filePath, std::vector<MaterialComponents::Material>& _materials)
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

	// returns false if the file did not exist
	return false;
}

// Prints the materials properties to the console application.
void FBXHandler::PrintMaterialProperties(std::vector<MaterialComponents::Material>& _materials)
{
	printf("New Object's Material...\n");
	for (unsigned i = 0; i < _materials.size(); i++)
	{
		printf("Material %u:\n", i + 1);
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
		printf("\n");
	}
}

#pragma endregion

#pragma region AdvancedMeshFunctions

bool FBXHandler::LoadAdvancedMeshFromFBXFile(const char * _fileName, std::vector<MeshComponentsAdvanced::OutInformation>& _outVector)
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
				MeshComponentsAdvanced::OutInformation meshInst;

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

void FBXHandler::ExportAdvancedMeshToBinaryFile(const char * _filePath, MeshComponentsAdvanced::OutInformation & _mesh)
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

bool FBXHandler::ReadInAdvancedBinaryMeshFile(const char * _fileName, MeshComponentsAdvanced::OutInformation & _objectToFill, float _scaleAmount)
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

#pragma endregion

#pragma region AnimationFunctions

bool FBXHandler::LoadAdvancedMeshWithSkinnedAndSkeletalAnimationFromFBXFile(const char * _fileName, std::vector<MeshComponentsAnimation::OutInformation>& _outVector, AnimationComponents::BindPose & _bindPose, AnimationComponents::AnimationClip & _animationClip, std::vector<AnimationComponents::SkeletonJoints>& _skelJoints, float _scaleAmount)
{
	int m_meshControlPointCount;

	struct Influence {
		int joint = 0;
		float weight = 0;
	};
	using influence_set = std::array<Influence, 4>;
	std::vector<influence_set> control_point_influences;

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

	FbxNode* lRootNode = lScene->GetRootNode();
	if (lRootNode)
	{
		FbxNode* tNode = lRootNode->GetChild(0);
		FbxGeometry* geometry = (FbxGeometry*)tNode->GetNodeAttribute();
		FbxNodeAttribute::EType geoNodeType = geometry->GetAttributeType();
		if (FbxNodeAttribute::eMesh == geoNodeType)
		{
			FbxMesh* theMesh = (FbxMesh*)geometry;

			m_meshControlPointCount = theMesh->GetControlPointsCount();
			control_point_influences.resize(m_meshControlPointCount);
		}
	}

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
							rootSkelTransform->globalTransformArray[count] = (float)currentMatrix.GetRow(y)[x];
							count++;
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
						rootSkelTransform->globalTransformArray[count] = (float)currentMatrix.GetRow(y)[x];
						count++;
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

	//bind pose is at 0
	for (FbxLongLong i = 0; i < frameCount; i++)
	{
		AnimationComponents::Keyframe currentKeyframe = AnimationComponents::Keyframe();

		currentKeyframe.joints.resize(_skelJoints.size());
		_bindPose.joints.resize(_skelJoints.size());

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
					if (i == 0)
					{
						_bindPose.joints[index].globalTransformArray[count] = (float)currentMatrix.GetRow(y)[x];
						_bindPose.joints[index].jointName = _skelJoints[index].jointName;
						_bindPose.joints[index].parentIndex = _skelJoints[index].parentIndex;
						++count;
					}
					else
					{
						currentKeyframe.joints[index].globalTransformArray[count] = (float)currentMatrix.GetRow(y)[x];
						currentKeyframe.joints[index].jointName = _skelJoints[index].jointName;
						currentKeyframe.joints[index].parentIndex = _skelJoints[index].parentIndex;
						++count;
					}

					/*	currentKeyframe.joints[index].globalTransformArray[count] = (float)currentMatrix.GetRow(y)[x];
					currentKeyframe.joints[index].jointName = _skelJoints[index].jointName;
					currentKeyframe.joints[index].parentIndex = _skelJoints[index].parentIndex;
					++count;*/
				}
			}
			/*if (i == 0) continue;
			else ++index;*/
			++index;
		}
		if (i != 0) _animationClip.frames.push_back(currentKeyframe);
		//_animationClip.frames.push_back(currentKeyframe);
	}

	if (_scaleAmount != 1.f)
	{
		// Scale the bind pose down
		for (size_t i = 0; i < _bindPose.joints.size(); i++)
		{
			_bindPose.joints[i].globalTransformArray[12] *= _scaleAmount;
			_bindPose.joints[i].globalTransformArray[13] *= _scaleAmount;
			_bindPose.joints[i].globalTransformArray[14] *= _scaleAmount;
		}

		// Scale the model down
		for (size_t i = 0; i < _skelJoints.size(); i++)
		{
			_skelJoints[i].globalTransformArray[12] *= _scaleAmount;
			_skelJoints[i].globalTransformArray[13] *= _scaleAmount;
			_skelJoints[i].globalTransformArray[14] *= _scaleAmount;
		}

		// Scale the animation down as well
		for (size_t i = 0; i < _animationClip.frames.size(); i++)
		{
			for (size_t j = 0; j < _animationClip.frames[i].joints.size(); j++)
			{
				_animationClip.frames[i].joints[j].globalTransformArray[12] *= _scaleAmount;
				_animationClip.frames[i].joints[j].globalTransformArray[13] *= _scaleAmount;
				_animationClip.frames[i].joints[j].globalTransformArray[14] *= _scaleAmount;
			}
		}
	}

	m_skelJoints = _skelJoints;

	FbxPose* currentBindPose = lScene->GetPose(0);
	if (currentBindPose->IsBindPose())
	{
		int nodeCount = currentBindPose->GetCount();
		for (int i = 0; i < nodeCount; i++)
		{
			FbxNode* currentNode = currentBindPose->GetNode(i);
			FbxMesh* currentMesh = currentNode->GetMesh();
			if (currentMesh)
			{
				int deformerCount = currentMesh->GetDeformerCount();
				for (int j = 0; j < deformerCount; j++)
				{
					FbxDeformer* deformer = currentMesh->GetDeformer(j);
					if (deformer->Is<FbxSkin>())
					{
						FbxSkin* skin;
						skin = (FbxSkin*)deformer;
						int skinClusterCount = skin->GetClusterCount();
						for (int k = 0; k < skinClusterCount; k++)
						{
							FbxCluster* cluster = skin->GetCluster(k);
							FbxNode* clusterNode = cluster->GetLink();
							for (size_t l = 0; l < fbxJoints.size(); l++)
							{
								if (clusterNode == fbxJoints[l]->node)
								{
									int controlPointCount = cluster->GetControlPointIndicesCount();
									double* weights = cluster->GetControlPointWeights();
									int* indices = cluster->GetControlPointIndices();
									for (int m = 0; m < controlPointCount; m++)
									{
										Influence influenceInst;
										influenceInst.weight = (float)weights[m];
										influenceInst.joint = (int)l;

										influence_set influenceSetInst = control_point_influences[indices[m]];
										int lowestIndex = 0;
										float lowestValue = 0.f;
										for (size_t o = 0; o < influenceSetInst.size(); o++)
										{
											//check for the lowest value and then break
											for (size_t p = 0; p < influenceSetInst.size(); p++)
											{
												lowestIndex = 0;
												lowestValue = influenceSetInst[o].weight;
												if (influenceSetInst[p].weight < lowestValue)
												{
													lowestIndex = (int)p;
													lowestValue = influenceSetInst[p].weight;
												}
											}

											influenceSetInst[lowestIndex] = influenceInst;
											control_point_influences[indices[m]] = influenceSetInst;
											break;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}


	FbxNode* root = lScene->GetRootNode();
	if (root)
	{
		for (int i = 0; i < root->GetChildCount(); i++)
		{
			FbxNode* tNode = root->GetChild(i);
			FbxGeometry* geometry = (FbxGeometry*)tNode->GetNodeAttribute();
			FbxNodeAttribute::EType geoNodeType = geometry->GetAttributeType();
			if (FbxNodeAttribute::eMesh == geoNodeType)
			{
				FbxMesh* theMesh = (FbxMesh*)geometry;
				MeshComponentsAnimation::OutInformation meshInst;

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
							MeshComponentsAnimation::VertexAdvanced currVert;
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

							currVert.weights[0] = control_point_influences[mControlPointIndex][0].weight;
							currVert.weights[1] = control_point_influences[mControlPointIndex][1].weight;
							currVert.weights[2] = control_point_influences[mControlPointIndex][2].weight;
							currVert.weights[3] = control_point_influences[mControlPointIndex][3].weight;

							currVert.joints[0] = control_point_influences[mControlPointIndex][0].joint;
							currVert.joints[1] = control_point_influences[mControlPointIndex][1].joint;
							currVert.joints[2] = control_point_influences[mControlPointIndex][2].joint;
							currVert.joints[3] = control_point_influences[mControlPointIndex][3].joint;

							float sum = currVert.weights[0] + currVert.weights[1] + currVert.weights[2] + currVert.weights[3];
							currVert.weights[0] /= sum;
							currVert.weights[1] /= sum;
							currVert.weights[2] /= sum;
							currVert.weights[3] /= sum;

							currVert.padding[0] = 0;
							currVert.padding[1] = 0;

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


	for (size_t i = 0; i < fbxJoints.size(); i++)
	{
		delete fbxJoints[i];
	}
	fbxJoints.clear();
	// Destroy the SDK manager and all the other objects it was handling.
	lSdkManager->Destroy();
	return true;
}

void FBXHandler::ExportAdvancedMeshWithSkinnedAnimationToBinaryFile(const char * _filePath, MeshComponentsAnimation::OutInformation & _mesh)
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

		file.write((char*)&_mesh.vertices[i].weights[0], sizeof(_mesh.vertices[i].weights[0]));
		file.write((char*)&_mesh.vertices[i].weights[1], sizeof(_mesh.vertices[i].weights[1]));
		file.write((char*)&_mesh.vertices[i].weights[2], sizeof(_mesh.vertices[i].weights[2]));
		file.write((char*)&_mesh.vertices[i].weights[3], sizeof(_mesh.vertices[i].weights[3]));

		file.write((char*)&_mesh.vertices[i].joints[0], sizeof(_mesh.vertices[i].joints[0]));
		file.write((char*)&_mesh.vertices[i].joints[1], sizeof(_mesh.vertices[i].joints[1]));
		file.write((char*)&_mesh.vertices[i].joints[2], sizeof(_mesh.vertices[i].joints[2]));
		file.write((char*)&_mesh.vertices[i].joints[3], sizeof(_mesh.vertices[i].joints[3]));
	}

	file.close();
}

void FBXHandler::ExportAdvancedMeshWithSkinnedAnimationToBinaryFile(const char * _fileName, MeshComponentsAnimation::OutInformation & _mesh, AnimationComponents::BindPose & _bindPose, AnimationComponents::AnimationClip & _animationClip, std::vector<AnimationComponents::SkeletonJoints>& _skelJoints)
{
	std::fstream file;
	file.open(_fileName, std::ios_base::binary | std::ios_base::out);

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

		file.write((char*)&_mesh.vertices[i].weights[0], sizeof(_mesh.vertices[i].weights[0]));
		file.write((char*)&_mesh.vertices[i].weights[1], sizeof(_mesh.vertices[i].weights[1]));
		file.write((char*)&_mesh.vertices[i].weights[2], sizeof(_mesh.vertices[i].weights[2]));
		file.write((char*)&_mesh.vertices[i].weights[3], sizeof(_mesh.vertices[i].weights[3]));

		file.write((char*)&_mesh.vertices[i].joints[0], sizeof(_mesh.vertices[i].joints[0]));
		file.write((char*)&_mesh.vertices[i].joints[1], sizeof(_mesh.vertices[i].joints[1]));
		file.write((char*)&_mesh.vertices[i].joints[2], sizeof(_mesh.vertices[i].joints[2]));
		file.write((char*)&_mesh.vertices[i].joints[3], sizeof(_mesh.vertices[i].joints[3]));
	}

	unsigned bindPoseJointCount = (unsigned)_bindPose.joints.size();
	file.write((char*)&bindPoseJointCount, sizeof(bindPoseJointCount));

	for (unsigned i = 0; i < bindPoseJointCount; i++)
	{
		file.write((char*)(&_bindPose.joints[i].parentIndex), sizeof(_bindPose.joints[i].parentIndex));

		for (unsigned j = 0; j < 16; j++)
		{
			file.write((char*)(&_bindPose.joints[i].globalTransformArray[j]), sizeof(_bindPose.joints[i].globalTransformArray[j]));
		}

		unsigned filePathLength = (unsigned)strlen(_bindPose.joints[i].jointName.c_str()) + 1;
		file.write((char*)&filePathLength, sizeof(filePathLength));

		const char * cPtrFilePath = _bindPose.joints[i].jointName.c_str();
		file.write(cPtrFilePath, filePathLength);
	}

	file.write((char*)(&_animationClip.duration), sizeof(_animationClip.duration));

	unsigned keyframeCount = (unsigned)_animationClip.frames.size();
	file.write((char*)(&keyframeCount), sizeof(keyframeCount));

	for (unsigned i = 0; i < keyframeCount; i++)
	{
		file.write((char*)(&_animationClip.frames[i].time), sizeof(_animationClip.frames[i].time));

		unsigned animFramesJointsCount = (unsigned)_animationClip.frames[i].joints.size();
		file.write((char*)(&animFramesJointsCount), sizeof(animFramesJointsCount));

		for (unsigned j = 0; j < animFramesJointsCount; j++)
		{
			file.write((char*)(&_animationClip.frames[i].joints[j].parentIndex), sizeof(_animationClip.frames[i].joints[j].parentIndex));
			for (unsigned k = 0; k < 16; k++)
			{
				file.write((char*)&_animationClip.frames[i].joints[j].globalTransformArray[k], sizeof(_animationClip.frames[i].joints[j].globalTransformArray[k]));
			}
			unsigned filePathLength = (unsigned)strlen(_animationClip.frames[i].joints[j].jointName.c_str()) + 1;
			file.write((char*)&filePathLength, sizeof(filePathLength));

			const char * cPtrFilePath = _animationClip.frames[i].joints[j].jointName.c_str();
			file.write(cPtrFilePath, filePathLength);
		}
	}

	unsigned skelJointsCount = (unsigned)_skelJoints.size();
	file.write((char*)&skelJointsCount, sizeof(skelJointsCount));

	for (unsigned i = 0; i < skelJointsCount; i++)
	{
		file.write((char*)(&_skelJoints[i].parentIndex), sizeof(_skelJoints[i].parentIndex));

		for (unsigned j = 0; j < 16; j++)
		{
			file.write((char*)(&_skelJoints[i].globalTransformArray[j]), sizeof(_skelJoints[i].globalTransformArray[j]));
		}

		unsigned filePathLength = (unsigned)strlen(_skelJoints[i].jointName.c_str()) + 1;
		file.write((char*)&filePathLength, sizeof(filePathLength));

		const char * cPtrFilePath = _skelJoints[i].jointName.c_str();
		file.write(cPtrFilePath, filePathLength);
	}

	file.close();
}

bool FBXHandler::ReadInAdvancedMeshWithSkinnedAnimationFromBinaryFile(const char * _fileName, MeshComponentsAnimation::OutInformation & _objectToFill)
{
	std::fstream file;
	file.open(_fileName, std::ios_base::binary | std::ios_base::in);

	if (file.is_open())
	{
		unsigned numOfIndices;
		unsigned numOfVertices;

		file.read((char*)&numOfIndices, sizeof(unsigned));

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

		file.close();
		return true;
	}
	
	// returns false if the file did not exist
	return false;
}

bool FBXHandler::ReadInAdvancedMeshWithSkinnedAnimationFromBinaryFile(const char * _fileName, MeshComponentsAnimation::OutInformation & _objectToFill, AnimationComponents::BindPose & _bindPose, AnimationComponents::AnimationClip & _animationClip, std::vector<AnimationComponents::SkeletonJoints>& _skelJoints)
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

#pragma endregion