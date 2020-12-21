#pragma once
#include "Resource.h"
#include <wrl.h>

class RenderTarget : public Resource {   
public:
    RenderTarget(IDXGISwapChain* SwapChain)
    :DSV(nullptr) {
        SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBuffer);
    }

    void Make(ID3D11Device* Device) {
        Device->CreateRenderTargetView(BackBuffer, NULL, Target.GetAddressOf());
        BackBuffer->Release();
    }

    void Bind(ID3D11DeviceContext* DeviceContext) {
        DeviceContext->OMSetRenderTargets(1, Target.GetAddressOf(), DSV);
    }

    void SetDepthStencilView(ID3D11DepthStencilView* dsv) { DSV = dsv; }

    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetView() const { return Target; }
private:
    ID3D11Texture2D* BackBuffer;
    ID3D11DepthStencilView* DSV;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> Target;
};