#include "Header.hlsli"

struct VertexOutput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float diffuse : DIFFUSE;
};

VertexOutput main(VertexColorNormal input)
{
    VertexOutput result;
    
    result.position = mul(input.pos, world);
    result.position = mul(result.position, view);
    result.position = mul(result.position, proj);
    
    result.color = input.color;
    
    float3 L = normalize(-lightDirection);
    float3 N = normalize(mul(input.normal, (float3x3) world));
    
    result.diffuse = dot(N, L);
    
    return result;
}