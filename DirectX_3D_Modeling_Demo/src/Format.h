#pragma once
#include <d3d11.h>
class Format {
public:
	Format() = delete;

	static DXGI_FORMAT GetFormat(const UINT numComponents) {
		DXGI_FORMAT format = DXGI_FORMAT_R32_FLOAT;

		switch (numComponents) {
		case 2:
			format = DXGI_FORMAT_R32G32_FLOAT;
			break;
		case 3:
			format = DXGI_FORMAT_R32G32B32_FLOAT;
			break;
		case 4:
			format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			break;
		}
		return format;
	}

	template<typename T>
	static UINT GetNumComponents(const UINT size) {
		return size / sizeof(T);
	}

	static UINT GetNumComponents(const DXGI_FORMAT format) {
		UINT numComponents = 0;
		switch (format) {
		case DXGI_FORMAT_B8G8R8A8_UNORM:
		case DXGI_FORMAT_R8G8B8A8_UNORM:
			numComponents = 4;
			break;
		case DXGI_FORMAT_R8_UNORM:
			numComponents = 1;
			break;
		}
		return numComponents;
	}

};