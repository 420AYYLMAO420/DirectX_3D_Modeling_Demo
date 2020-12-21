#include <vector>
#include <string>
#include <d3d11.h>
#include <memory>
#include "Resource.h"

class Model : public Resource {
public:
	Model(const std::string& path, class Shader* shader);
	Model();
	virtual void Make(ID3D11Device* Device);
	virtual void Render(ID3D11DeviceContext* DeviceContext);
private:
	std::shared_ptr<class Texture> GetTexture(const struct aiMaterial* mat, const enum aiTextureType type, const UINT slot);
	virtual void Bind(ID3D11DeviceContext* DeviceContext);

protected:
	std::vector<std::shared_ptr<class Mesh>> Meshes;
	class Shader* ShaderObject;

private:
};