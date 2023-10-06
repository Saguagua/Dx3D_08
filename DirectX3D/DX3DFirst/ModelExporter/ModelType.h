#pragma once
typedef VertexTextureNormalTangent ModelVertex;

struct MeshData
{
	string name;

	UINT materialIndex;

	vector<ModelVertex> _vertices;
	vector<UINT>		 _indices;
};