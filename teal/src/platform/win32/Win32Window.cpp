#include "Win32Window.h"

namespace Teal
{
	Win32Window::Win32Window(const std::string& name)
	{
		DWORD dwExStyle;
		DWORD dwStyle;

		_Hinstance = GetModuleHandle(NULL);
		_Wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		_Wc.lpfnWndProc = DefWindowProc;
		_Wc.cbClsExtra = 0;
		_Wc.cbWndExtra = 0;
		_Wc.hInstance = _Hinstance;
		_Wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		_Wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		_Wc.hbrBackground = NULL;
		_Wc.lpszMenuName = NULL;
		_Wc.lpszClassName = name.c_str();

		if (!RegisterClass(&_Wc))
		{
			MessageBox(NULL, "Fuck", "Fuckadoo", MB_ICONERROR);
		}

		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
		_Hwnd = CreateWindowEx(
			dwExStyle,
			_Wc.lpszClassName,
			name.c_str(),
			WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle,
			0,0,
			1280, 720,
			NULL,
			NULL,
			_Hinstance,
			NULL
		);

		_HDC = GetDC(_Hwnd);
		ShowWindow(_Hwnd, SW_SHOW);
		SetForegroundWindow(_Hwnd);
		SetFocus(_Hwnd);
	}

	Win32Window::~Win32Window()
	{
		ReleaseDC(_Hwnd, _HDC);
		DestroyWindow(_Hwnd);
		UnregisterClass(_Wc.lpszClassName, _Hinstance);
	}
}