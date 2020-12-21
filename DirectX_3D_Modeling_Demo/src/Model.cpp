#include "Model.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <d3d11.h>
#include <string>
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

std::string directory;

Model::Model(const std::string& path, Shader* shader)
:ShaderObject(shader) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        OutputDebugStringA(importer.GetErrorString());
    }

    directory = path.substr(0, path.find_last_of('/'));

    for (UINT meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++) {
        const aiMesh* mesh = scene->mMeshes[meshIndex];
        std::vector<VERTEX> Vertices;
        std::vector<UINT> Indices;

        for (UINT vert = 0; vert < mesh->mNumVertices; vert++) {
            VERTEX vertex = {};
            vertex.Position.X = mesh->mVertices[vert].x;
            vertex.Position.Y = mesh->mVertices[vert].y;
            vertex.Position.Z = mesh->mVertices[vert].z;

            if (mesh->HasNormals()) {
                vertex.Normal.X = mesh->mNormals[vert].x;
                vertex.Normal.Y = mesh->mNormals[vert].y;
                vertex.Normal.Z = mesh->mNormals[vert].z;
            }

            if (mesh->mTextureCoords[0]) {
                vertex.TexCoords.U = mesh->mTextureCoords[0][vert].x;
                vertex.TexCoords.V = mesh->mTextureCoords[0][vert].y;

                if (mesh->HasTangentsAndBitangents()) {
                    vertex.Tangent.X = mesh->mTangents[vert].x;
                    vertex.Tangent.Y = mesh->mTangents[vert].y;
                    vertex.Tangent.Z = mesh->mTangents[vert].z;

                    vertex.Bitangent.X = mesh->mBitangents[vert].x;
                    vertex.Bitangent.Y = mesh->mBitangents[vert].y;
                    vertex.Bitangent.Z = mesh->mBitangents[vert].z; 
                }
            }

            Vertices.push_back(vertex);
        }

        for (UINT faceIndex = 0; faceIndex < mesh->mNumFaces; faceIndex++)
        {
            const aiFace face = mesh->mFaces[faceIndex];
            for (UINT indIndex = 0; indIndex < face.mNumIndices; indIndex++)
                Indices.push_back(face.mIndices[indIndex]);
        }

        std::vector<std::shared_ptr<Texture>> textures;
        if (mesh->mMaterialIndex >= 0) {
            const aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

            if(std::shared_ptr<Texture> diffuse = GetTexture(material, aiTextureType_DIFFUSE, 0))
                textures.push_back(diffuse);
            if(std::shared_ptr<Texture> specular = GetTexture(material, aiTextureType_SPECULAR, 1))
                textures.push_back(specular);
            if (std::shared_ptr<Texture> normal = GetTexture(material, aiTextureType_NORMALS, 2))
                textures.push_back(normal);
        }

        Meshes.push_back(std::make_shared<Mesh>(Vertices, Indices, textures, ShaderObject));
    }
}

Model::Model()
: ShaderObject(nullptr)
{
}

void Model::Make(ID3D11Device* Device)
{
    for(std::shared_ptr<Mesh> mesh : Meshes)
        mesh->Make(Device);
}

#define PADDING 4

std::shared_ptr<Texture> Model::GetTexture(const aiMaterial* mat, const aiTextureType type, const UINT slot)
{
    aiString texName;
    mat->GetTexture(type, 0, &texName);
    if (texName.length == NULL)
        return nullptr;
    std::string texPath = std::string(texName.C_Str() + PADDING, texName.C_Str() + texName.length + PADDING);
    texPath = directory + '/' + texPath;
    return std::make_shared<Texture>(texPath.c_str(), slot);
}

void Model::Bind(ID3D11DeviceContext* DeviceContext)
{
    
}

void Model::Render(ID3D11DeviceContext* DeviceContext)
{
    ShaderObject->Bind(DeviceContext);
    for (std::shared_ptr<Mesh> mesh : Meshes) {
        mesh->Bind(DeviceContext);
        mesh->Render(DeviceContext);
    }
}
