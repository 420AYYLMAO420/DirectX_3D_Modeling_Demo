#include "IndexBuffer.h"
#include "Format.h"

IndexBuffer::IndexBuffer(const void* data, const UINT size)
	:Size(size)
{
	BufferDesc.ByteWidth = Size;
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.MiscFlags = NULL;
	BufferDesc.CPUAccessFlags = NULL;
	BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	
	Data = data;
}

void IndexBuffer::Bind(ID3D11DeviceContext* DeviceContext)
{
	DeviceContext->IASetIndexBuffer(BufferObject.Get(), DXGI_FORMAT_R32_UINT, NULL);
}

UINT IndexBuffer::GetNumIndices() const
{
	return Format::GetNumComponents<UINT>(Size);
}
