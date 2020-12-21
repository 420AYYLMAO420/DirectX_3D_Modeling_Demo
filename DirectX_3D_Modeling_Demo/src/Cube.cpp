#include "Cube.h"
#include "Shader.h"
#include "Format.h"
#include <DirectXMath.h>
#include "Mesh.h"
#include "ConstantBuffer.h"

const VERTEX vertices[] =
{
    {-0.5f,  0.5f, -0.5f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f}, 
    { 0.5f,  0.5f, -0.5f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f},
    { 0.5f,  0.5f,  0.5f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f},
    {-0.5f,  0.5f,  0.5f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f},
                       
    {-0.5f, -0.5f,  0.5f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f},
    { 0.5f, -0.5f,  0.5f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f},
    { 0.5f, -0.5f, -0.5f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f},
    {-0.5f, -0.5f, -0.5f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f}
};

//array of indices the index buffer will use
const unsigned int indices[] = {
    0, 1, 2,
    0, 2, 3,

    4, 5, 6,
    4, 6, 7,

    3, 2, 5,
    3, 5, 4,

    2, 1, 6,
    2, 6, 5,

    1, 7, 6,
    1, 0, 7,

    0, 3, 4,
    0, 4, 7
};

struct COLOR {
    float R, G, B, A;
};

COLOR Colors[6] = {
    {1.f, 1.f, 1.f, 1.f},
    {1.f, 0.f, 0.f, 1.f}, 
    {1.f, 0.f, 1.f, 1.f},
    {0.f, 0.f, 1.f, 1.f},
    {0.f, 1.f, 0.f, 1.f},
    {0.f, 0.f, 0.f, 1.f}
};

Cube::Cube(Shader* shader)
{
    Meshes.push_back(std::make_shared<Mesh>(vertices, indices, std::size(vertices), std::size(indices), shader));

    ShaderObject = shader;
}

void Cube::Make(ID3D11Device* device)
{
    __super::Make(device);
}

void Cube::Bind(ID3D11DeviceContext* context)
{
    
}
