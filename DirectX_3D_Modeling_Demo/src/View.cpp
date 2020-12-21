#include "View.h"
#include "RenderTarget.h"
#include "DepthStencil.h"

View::View(IDXGISwapChain* sc, const UINT width, const UINT height)
{
	DS = std::make_shared<DepthStencil>(width, height);
	RT = std::make_shared<RenderTarget>(sc);

	SecureZeroMemory(&Viewport, sizeof(D3D11_VIEWPORT));
	Viewport.TopLeftX = 0;
	Viewport.TopLeftY = 0;
	Viewport.Width = width;
	Viewport.Height = height;
	Viewport.MinDepth = 0.f;
	Viewport.MaxDepth = 1.f;

}

void View::Make(ID3D11Device* device)
{
	DS->Make(device);
	RT->Make(device);
}

void View::Bind(ID3D11DeviceContext* context)
{
	DS->Bind(context);
	RT->SetDepthStencilView(DS->GetView().Get());
	RT->Bind(context);
	context->RSSetViewports(1, &Viewport);
}

