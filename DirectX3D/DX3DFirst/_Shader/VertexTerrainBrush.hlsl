#include "Header.hlsli"

struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 tangent : TANGENT; //x
    float3 binormal : BINORMAL; //y
    float3 viewDir : VIEWDIR;
    
    float3 worldPos : POSITION;
};

VertexOutput main(VertexTextureNormalTangent input)
{
    VertexOutput result;
    
    result.position = mul(input.pos, world);
    
    result.worldPos = result.position;
    
    float3 cameraPos = invView._41_42_43;
    
    result.viewDir = normalize(result.position.xyz - cameraPos);
    
    result.position = mul(result.position, view);
    result.position = mul(result.position, proj);
    
    result.uv = input.uv;
    
    result.normal = normalize(mul(input.normal, (float3x3) world));
    
    result.tangent = normalize(mul(input.tangent, (float3x3) world));
    result.binormal = cross(result.normal, result.tangent);
    return result;
}
//시멘틱 : 우리가 사용할 변수의 용도
//SV_POSITION ->반환 값을 RS에 넘긴다. SV -> SystemValue