#include "framework.h"
#include "Quad.h"

Quad::Quad(Vector2 size)
{
	float L = -size.x * 0.5f;
	float R = +size.x * 0.5f;
	float B = -size.y * 0.5f;
	float T = +size.y * 0.5f;

	_vertices =
	{
		{Vector3(L, T, 0.0f), Vector2(0.0f, 0.0f)},
		{Vector3(R, T, 0.0f), Vector2(1.0f, 0.0f)},
		{Vector3(L, B, 0.0f), Vector2(0.0f, 1.0f)},
		{Vector3(R, B, 0.0f), Vector2(1.0f, 1.0f)},
	};

	_indices =
	{
		0, 1, 2,
		2, 1, 3
	};

	_mesh = new Mesh(_vertices, _indices);

	_material = new Material();
	_material->SetShader(L"Texture");

	_worldBuffer = new MatrixBuffer();

	////////////////Texture
	ScratchImage image;
	LoadFromWICFile(L"_Texture/Landscape/Box.png", WIC_FLAGS_NONE, nullptr, image);

	CreateShaderResourceView(
		DEVICE,
		image.GetImages(),
		image.GetImageCount(),
		image.GetMetadata(),
		&_srv
	);

	D3D11_SAMPLER_DESC samplerDesc = {};

	samplerDesc.Filter		   = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.AddressU	   = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV	   = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW	   = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.MinLOD		   = 0;
	samplerDesc.MaxLOD		   = D3D11_FLOAT32_MAX;
	//LOD : Level Of Detail
}

Quad::~Quad()
{
	delete _mesh;
	delete _worldBuffer;

	_srv->Release();
	_samplerState->Release();
}

void Quad::Render()
{
	_worldBuffer->SetData(Transform::_world);
	_worldBuffer->SetVSBuffer(0);

	_material->SetMaterial();
	_mesh->SetMesh();

	DC->PSSetShaderResources(0, 1, &_srv);
	DC->PSSetSamplers(0,1,&_samplerState);

	DC->DrawIndexed(_indices.size(), 0, 0);
}
