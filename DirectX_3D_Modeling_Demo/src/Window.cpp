#include "Window.h"
#include "GUI.h"
#include "ico_res.h"

#include "imgui/imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
		return true;
	switch (uMsg) {
	case WM_CLOSE:
		PostQuitMessage(1);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

Window::Window(const wchar_t* title, unsigned int width, unsigned int height)
	:WinHandle(nullptr), Width(width), Height(height)
{

	ClassName = L"GenericClassName";
	SecureZeroMemory(&WinClass, sizeof(WNDCLASSEX));
	SecureZeroMemory(&Message, sizeof(MSG));
	WinClass.cbSize = sizeof(WNDCLASSEX);
	WinClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	WinClass.lpfnWndProc = WindowProc;
	WinClass.cbClsExtra = NULL;
	WinClass.cbWndExtra = NULL;
	WinClass.hInstance = GetModuleHandle(nullptr);
	WinClass.hIcon = static_cast<HICON>(LoadImage(WinClass.hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 64, 64, NULL));
	WinClass.hIconSm = static_cast<HICON>(LoadImage(WinClass.hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, NULL));
	WinClass.hCursor = nullptr;
	WinClass.hbrBackground = nullptr;
	WinClass.lpszMenuName = nullptr;
	WinClass.lpszClassName = ClassName;
	WinClass.hIconSm = nullptr;
	RegisterClassEx(&WinClass);
	RECT wr = { 0, 0, Width, Height };
	AdjustWindowRect(&wr, WS_MINIMIZEBOX | WS_CAPTION | WS_SYSMENU, FALSE);
	WinHandle = CreateWindowEx(NULL, ClassName, title,
		WS_MINIMIZEBOX | WS_CAPTION | WS_SYSMENU,
		0, 0,
		wr.right - wr.left, wr.bottom - wr.top, 
		nullptr, nullptr,
		GetModuleHandle(NULL), nullptr);
	ShowWindow(WinHandle, SW_SHOW);

	SetCursorPos(Width / 2, Height / 2);
	
	GUI::InitWin32(WinHandle);
}

Window::~Window()
{
	GUI::Close();
	UnregisterClass(ClassName, GetModuleHandle(nullptr));

}

bool firstMouse = true;
BOOL Window::HandleMSG()
{
	//check if message is in the message queue
	if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
	{
		switch (Message.message) {
		case WM_MOUSEMOVE: {
			POINT cursorPos = {};
			GetCursorPos(&cursorPos);
			ScreenToClient(WinHandle, &cursorPos);
			MouseX = cursorPos.x;
			MouseY = cursorPos.y;
			static float prevX = 0, prevY = 0;
			if (firstMouse)
			{
				prevX = MouseX;
				prevY = MouseY;
				firstMouse = false;
			}
			OffsetX = MouseX - prevX;
			OffsetY = prevY - MouseY;

			break;
		}
		case WM_KEYDOWN:
			KeyPressed = Message.wParam;
			break;
		case WM_KEYUP:
			KeyPressed = NULL;
			break;
		case WM_QUIT:
			return TRUE;
		default:
			//translate any virtual key message into WM_CHAR message
			TranslateMessage(&Message);
			//Send the message to the window procedure
			DispatchMessage(&Message);
		}
		
	}
	return FALSE;
}

