#pragma once

#include "Resource.h"
#include <vector>
#include <wrl.h>

class InputLayout : public Resource {
public:
	InputLayout(ID3D10Blob* ShaderByteCode);

	void Make(ID3D11Device* Device);
	void Bind(ID3D11DeviceContext* DeviceContext);
	void AddAttribute(const char* name, const UINT numComponents);

private:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> InputLayoutObject;
	std::vector<D3D11_INPUT_ELEMENT_DESC> Attributes;
	UINT AttributeOffset;
	ID3D10Blob* ShaderByteCode;
};