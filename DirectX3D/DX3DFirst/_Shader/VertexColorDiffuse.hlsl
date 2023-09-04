#include "Header.hlsli"

struct VertexOutput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float3 normal : NORMAL;
};

VertexOutput main(VertexColorNormal input)
{
    VertexOutput result;
    
    result.position = mul(input.pos, world);
    result.position = mul(result.position, view);
    result.position = mul(result.position, proj);
    
    result.color = input.color;
    
    result.normal = normalize(mul(input.normal, (float3x3) world));

    return result;
}