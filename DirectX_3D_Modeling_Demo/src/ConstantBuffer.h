#pragma once

#include <wrl.h>
#include "Buffer.h"

enum class SHADER {
	VERTEX, PIXEL
};

class ConstantBuffer : public Buffer {
public:
	ConstantBuffer(const void* initData, const UINT size, const SHADER type, const UINT slot);
	void Bind(ID3D11DeviceContext* DeviceContext) override;
	void Update(ID3D11DeviceContext* context, const void* data, const UINT size);

private:
	SHADER ShaderType;
	UINT Slot;
};