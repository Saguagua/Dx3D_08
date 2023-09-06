#include "Header.hlsli"

struct VertexOutput
{
    float4 pos : SV_Position;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 viewDir : VIEWDIR;
};

float4 main(VertexOutput input) : SV_TARGET
{
    
    float3 L = normalize(lightDirection);
    
    float diffuseIntensity = saturate(dot(input.normal, -L));
    
    float4 albedo = float4(1, 1, 1, 1);
    
    if (hasDiffuseMap)
        albedo = diffuseMap.Sample(samp, input.uv);
    
    float4 diffuse = albedo * diffuseIntensity;
    
    
    float specularIntensity = 0;
    
    float3 reflection = normalize(reflect(L, input.normal));
    
    if (hasSpecularMap)
        specularIntensity = saturate(dot(-reflection, input.viewDir));
    
    float4 specularMapIntensity = float4(1, 1, 1, 1);
    
    specularMapIntensity = specularMap.Sample(samp, input.uv);
    
    specularIntensity = pow(specularIntensity, shininess) * specularMapIntensity;
    
    float4 specular = albedo * specularIntensity;
    
    float4 ambient = albedo * ambientLight;
    
    return diffuse + specular + ambient; //pphong shading
}