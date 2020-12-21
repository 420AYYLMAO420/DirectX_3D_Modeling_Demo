#include "Mesh.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "InputLayout.h"
#include "Format.h"
#include "Texture.h"

Mesh::Mesh(const std::vector<VERTEX>& vertices, const std::vector<UINT>& indices, const std::vector<std::shared_ptr<Texture>>& textures, Shader* shader)
	:ShaderObject(shader), Vertices(vertices), Indices(indices), Textures(textures)
{
	VBuffer = std::make_shared<VertexBuffer>(Vertices.data(), sizeof(VERTEX) * Vertices.size(), sizeof(VERTEX));
	IBuffer = std::make_shared<IndexBuffer>(Indices.data(), sizeof(UINT) * Indices.size());
	ILayout = std::make_shared<InputLayout>(ShaderObject->GetVertexShaderByteCode());
	ILayout->AddAttribute("Pos", Format::GetNumComponents<float>(sizeof(VERTEX::Position)));
	ILayout->AddAttribute("Norm", Format::GetNumComponents<float>(sizeof(VERTEX::Normal)));
	ILayout->AddAttribute("Tex", Format::GetNumComponents<float>(sizeof(VERTEX::TexCoords)));
	ILayout->AddAttribute("Tan", Format::GetNumComponents<float>(sizeof(VERTEX::Tangent)));
	ILayout->AddAttribute("Bitan", Format::GetNumComponents<float>(sizeof(VERTEX::Bitangent)));
}

Mesh::Mesh(const void* vertices, const void* indices, const UINT numVert, const UINT numInd, Shader* shader)
	:ShaderObject(shader)
{
	VBuffer = std::make_shared<VertexBuffer>(vertices, sizeof(VERTEX) * numVert, sizeof(VERTEX));
	IBuffer = std::make_shared<IndexBuffer>(indices, sizeof(UINT) * numInd);
	ILayout = std::make_shared<InputLayout>(ShaderObject->GetVertexShaderByteCode());
	ILayout->AddAttribute("Pos", Format::GetNumComponents<float>(sizeof(VERTEX::Position)));
	ILayout->AddAttribute("Norm", Format::GetNumComponents<float>(sizeof(VERTEX::Normal)));
	ILayout->AddAttribute("Tex", Format::GetNumComponents<float>(sizeof(VERTEX::TexCoords)));
	ILayout->AddAttribute("Tan", Format::GetNumComponents<float>(sizeof(VERTEX::Tangent)));
	ILayout->AddAttribute("Bitan", Format::GetNumComponents<float>(sizeof(VERTEX::Bitangent)));
}

void Mesh::Make(ID3D11Device* Device)
{
	VBuffer->Make(Device);
	IBuffer->Make(Device);
	ILayout->Make(Device);
	if (Textures.size() != 0) {
		for (std::shared_ptr<Texture> texture : Textures)
			texture->Make(Device);
	}
}

void Mesh::Bind(ID3D11DeviceContext* DeviceContext)
{
	VBuffer->Bind(DeviceContext);
	IBuffer->Bind(DeviceContext);
	ILayout->Bind(DeviceContext);
	if (Textures.size() != 0) {
		for (std::shared_ptr<Texture> texture : Textures)
			texture->Bind(DeviceContext);
	}
}

void Mesh::Render(ID3D11DeviceContext* DeviceContext)
{
	DeviceContext->DrawIndexed(IBuffer->GetNumIndices(), 0, 0);
}
