#include "App.h"
#include "Window.h"
#include "Graphics.h"
#include "GUI.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

App::App(const wchar_t* title, unsigned int width, unsigned int height)
	:bQuit(false)
{
	GUI::Init();
	WindowObject = std::make_unique<Window>(title, width, height);
	GraphicsObject = std::make_unique<Graphics>(WindowObject->GetHWND(), width, height);
}

App::~App()
{

}

WPARAM App::Run()
{
	while (!bQuit) {
		bQuit = WindowObject->HandleMSG();
		const auto offsetx = WindowObject->GetOffsetX(), offsety = WindowObject->GetOffsetY();
		GraphicsObject->Render(WindowObject->GetKeyPressed(), offsetx, offsety);
	}

	return WindowObject->GetCurrentMSG()->wParam;
}
