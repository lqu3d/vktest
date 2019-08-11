#include "XWindow.h"

#include<vector>	
#include<string>	
#include<assert.h>

bool XWindow::shouldClose = false; //��̬������Ҫ��ȫ�ֿռ��ʼ��

void XWindow::Init() {
	WNDCLASSEX win_class;
	assert(width > 0);
	assert(height > 0);

	/***
	*ע�⣬�����κ�һ���ֶγ������ܵ��´���ʧ�ܻ��쳣����������
	*/
	win_class.cbSize = sizeof(WNDCLASSEX);
	win_class.style = CS_HREDRAW | CS_VREDRAW;
	win_class.lpfnWndProc = wndProc;
	win_class.cbClsExtra = 0;
	win_class.cbWndExtra = 0;
	win_class.hInstance = hInst;  // hInstance
	win_class.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	win_class.hCursor = LoadCursor(NULL, IDC_ARROW);
	win_class.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	win_class.lpszMenuName = NULL;
	win_class.lpszClassName = name;
	win_class.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	// Register window class:
	if (!RegisterClassEx(&win_class)) {
		// It didn't work, so try to give a useful error:
		printf("Unexpected error trying to start the application!\n");
		fflush(stdout);
		exit(1);
	}
	// Create window with the registered class:
	RECT wr = { 0, 0, width, height };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
	hWnd = CreateWindowEx(0,
		name,             // class name
		name,             // app name
		WS_OVERLAPPEDWINDOW |  // window style
		WS_VISIBLE | WS_SYSMENU,
		0,0,            // x/y coords
		wr.right - wr.left,  // width
		wr.bottom - wr.top,  // height
		NULL,                // handle to parent
		NULL,                // handle to menu
		hInst,     // hInstance
		NULL);               // no extra parameters
	if (!hWnd) {
		// It didn't work, so try to give a useful error:
		printf("Cannot create a window in which to draw!\n");
		fflush(stdout);
		exit(1);
	}
	SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);

	shouldClose = false;
}

bool XWindow::ShouldClose() {
	if (shouldClose) {
		PostQuitMessage(0);
		return true;
	}

	return false;
}

void XWindow::PollEvents() {
	MSG msg;
	while (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK XWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	struct sample_info* info = reinterpret_cast<struct sample_info*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	switch (uMsg) {
	case WM_CLOSE:
		shouldClose = true;
		break;

	//case WM_PAINT:
		/*** ��Σ�յ����� ����������
		*ע�����return������������DefWindowProc������windows��֪������Ϣ�Ѵ�����ɣ����᲻ͣ�ļ�������WM_PAINT
		*/
		//return;
	default:
		break;
	}
	return (DefWindowProc(hWnd, uMsg, wParam, lParam));
}

