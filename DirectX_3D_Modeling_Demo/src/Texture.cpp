#include "Texture.h"
#include "Format.h"
#include <comdef.h>

Texture::Texture(const char* path, const UINT slot)
	:Slot(slot)
{
	wchar_t w_path[128];
	mbstowcs_s(nullptr, w_path, path, _TRUNCATE);
	DirectX::LoadFromWICFile(w_path, DirectX::WIC_FLAGS_IGNORE_SRGB, nullptr, scratch);
}

Texture::~Texture()
{
}

void Texture::Make(ID3D11Device* Device)
{
	SecureZeroMemory(&TextureDesc, sizeof(D3D11_TEXTURE2D_DESC));
	TextureDesc.Width = scratch.GetMetadata().width;
	TextureDesc.Height = scratch.GetMetadata().height;
	TextureDesc.MipLevels = 1;
	TextureDesc.ArraySize = 1;
	TextureDesc.Format = scratch.GetMetadata().format;
	TextureDesc.Usage = D3D11_USAGE_DEFAULT;
	TextureDesc.SampleDesc.Count = 1;
	TextureDesc.SampleDesc.Quality = 0;
	TextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	TextureDesc.CPUAccessFlags = 0;
	TextureDesc.MiscFlags = 0;

	SecureZeroMemory(&SubResData, sizeof(D3D11_SUBRESOURCE_DATA));
	SubResData.pSysMem = scratch.GetPixels();
	SubResData.SysMemPitch = sizeof(UINT32) * scratch.GetMetadata().width;
	Device->CreateTexture2D(&TextureDesc, &SubResData, TextureObject.GetAddressOf());

	SecureZeroMemory(&TextureViewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	TextureViewDesc.Format = TextureDesc.Format;
	TextureViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	TextureViewDesc.Texture2D.MostDetailedMip = 0;
	TextureViewDesc.Texture2D.MipLevels = 1;
	Device->CreateShaderResourceView(TextureObject.Get(), &TextureViewDesc, TextureView.GetAddressOf());
}

void Texture::Bind(ID3D11DeviceContext* DeviceContext)
{
	DeviceContext->PSSetShaderResources(Slot, 1, TextureView.GetAddressOf());
}
