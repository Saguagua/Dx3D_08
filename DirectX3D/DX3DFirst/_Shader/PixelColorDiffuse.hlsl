#include "Header.hlsli"

struct VertexOutput
{
    float4 pos : SV_Position;
    float4 color : COLOR;
    float3 normal : NORAML;
};

float4 main(VertexOutput output) : SV_TARGET
{
        
    float3 L = normalize(-lightDirection);
    float diffuse = dot(output.normal, L);
    
	return output.color * diffuse;
}