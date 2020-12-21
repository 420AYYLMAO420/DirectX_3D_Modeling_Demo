#include "Sampler.h"

Sampler::Sampler()
{
	SecureZeroMemory(&SamplerDesc, sizeof(D3D11_SAMPLER_DESC));
	SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
}

void Sampler::Make(ID3D11Device* Device)
{
	Device->CreateSamplerState(&SamplerDesc, SamplerState.GetAddressOf());
}

void Sampler::Bind(ID3D11DeviceContext* DeviceContext)
{
	DeviceContext->PSSetSamplers(0, 1, SamplerState.GetAddressOf());
}
