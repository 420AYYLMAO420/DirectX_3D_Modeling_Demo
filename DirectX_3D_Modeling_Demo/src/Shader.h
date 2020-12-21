#pragma once
#include <wrl.h>
#include <map>
#include "Resource.h"

class Shader : public Resource {
public:
	Shader(const wchar_t* vscso_path, const wchar_t* pscso_path);
	void Make(ID3D11Device* Device);
	void Bind(ID3D11DeviceContext* DeviceContext);
	ID3D10Blob* GetVertexShaderByteCode() const { return VShaderByteCode.Get(); }
private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> VShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> PShader;
	Microsoft::WRL::ComPtr<ID3D10Blob> VShaderByteCode;
	Microsoft::WRL::ComPtr<ID3D10Blob> PShaderByteCode;
};