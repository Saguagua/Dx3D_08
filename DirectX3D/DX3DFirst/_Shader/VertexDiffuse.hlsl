#include "Header.hlsli"

struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 uv : UV;
    float diffuse : DIFFUSE;
};

VertexOutput main(VertexTextureNormal input)
{
    VertexOutput result;
    
    result.position = mul(input.position, world);
    result.position = mul(result.position, view);
    result.position = mul(result.position, projection);
    
    result.uv = input.uv;
    
    //float3 light = normalize(-lightDirection);
    //float3 normalize = normalize(mul(input.normal, (float3x3)world));
    
    //result.diffuse = normalize;
    
    return result;
}
//�ø�ƽ : �츮�� ����� ������ �뵵
//SV_POSITION ->��ȯ ���� RS�� �ѱ��. SV -> SystemValue