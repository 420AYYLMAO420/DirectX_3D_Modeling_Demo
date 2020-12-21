#include "Demo_Windows.h"
#include "App.h"

int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	App* app = new App(L"DirectX 3D Modeling Demo", 1280, 720);
	WPARAM ExitCode;

	if(app)
		ExitCode = app->Run();

	delete app;
	return ExitCode;
}