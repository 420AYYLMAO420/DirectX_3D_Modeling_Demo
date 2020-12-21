#include "Shader.h"
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

Shader::Shader(const wchar_t* vscso_path, const wchar_t* pscso_path)
{
    D3DReadFileToBlob(vscso_path, VShaderByteCode.GetAddressOf());
    D3DReadFileToBlob(pscso_path, PShaderByteCode.GetAddressOf());
}

void Shader::Make(ID3D11Device* Device)
{
    Device->CreateVertexShader(VShaderByteCode->GetBufferPointer(),
        VShaderByteCode->GetBufferSize(), nullptr, VShader.GetAddressOf());
    Device->CreatePixelShader(PShaderByteCode->GetBufferPointer(),
        PShaderByteCode->GetBufferSize(), nullptr, PShader.GetAddressOf());
}

void Shader::Bind(ID3D11DeviceContext* DeviceContext)
{
    DeviceContext->VSSetShader(VShader.Get(), nullptr, 0);
    DeviceContext->PSSetShader(PShader.Get(), nullptr, 0);
}



