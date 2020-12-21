struct VOut
{
    float4 pos : SV_Position;
    float3 norm : Normal;
    float2 tex : TexCoord;
};

cbuffer Transform
{
    matrix transform;
    matrix modelView;
};


VOut main(float3 pos : Pos, float2 tex : Tex, float3 norm : Norm)
{
    VOut vertex;
    vertex.pos = mul(float4(pos, 1.f), transform);
    vertex.tex = tex;
    vertex.norm = mul(norm, (float3x3) modelView);
    return vertex;
}