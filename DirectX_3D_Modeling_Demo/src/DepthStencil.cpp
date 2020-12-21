#include "DepthStencil.h"

DepthStencil::DepthStencil(const UINT width, const UINT height)
{
    SecureZeroMemory(&DSBufferDesc, sizeof(D3D11_TEXTURE2D_DESC));
    DSBufferDesc.Width = width;
    DSBufferDesc.Height = height;
    DSBufferDesc.MipLevels = 1;
    DSBufferDesc.ArraySize = 1;
    DSBufferDesc.Format = DXGI_FORMAT_D32_FLOAT;
    DSBufferDesc.SampleDesc.Count = 1;
    DSBufferDesc.SampleDesc.Quality = 0;
    DSBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    DSBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    DSBufferDesc.CPUAccessFlags = 0;
    DSBufferDesc.MiscFlags = 0;

    SecureZeroMemory(&DSDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
    DSDesc.DepthEnable = true;
    DSDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    DSDesc.DepthFunc = D3D11_COMPARISON_LESS;

    SecureZeroMemory(&DSVDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
    DSVDesc.Format = DXGI_FORMAT_D32_FLOAT;
    DSVDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    DSVDesc.Texture2D.MipSlice = 0;
}

void DepthStencil::Make(ID3D11Device* Device)
{
    Device->CreateTexture2D(&DSBufferDesc, NULL, DSBuffer.GetAddressOf());
    Device->CreateDepthStencilState(&DSDesc, DSState.GetAddressOf());
    Device->CreateDepthStencilView(DSBuffer.Get(),
        &DSVDesc,
        DSView.GetAddressOf()
    );  
}

void DepthStencil::Bind(ID3D11DeviceContext* DeviceContext)
{
    DeviceContext->OMSetDepthStencilState(DSState.Get(), 1);
}
