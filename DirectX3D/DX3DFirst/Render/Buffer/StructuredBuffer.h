#pragma once
class StructuredBuffer
{
public:
	StructuredBuffer(void* inputData, UINT inputStride, UINT inputCount, UINT outputStride, UINT outputCount);
	~StructuredBuffer();

	void Copy(void* data, UINT size);

	ID3D11UnorderedAccessView* GetUAV() { return _uav; }
	ID3D11ShaderResourceView* GetSRV() { return _srv; }

	void UpdateInput(void* data);

	void SetSRV();
	void SetUAV();
private:
	void CreateUAV();
	void CreateInput();
	void CreateOutput();
	void CreateSRV();
	void CreateResult();

private:
	ID3D11UnorderedAccessView* _uav;  // 계산된 정보를 가져오기 위한 용도 (병렬연산을 하는 구조에선 읽기가 힘들고 비효율적)
	ID3D11ShaderResourceView* _srv;   // 읽기용
	//둘 다 셰이더에 정보를 보내기 위한 용도로 사용


	ID3D11Resource* _input;
	ID3D11Resource* _output;
	ID3D11Resource* _result;

	void* _inputData;
	UINT _inputStride;
	UINT _inputCount;

	UINT _outputStride;
	UINT _outputCount;
};

