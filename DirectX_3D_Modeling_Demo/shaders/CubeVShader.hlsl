cbuffer Transform
{
    matrix transform;
    matrix modelView;
};

float4 main(float3 pos : Pos) : SV_Position
{
    return mul(float4(pos, 1.f),  transform);
}

