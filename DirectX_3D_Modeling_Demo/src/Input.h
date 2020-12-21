#pragma once

#include "Demo_Windows.h"

class Input {
public:
	Input();
	const UINT& GetMouseX() const { return MouseX; }
	void SetMouseX(const UINT& x) { MouseX = x; }
	const UINT& GetMouseY() const { return MouseY; }
	void SetMouseY(const UINT& y) { MouseY = y; }
private:
	UINT MouseX;
	UINT MouseY;

};