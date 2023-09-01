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
//시멘틱 : 우리가 사용할 변수의 용도
//SV_POSITION ->반환 값을 RS에 넘긴다. SV -> SystemValue