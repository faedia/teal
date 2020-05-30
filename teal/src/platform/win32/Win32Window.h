#pragma once

#include <string>
#include <Windows.h>

namespace Teal
{
	class Win32Window
	{
	public:
		Win32Window(const std::string& name);
		~Win32Window();

		HWND& GetHwnd() { return _Hwnd; }
		HINSTANCE& GetHinstance() { return _Hinstance; }
		HDC& GetHDC() { return _HDC; }

	private:
		HWND _Hwnd;
		HINSTANCE _Hinstance;
		HDC _HDC;
		WNDCLASS _Wc;
	};
}
