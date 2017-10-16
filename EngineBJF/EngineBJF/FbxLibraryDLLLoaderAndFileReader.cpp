#include "FbxLibraryDLLLoaderAndFileReader.h"

bool FbxLibraryHandle::RunFbxLoader(const char* _fbxFile, const char* _writeOutFile)
{
	HINSTANCE hinstLib; //Handle to the DLL
	MYFUNCPOINT01 ProcAddress01; //Pointer to the function
	MYFUNCPOINT02 ProcAddress02; //Pointer to the function

	hinstLib = LoadLibrary(L"FbxLibraryDLL.dll");

	if (!hinstLib) return false;

	ProcAddress01 = (MYFUNCPOINT01)GetProcAddress(hinstLib, "LoadMeshFromFBXFile");
	ProcAddress02 = (MYFUNCPOINT02)GetProcAddress(hinstLib, "ExportMeshToBinaryFile");

	if (!ProcAddress01 || !ProcAddress01) return false;

	std::vector<BFMesh> meshes;

	bool rtrnVal = (ProcAddress01)(_fbxFile, meshes);

	if (rtrnVal) {
		printf("Mesh was loaded successfully.\n");
		(ProcAddress02)(_writeOutFile, meshes[0]);
	}
	return true;
}

bool FbxLibraryHandle::ReadInBinaryMeshFile(const char * _fileName, OutInformation& _objectToFill)
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
			_objectToFill.oi_indices.push_back(num);
		}
		
		file.read((char*)&numOfVertices, 4);

		VertexPositionColor vert;

		for (unsigned i = 0; i < numOfVertices; i++)
		{
			file.read((char*)(&vert.position[0]), sizeof(4));
			file.read((char*)(&vert.position[1]), sizeof(4));
			file.read((char*)(&vert.position[2]), sizeof(4));
			file.read((char*)(&vert.position[3]), sizeof(4));
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
