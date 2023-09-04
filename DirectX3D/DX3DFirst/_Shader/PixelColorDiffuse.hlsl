#include "Header.hlsli"

struct VertexOutput
{
    float4 pos : SV_Position;
    float4 color : COLOR;
    float diffuse : DIFFUSE;
};

float4 main(VertexOutput output) : SV_TARGET
{
	return output.color * output.diffuse;
}