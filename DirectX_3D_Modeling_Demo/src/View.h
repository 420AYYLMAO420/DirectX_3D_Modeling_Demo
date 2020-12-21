#pragma once

#include "Resource.h"
#include <memory>

class View : public Resource {
public:
	View(struct IDXGISwapChain* sc, const UINT width, const UINT height);
	void Make(ID3D11Device* device);
	void Bind(ID3D11DeviceContext* context);
	std::shared_ptr<class RenderTarget> GetRenderTarget() const { return RT; }
	std::shared_ptr<class DepthStencil> GetDepthStencil() const { return DS; }
private:
	std::shared_ptr<class RenderTarget> RT;
	std::shared_ptr<class DepthStencil> DS;
	struct D3D11_VIEWPORT Viewport;
};