
struct VertexOutput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

float4 main(VertexOutput input) : SV_TARGET
{
	return input.color;
}

//선형보간으로 색상을 섞는다
//가중평균을 사용