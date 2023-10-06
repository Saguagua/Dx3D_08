#include "framework.h"
#include "TerrainEditorScene.h"

TerrainEditorScene::TerrainEditorScene()
{
	_terrainEditor = new TerrainEditor();

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
	DC->Dispatch(2, 1, 1); //Compute Shader의 시작-> 쓰레드 그룹의 갯수를 알려준다

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

	//논리 프로세스는 쓰레드 그룹

	fclose(file);

	delete buffer;

	delete output;
}
