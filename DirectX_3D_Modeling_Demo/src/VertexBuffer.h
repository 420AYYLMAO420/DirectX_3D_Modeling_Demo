#pragma once
#include "Buffer.h"

class VertexBuffer : public Buffer {
public:
	VertexBuffer(const void* data, const UINT size, const UINT stride);
	void Bind(ID3D11DeviceContext* DeviceContext) override;

private:
	UINT Stride;
};