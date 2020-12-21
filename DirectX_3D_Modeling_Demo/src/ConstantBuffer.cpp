#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer(const void* initData, const UINT size, const SHADER type, const UINT slot)
    :ShaderType(type), Slot(slot)
{
    BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    BufferDesc.ByteWidth = size;

    Data = initData;
}

void ConstantBuffer::Bind(ID3D11DeviceContext* DeviceContext)
{
    switch (ShaderType) {
    case SHADER::VERTEX:
        DeviceContext->VSSetConstantBuffers(Slot, 1, BufferObject.GetAddressOf());
        break;
    case SHADER::PIXEL:
        DeviceContext->PSSetConstantBuffers(Slot, 1, BufferObject.GetAddressOf());
        break;
    default:
        OutputDebugString(L"\nShader type not specified\n");
    }
   
}

void ConstantBuffer::Update(ID3D11DeviceContext* context, const void* data, const UINT size)
{
    D3D11_MAPPED_SUBRESOURCE mapped;
    context->Map(BufferObject.Get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mapped);
    memcpy(mapped.pData, data, size);
    context->Unmap(BufferObject.Get(), NULL);
}
