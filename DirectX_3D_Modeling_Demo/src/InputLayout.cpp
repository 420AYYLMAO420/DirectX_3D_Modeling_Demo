#include "InputLayout.h"
#include "Format.h"
InputLayout::InputLayout(ID3D10Blob* ShaderByteCode)
	:AttributeOffset(0), ShaderByteCode(ShaderByteCode)
{
}

void InputLayout::AddAttribute(const char* name, const UINT numComponents) {
	
	D3D11_INPUT_ELEMENT_DESC InputDesc;
	SecureZeroMemory(&InputDesc, sizeof(D3D11_INPUT_ELEMENT_DESC));
	InputDesc.Format = Format::GetFormat(numComponents);
	InputDesc.SemanticName = name;
	InputDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	InputDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	Attributes.push_back(InputDesc);
}

void InputLayout::Make(ID3D11Device* Device)
{
	Device->CreateInputLayout(Attributes.data(), Attributes.size(),
		ShaderByteCode->GetBufferPointer(), ShaderByteCode->GetBufferSize(), InputLayoutObject.GetAddressOf());
}

void InputLayout::Bind(ID3D11DeviceContext* DeviceContext)
{
	DeviceContext->IASetInputLayout(InputLayoutObject.Get());
}


