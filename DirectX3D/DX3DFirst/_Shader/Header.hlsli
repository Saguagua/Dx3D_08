
cbuffer World : register(b0)
{
    matrix world;
}

cbuffer View : register(b1)
{
    matrix view;
}

cbuffer LightDirection : register(b3)
{
    float3 lightDirection;
}

cbuffer Projection : register(b2)
{
    matrix projection;
}

struct VertexTexture
{
    float4 position : POSITION;
    float2 uv : UV;
};

struct VertexColor
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct VertexTextureNormal
{
    float4 position : POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
};


Texture2D diffuseMap : register(t0);
//이미지 파인
SamplerState samp : register(s0);
//Desc 같은 거 설정값 결정