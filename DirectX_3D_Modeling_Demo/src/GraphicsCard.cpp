#include "GraphicsCard.h"
#include "Resource.h"
#include "Model.h"
#include "View.h"
#include "RenderTarget.h"
#include "DepthStencil.h"

GraphicsCard::GraphicsCard(HWND hwnd)
{
    DXGI_SWAP_CHAIN_DESC scd;
    SecureZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
    scd.BufferCount = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    scd.OutputWindow = hwnd;
    scd.SampleDesc.Count = 1;
    scd.SampleDesc.Quality = 0;
    scd.Windowed = TRUE;
    scd.Flags = NULL;

    D3D11CreateDeviceAndSwapChain(
        NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        NULL,
        NULL,
        NULL,
        D3D11_SDK_VERSION,
        &scd,
        SwapChain.GetAddressOf(),
        Device.GetAddressOf(),
        NULL,
        DeviceContext.GetAddressOf());
}

void GraphicsCard::Make(std::unordered_map<const char*, std::shared_ptr<Resource>> resources)
{
    for (std::pair<const char*, std::shared_ptr<Resource>> res : resources)
        res.second->Make(Device.Get());
}

void GraphicsCard::Make(Resource* resource)
{
    resource->Make(Device.Get());
}

void GraphicsCard::Bind(std::unordered_map<const char*, std::shared_ptr<Resource>> resources)
{
    for (std::pair<const char*, std::shared_ptr<Resource>> res : resources)
        res.second->Bind(DeviceContext.Get());
}

void GraphicsCard::Bind(std::shared_ptr<class Resource> resource)
{
    resource->Bind(DeviceContext.Get());
}

void GraphicsCard::Bind(Resource* resource)
{
    resource->Bind(DeviceContext.Get());
}

void GraphicsCard::Render(Model* model)
{
    model->Render(DeviceContext.Get());
}

void GraphicsCard::Clear(View* view, float r, float g, float b, float a)
{
    float color[] = { r,g,b,a };

    DeviceContext->ClearRenderTargetView(view->GetRenderTarget()->GetView().Get(), color);
    if(ID3D11DepthStencilView* ds = view->GetDepthStencil()->GetView().Get())
        DeviceContext->ClearDepthStencilView(ds, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);

}

void GraphicsCard::SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
{
    DeviceContext->IASetPrimitiveTopology(topology);
}

void GraphicsCard::Render(const BOOL usingIndices, const UINT numUnits)
{
    if (usingIndices)
        DeviceContext->DrawIndexed(numUnits, 0, 0);
    else
        DeviceContext->Draw(numUnits, 0);
}
    
void GraphicsCard::SwapBuffers()
{
    SwapChain->Present(0, 0);
}
