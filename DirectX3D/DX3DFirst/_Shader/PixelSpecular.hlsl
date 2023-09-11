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
    
    float specularIntensity = 0;
    
    float3 reflection = normalize(reflect(L, input.normal));
    
    if (hasSpecularMap)
        specularIntensity = saturate(dot(-reflection, input.viewDir));
    
    float4 specularSample = float4(1, 1, 1, 1);
    
    specularSample = specularMap.Sample(samp, input.uv);
    
    float4 diffuse = albedo * diffuseIntensity * mDiffuse;
    
    float4 specular = pow(specularIntensity, shininess) * specularSample * mSpecular;
    
    float4 ambient = albedo * ambientLight * mAmbient;
    
    return diffuse + specular + ambient; //pphong shading
}