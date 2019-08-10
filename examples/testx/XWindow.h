#pragma once
#include <Windows.h>

class XWindow
{
public:
	int width = 1280;
	int height = 720;
	char name[256] = "hello";
	HINSTANCE hInst = NULL;
	HWND hWnd = NULL;

public:
	void Init();
	bool ShouldClose();
	void PollEvents();

private:
	static bool shouldClose;
	WNDPROC wndProc = WndProc;
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

