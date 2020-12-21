#pragma once
#include <d3d11.h>
#include <wrl.h>
#include "Resource.h"

class DepthStencil : public Resource {
public:
	DepthStencil(const UINT width, const UINT height);
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> GetView() const { return DSView; }
	void Make(ID3D11Device* Device);
	void Bind(ID3D11DeviceContext* DeviceContext);
private:
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> DSState;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> DSBuffer;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> DSView;

	D3D11_DEPTH_STENCIL_DESC DSDesc;
	D3D11_TEXTURE2D_DESC DSBufferDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC DSVDesc;

};