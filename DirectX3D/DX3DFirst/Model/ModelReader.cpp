#include "framework.h"
#include "ModelReader.h"

ModelReader::ModelReader(string name)
	:_name(name)
{
	ReadMaterial();
	ReadMesh();
}

ModelReader::~ModelReader()
{
	for (Material* m : _materials)
		delete m;

	for (ModelMesh* m : _meshes)
		delete m;
	_materials.clear();
	_meshes.clear();
}

void ModelReader::SetShader(wstring file)
{
	for (Material* m : _materials)
		m->SetShader(file);
}

void ModelReader::ReadMaterial()
{
	string path = "_ModelData/Material/" + _name + "/MaterialList.list";

	BinaryReader data(ToWString(path));

	UINT  size = data.ReadUINT();

	for (UINT i = 0; i < size; i++)
	{
		Material* m = new Material();

		string file = "_ModelData/Material/" + _name + "/" + data.ReadString() + ".mat";

		m->Load(ToWString(file));
		
		_materials.push_back(m);
	}
}

void ModelReader::ReadMesh()
{
	string path = "_ModelData/Mesh/" + _name + ".mesh";

	BinaryReader data(ToWString(path));

	UINT  size = data.ReadUINT();

	for (UINT i = 0; i < size; i++)
	{
		ModelMesh* mesh = new ModelMesh();

		mesh->_name = data.ReadString();
		mesh->_materialIndex = data.ReadUINT();
		
		{
			UINT count = data.ReadUINT();

			mesh->_vertices.resize(count);

			void* ptr = mesh->_vertices.data();

			data.ReadData(&ptr, sizeof(ModelVertex) * count);
		}

		{
			UINT count = data.ReadUINT();

			mesh->_indices.resize(count);

			void* ptr = mesh->_indices.data();

			data.ReadData(&ptr, sizeof(UINT) * count);
		}

		_meshes.push_back(mesh);

	}
}