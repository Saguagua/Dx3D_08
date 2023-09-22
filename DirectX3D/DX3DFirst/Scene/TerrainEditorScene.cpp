#include "framework.h"
#include "TerrainEditorScene.h"

TerrainEditorScene::TerrainEditorScene()
{
	_terrainEditor = new TerrainEditor();
	_terrainEditor->GetMaterial()->SetDiffuseMap(L"Landscape/FieldStone_DM.tga");
	_terrainEditor->GetMaterial()->SetSpecularMap(L"Landscape/FieldStone_SM.tga");
	_terrainEditor->GetMaterial()->SetNormalMap(L"Landscape/FieldStone_NM.tga");
	//RawData();

	BinaryWriter data(L"Data");
	data.WriteData(10);
	data.WriteData(10.0f);
}

TerrainEditorScene::~TerrainEditorScene()
{
	delete _terrainEditor;
}

void TerrainEditorScene::Update()
{
	_terrainEditor->Update();
	
}

void TerrainEditorScene::PreRender()
{
}

void TerrainEditorScene::Render()
{
	_terrainEditor->Render();
}

void TerrainEditorScene::PostRender()
{
	_terrainEditor->Debug();
	_terrainEditor->GetMaterial()->SelectMap();
}

void TerrainEditorScene::RawData()
{
	ComputeShader* shader = Shader::GetCS(L"ByteAddress");

	struct Output
	{
		UINT groupID[3];
		UINT groupThreadID[3];
		UINT dispatchThreadID[3];
		UINT groupIndex;
	};

	UINT size = 10 * 8 * 3 * 2;

	Output* output = new Output[size];

	RawBuffer* buffer = new RawBuffer(nullptr, sizeof(Output) * size);

	ID3D11UnorderedAccessView* uav = buffer->GetUAV();

	shader->SetShader();
	
	DC->CSSetUnorderedAccessViews(0, 1, &uav, nullptr);
	DC->Dispatch(2, 1, 1); //Compute Shader�� ����-> ������ �׷��� ������ �˷��ش�

	buffer->Copy(output, sizeof(Output)* size);

	FILE* file;
	fopen_s(&file, "_TextData/RawTest.csv", "w");

	for (size_t i = 0; i < size; i++)
	{
		fprintf
		(
			file,
			"%d, %d,%d,%d, %d,%d,%d, %d,%d,%d, %d,\n",
			i,
			output[i].groupID[0],
			output[i].groupID[1],
			output[i].groupID[2],
			output[i].groupThreadID[0],
			output[i].groupThreadID[1],
			output[i].groupThreadID[2],
			output[i].dispatchThreadID[0],
			output[i].dispatchThreadID[1],
			output[i].dispatchThreadID[2],
			output[i].groupIndex
		);
	}

	//�� ���μ����� ������ �׷�

	fclose(file);

	delete buffer;

	delete output;
}
