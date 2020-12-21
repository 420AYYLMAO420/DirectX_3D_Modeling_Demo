#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, const UINT size, const UINT stride)
    :Stride(stride)
{
    BufferDesc.Usage = D3D11_USAGE_DEFAULT;
    BufferDesc.ByteWidth = size;
    BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    BufferDesc.CPUAccessFlags = NULL;
    BufferDesc.MiscFlags = NULL;
    BufferDesc.StructureByteStride = Stride;

    Data = data;
}

void VertexBuffer::Bind(ID3D11DeviceContext* DeviceContext)
{
    const UINT offset = 0;
    DeviceContext->IASetVertexBuffers(0, 1, BufferObject.GetAddressOf(), &Stride, &offset);
}
