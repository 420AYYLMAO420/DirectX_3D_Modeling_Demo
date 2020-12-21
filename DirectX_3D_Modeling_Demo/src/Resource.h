#pragma once
#include <d3d11.h>

class Resource {
public:
	virtual void Make(ID3D11Device* Device) = 0;
	virtual void Bind(ID3D11DeviceContext* DeviceContext) = 0;
};