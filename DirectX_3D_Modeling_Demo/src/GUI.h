#pragma once

#include "Demo_Windows.h"

class GUI {
public:
	static void Init();
	static void InitWin32(HWND hwnd);
	static void InitDX11(struct ID3D11Device* device, struct ID3D11DeviceContext* context);
	static void Close();
	static void NewFrame();
	static void Render();
};