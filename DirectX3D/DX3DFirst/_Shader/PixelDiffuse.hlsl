#include "Header.hlsli"

struct VertexOutput
{
    float4 pos : SV_Position;
    float2 uv : UV;
    float diffuse : DIFFUSE;
};

float4 main(VertexOutput input) : SV_TARGET
{
    return diffuseMap.Sample(samp, input.uv) * input.diffuse;
}