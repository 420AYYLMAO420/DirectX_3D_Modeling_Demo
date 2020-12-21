#pragma once
#include "Buffer.h"

class IndexBuffer : public Buffer {
public:
	IndexBuffer(const void* data, const UINT size);
	void Bind(ID3D11DeviceContext* DeviceContext) override;
	UINT GetNumIndices() const;
private:
	UINT Size;
};