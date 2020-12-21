#pragma once
#include "Demo_Windows.h"
#include <memory>

class App {
public:
	App(const wchar_t * title, unsigned int width, unsigned int height);
	~App();

	WPARAM Run();
private:
	std::unique_ptr<class Window> WindowObject;
	std::unique_ptr<class Graphics> GraphicsObject;
	BOOL bQuit;

};