#pragma once

#include <DirectXMath.h>
#include <d3d11.h>
#include "Resource.h"
#include <string>
#include <vector>
#include <memory>

struct VERTEX {
    // position
    struct {
        float X, Y, Z;
    } Position;
    // normal
    struct {
        float X, Y, Z;
    } Normal;
    // texCoords
    struct {
        float U, V;
    } TexCoords;
    // tangent
    struct {
        float X, Y, Z;
    } Tangent;
    // bitangent
    struct {
        float X, Y, Z;
    } Bitangent;
};

class Mesh : public Resource {
public:
    Mesh(const std::vector<VERTEX>& vertices, const std::vector<UINT>& indices, const std::vector<std::shared_ptr<class Texture>>& textures, class Shader* shader);
    Mesh(const void* vertices, const void* indices, const UINT numVert, const UINT numInd, class Shader* shader);
    void Make(ID3D11Device* Device);
    void Bind(ID3D11DeviceContext* DeviceContext);
    void Render(ID3D11DeviceContext* DeviceContext);
    std::vector<VERTEX> Vertices;
    std::vector<UINT> Indices;
    std::vector<std::shared_ptr<class Texture>> Textures;
private:
    std::shared_ptr<class VertexBuffer> VBuffer;
    std::shared_ptr<class IndexBuffer> IBuffer;
    std::shared_ptr<class InputLayout> ILayout;
    class Shader* ShaderObject;
};