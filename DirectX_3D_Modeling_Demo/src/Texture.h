#pragma once

#include <wrl.h>
#include <DirectXTex/DirectXTex.h>
#include "Resource.h"

class Texture : public Resource {
public:
	Texture(const char* path, const UINT slot);
	~Texture();
	void Make(ID3D11Device* Device);
	void Bind(ID3D11DeviceContext* DeviceContext);

private:
	Microsoft::WRL::ComPtr<ID3D11Texture2D> TextureObject;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> TextureView;
	D3D11_SHADER_RESOURCE_VIEW_DESC TextureViewDesc;
	D3D11_TEXTURE2D_DESC TextureDesc;
	D3D11_SUBRESOURCE_DATA SubResData;
	DirectX::ScratchImage scratch;
	UINT Slot;
};