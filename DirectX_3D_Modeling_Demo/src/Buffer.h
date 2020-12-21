#pragma once
#include <wrl.h>
#include "Resource.h"
#include <comdef.h>

class Buffer : public Resource {
public:
	Buffer() : Data(nullptr) {
		SecureZeroMemory(&BufferDesc, sizeof(D3D11_BUFFER_DESC));
	}

	virtual void Make(ID3D11Device* Device) {
		D3D11_SUBRESOURCE_DATA SubResData;
		SecureZeroMemory(&SubResData, sizeof(D3D11_SUBRESOURCE_DATA));
		SubResData.pSysMem = Data;
		SubResData.SysMemPitch = 0;
		SubResData.SysMemSlicePitch = 0;
		HRESULT hr = Device->CreateBuffer(&BufferDesc, &SubResData, BufferObject.GetAddressOf());
		if (FAILED(hr)) {
			_com_error error(hr);
			MessageBox(NULL, error.ErrorMessage(), L"Error", MB_OK);
		}
	}

	virtual void Bind(ID3D11DeviceContext* DeviceContext) {}

protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> BufferObject;
	const void* Data;
	D3D11_BUFFER_DESC BufferDesc;
};