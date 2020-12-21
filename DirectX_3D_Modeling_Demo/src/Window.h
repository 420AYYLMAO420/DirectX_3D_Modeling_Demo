#pragma once
#include "Demo_Windows.h"
#include <memory>

class Window {
public:
	Window(const wchar_t* title, unsigned int width, unsigned int height);
	Window(const Window&) = delete;
	Window& operator=(const Window& ()) = delete;
	~Window();

	BOOL HandleMSG();
	const MSG* GetCurrentMSG() const { return &Message; }
	const HWND GetHWND() const { return WinHandle; }
	const UINT GetMouseX() const { return MouseX; }
	const UINT GetMouseY() const { return MouseY; }
	const UINT GetOffsetX() const { return OffsetX; }
	const UINT GetOffsetY() const { return OffsetY; }
	const UINT GetWidth() const { return Width; }
	const UINT GetHeight() const { return Height; }
	const UINT GetKeyPressed() const { return KeyPressed; }
private:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
private:
	UINT Width;
	UINT Height;

	float MouseX;
	float MouseY;
	float OffsetX;
	float OffsetY;
	UINT KeyPressed;

	HWND WinHandle;
	WNDCLASSEX WinClass;
	const wchar_t* ClassName;
	MSG Message;
};