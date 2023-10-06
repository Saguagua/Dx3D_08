#include "framework.h"
#include "ModelExporter.h"

ModelExporter::ModelExporter(string name)
	:_name(name)
{
	_importer = new Assimp::Importer();

	_scene = _importer->ReadFile("_ModelData/FBX/" + name + ".fbx",
		aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_MaxQuality);

	assert(_scene != nullptr);
}

ModelExporter::~ModelExporter()
{
	delete _importer;
}

void ModelExporter::ExportModel()
{
	ExportMaterial();
	ExportMesh();
}

void ModelExporter::ExportMaterial()
{
	for (UINT i = 0; i < _scene->mNumMaterials; i++)
	{
		aiMaterial* srcMaterial = _scene->mMaterials[i];

		Material* material = new Material();

		material->SetLabel(srcMaterial->GetName().C_Str());

		aiColor3D color;

		srcMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		material->GetMBuffer()->_data.diffuse = Vector4(color.r, color.g, color.b, 1.0f);


		srcMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);
		material->GetMBuffer()->_data.specular = Vector4(color.r, color.g, color.b, 1.0f);

		srcMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);
		material->GetMBuffer()->_data.ambient = Vector4(color.r, color.g, color.b, 1.0f);

		srcMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, color);
		material->GetMBuffer()->_data.emissive = Vector4(color.r, color.g, color.b, 1.0f);

		srcMaterial->Get(AI_MATKEY_SHININESS, material->GetMBuffer()->_data.shininess);

		aiString file;

		srcMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &file);
		material->SetDiffuseMap(CreateTexture(file.C_Str()));

		srcMaterial->GetTexture(aiTextureType_SPECULAR, 0, &file);
		material->SetSpecularMap(CreateTexture(file.C_Str()));

		srcMaterial->GetTexture(aiTextureType_NORMALS, 0, &file);
		material->SetNormalMap(CreateTexture(file.C_Str()));

		string savePath = "_ModelData/Material/" + _name + "/" + material->GetLabel() + ".mat";

		CreateFolder(savePath);

		material->Save(ToWString(savePath));

		_materialNames.push_back(material->GetLabel());

		delete material;
	}

	BinaryWriter data(L"_ModelData/Material/" + ToWString(_name) + L"/MaterialList.list");

	data.WriteData((UINT)_materialNames.size());

	for (string name : _materialNames)
		data.WriteData(name);
}

void ModelExporter::ExportMesh()
{
	ReadMesh(_scene->mRootNode);

	WriteMesh();
}

void ModelExporter::ReadMesh(aiNode* node)
{
	for (UINT i = 0; i < node->mNumMeshes; i++)
	{
		MeshData* mesh = new MeshData();

		mesh->name = node->mName.C_Str();

		UINT index = node->mMeshes[i];

		aiMesh* srcMesh = _scene->mMeshes[index];

		mesh->materialIndex = srcMesh->mMaterialIndex;

		UINT startVertex = mesh->_vertices.size();

		mesh->_vertices.resize(srcMesh->mNumVertices);

		for (UINT j = 0; j < srcMesh->mNumVertices; j++)
		{
			ModelVertex vertex;


			memcpy(&vertex._pos, &srcMesh->mVertices[j], sizeof(Vector3));

			if (srcMesh->HasTextureCoords(0))
				memcpy(&vertex._uv, &srcMesh->mTextureCoords[0][j], sizeof(Vector2));

			if (srcMesh->HasNormals())
				memcpy(&vertex._normal, &srcMesh->mNormals[j], sizeof(Vector3));

			if (srcMesh->HasTangentsAndBitangents())
				memcpy(&vertex._tangent, &srcMesh->mTangents[j], sizeof(Vector3));

			mesh->_vertices[j] = vertex;
		}

		for (size_t j = 0; j < srcMesh->mNumFaces; j++)
		{
			aiFace& face = srcMesh->mFaces[j];

			for (UINT k = 0; k < face.mNumIndices; k++)
			{
				mesh->_indices.push_back(face.mIndices[k] + startVertex);
			}
		}

		_meshes.push_back(mesh);

	}

	for (UINT i = 0; i < node->mNumChildren; i++)
	{
		ReadMesh(node->mChildren[i]);
	}
}

void ModelExporter::WriteMesh()
{
	string path = "_ModelData/Mesh/" + _name + ".mesh";

	CreateFolder(path);

	BinaryWriter data(ToWString(path));

	data.WriteData((UINT)_meshes.size());

	for (MeshData* mesh : _meshes)
	{
		data.WriteData(mesh->name);
		data.WriteData(mesh->materialIndex);
		
		data.WriteData((UINT)mesh->_vertices.size());
		data.WriteData(mesh->_vertices.data(), mesh->_vertices.size() * sizeof(ModelVertex));

		data.WriteData((UINT)mesh->_indices.size());
		data.WriteData(mesh->_indices.data(), mesh->_indices.size() * sizeof(UINT));

		delete mesh;
	}

	_meshes.clear();
}

wstring ModelExporter::CreateTexture(string file)
{
	if (file.length() == 0)
		return L"";

	string fileName = GetFileName(file);

	const aiTexture* texture = _scene->GetEmbeddedTexture(file.c_str());

	string path = "_Texture/Model/" + _name + "/" + fileName;

	CreateFolder(path);

	if (PathFileExistsA(path.c_str()))
		return ToWString(path);

	if (texture == nullptr)
		return L"";

	if (texture->mHeight < 1)
	{
		BinaryWriter data(ToWString(path));
		data.WriteData(texture->pcData, texture->mWidth);
	}
	else
	{
		Image image;
		image.width = texture->mWidth;
		image.height = texture->mHeight;
		image.pixels = (uint8_t*)texture->pcData;
		image.rowPitch = image.width * 4;
		image.slicePitch = image.width * image.height * 4;

		SaveToWICFile(image, WIC_FLAGS_NONE, GetWICCodec(WIC_CODEC_PNG), ToWString(path).c_str());
		
	}

	return wstring();
}
