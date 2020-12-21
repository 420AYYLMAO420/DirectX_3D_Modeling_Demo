#pragma once

#include <d3d11.h>
#include <wrl.h>
#include <memory>
#include <unordered_map>

class Graphics {
public:
	Graphics(HWND hwnd, unsigned int width, unsigned int height);
	//Do not copy graphics object
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics& ()) = delete;
	~Graphics();

	void Render(const UINT key, float x, float y);

private:
	template<class T>
	T* GetResource(const char* name) const;
private:
	std::unordered_map<const char*, std::shared_ptr<class Resource>> Resources;
	std::unique_ptr<class GraphicsCard> GPU;
	std::unique_ptr<class Time> Timer;
	std::unique_ptr<class Camera> CameraObject;
	UINT Width;
	UINT Height;
};


