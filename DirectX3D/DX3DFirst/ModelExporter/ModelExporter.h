#pragma once
class ModelExporter
{
public:
	ModelExporter(string name);
	~ModelExporter();

	void ExportModel();

private:
	void ExportMaterial();
	void ExportMesh();

	void ReadMesh(aiNode* node);
	void WriteMesh();

	wstring CreateTexture(string file);

	string _name;

	Assimp::Importer* _importer;
	
	const aiScene* _scene;

	vector<MeshData*> _meshes;

	vector<string> _materialNames;
};

