#pragma once

#include <string>
#include <Windows.h>
#include "teal/Event.h"
#include <queue>

namespace Teal
{
	class Win32Window
	{
	public:
		Win32Window(const std::string& name, int width, int height);
		~Win32Window();

		HWND& GetHwnd() { return _Hwnd; }
		HINSTANCE& GetHinstance() { return _Hinstance; }
		HDC& GetHDC() { return _HDC; }

		inline std::queue<std::shared_ptr<Event>>& GetEventQueue() { return _EventQueue; }

		inline int GetWidth() const { return _Width; }
		inline int GetHeight() const { return _Height; }

	private:
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

		std::queue<std::shared_ptr<Event>> _EventQueue;

		HWND _Hwnd;
		HINSTANCE _Hinstance;
		HDC _HDC;
		WNDCLASS _Wc;
		RAWINPUTDEVICE _RID[1];

		int _AbsoluteX, _AbsoluteY;
		bool _MouseInWindow;

		int _Width, _Height;
	};
}
