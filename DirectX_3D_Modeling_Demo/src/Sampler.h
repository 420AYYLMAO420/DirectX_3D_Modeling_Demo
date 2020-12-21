#pragma once
#include <wrl.h>
#include "Resource.h"

class Sampler : public Resource {
public:
	Sampler();
	void Make(ID3D11Device* Device);
	void Bind(ID3D11DeviceContext* DeviceContext);

private:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> SamplerState;
	D3D11_SAMPLER_DESC SamplerDesc;
};