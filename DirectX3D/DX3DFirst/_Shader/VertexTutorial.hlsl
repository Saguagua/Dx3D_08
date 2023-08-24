
cbuffer World : register(b0)
{
    matrix world;
}

cbuffer View : register(b1)
{
    matrix view;
}

cbuffer Projection : register(b2)
{
    matrix projection;
}

struct VertexInput
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

VertexOutput main(VertexInput input) 
{
    VertexOutput result;
    
    result.position = mul(input.position, world);
    result.position = mul(result.position, view);
    result.position = mul(result.position, projection);
    
    result.color = input.color;
    
	return result;
}
//시멘틱 : 우리가 사용할 변수의 용도
//SV_POSITION ->반환 값을 RS에 넘긴다. SV -> SystemValue