/************* Resources *************/

cbuffer CBufferPerObject
{
    float4x4 WorldViewProjection : WORLDVIEWPROJECTION; 
}

/************* Data Structures *************/

struct VS_INPUT
{
    float4 ObjectPosition: POSITION;
    float4 Color : COLOR;
	float4 Normal: NORMAL;
};

struct VS_OUTPUT 
{
    float4 Position: SV_Position;
	float4 Color : COLOR;
	float4 Normal: NORMAL;
};

RasterizerState DisableCulling
{
    CullMode = NONE;
};

/************* Vertex Shader *************/

VS_OUTPUT vertex_shader(VS_INPUT IN)
{
    VS_OUTPUT OUT = (VS_OUTPUT)0;
    
    OUT.Position = mul(IN.ObjectPosition, WorldViewProjection);
    OUT.Color = IN.Color;
	OUT.Normal = IN.Normal;
    return OUT;
}

/************* Pixel Shader *************/

float4 pixel_shader(VS_OUTPUT IN) : SV_Target
{
	float3 lightDir;
	float4 color;
	float intensity;
	float4 shadowcol = float4(0.5f,0,0.2f,1);

	color = IN.Color;
	lightDir = float4(-0.1f, -1, 1, 1);
	intensity = dot(IN.Normal,lightDir);
	color = lerp(color,shadowcol,intensity);
	

    return color;
}

/************* Techniques *************/

technique11 main11
{
    pass p0
    {
        SetVertexShader(CompileShader(vs_5_0, vertex_shader()));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_5_0, pixel_shader()));

        SetRasterizerState(DisableCulling);
    }
}