
struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 uv : UV;
};

Texture2D     map   : register(t0);
//이미지 파인
SamplerState samp   : register(s0);
//Desc 같은 거 설정값 결정

float4 main(VertexOutput input) : SV_TARGET
{
    float4 tex = map.Sample(samp, input.uv);
    return tex;
}

//선형보간으로 색상을 섞는다
//가중평균을 사용