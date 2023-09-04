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
    
    result.position = mul(input.pos, world);
    result.position = mul(result.position, view);
    result.position = mul(result.position, proj);
    
    result.uv = input.uv;
    
    float3 L = normalize(-lightDirection);
    float3 N = normalize(mul(input.normal, (float3x3)world));
    
    result.diffuse = dot(N, L);
    
    return result;
}
//�ø�ƽ : �츮�� ����� ������ �뵵
//SV_POSITION ->��ȯ ���� RS�� �ѱ��. SV -> SystemValue