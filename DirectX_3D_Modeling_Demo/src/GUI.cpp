#include "GUI.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"


void GUI::Init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsLight();
}

void GUI::InitWin32(HWND hwnd)
{
	ImGui_ImplWin32_Init(hwnd);
}

void GUI::InitDX11(ID3D11Device* device, ID3D11DeviceContext* context) {
	ImGui_ImplDX11_Init(device, context);
}

void GUI::Close()
{
	ImGui::DestroyContext();
}

void GUI::NewFrame()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void GUI::Render()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
