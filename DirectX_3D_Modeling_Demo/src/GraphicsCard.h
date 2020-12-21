#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <unordered_map>
#include <memory>
#include "Demo_Windows.h"


class GraphicsCard {
public:
	GraphicsCard(HWND hwnd);
	GraphicsCard(const GraphicsCard&) = delete;
	GraphicsCard& operator=(const GraphicsCard& ()) = delete;
	void Make(std::unordered_map<const char*, std::shared_ptr<class Resource>> resources);
	void Make(class Resource* resource);
	void Bind(std::unordered_map<const char*, std::shared_ptr<class Resource>> resources);
	void Bind(std::shared_ptr<class Resource> resource);
	void Bind(class Resource* resource);
	void Render(class Model* model);
	ID3D11Device* GetDevice() const { return Device.Get(); }
	ID3D11DeviceContext* GetDeviceContext() const { return DeviceContext.Get(); }
	IDXGISwapChain* GetSwapChain() const { return SwapChain.Get(); }
	void Clear(class View* view,
		float r = 0, float g = 0, float b = 0, float a = 1);
	void SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology);
	void Render(const BOOL usingIndices, const UINT numUnits);
	void SwapBuffers();

private:
	Microsoft::WRL::ComPtr<ID3D11Device> Device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> DeviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> SwapChain;

};