#include "Win32Window.h"

namespace Teal
{
	Win32Window::Win32Window(const std::string& name, int width, int height) : _AbsoluteX(0), _AbsoluteY(0), _MouseInWindow(false), _Width(width), _Height(height)
	{
		DWORD dwExStyle;
		DWORD dwStyle;

		_Hinstance = GetModuleHandle(NULL);
		_Wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		_Wc.lpfnWndProc = Win32Window::WindowProc;
		_Wc.cbClsExtra = 0;
		_Wc.cbWndExtra = 0;
		_Wc.hInstance = _Hinstance;
		_Wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		_Wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		_Wc.hbrBackground = NULL;
		_Wc.lpszMenuName = NULL;
		_Wc.lpszClassName = name.c_str();

		RegisterClass(&_Wc);

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
			this
		);
		TL_ASSERT(_Hwnd, "Window should be successfully created")

		_HDC = GetDC(_Hwnd);
		ShowWindow(_Hwnd, SW_SHOW);
		SetForegroundWindow(_Hwnd);
		SetFocus(_Hwnd);

		_RID[0].usUsagePage = 0x01;
		_RID[0].usUsage = 0x02;
		_RID[0].dwFlags = RIDEV_INPUTSINK;
		_RID[0].hwndTarget = _Hwnd;
		RegisterRawInputDevices(_RID, 1, sizeof(_RID[0]));
	}

	Win32Window::~Win32Window()
	{
		RegisterRawInputDevices(_RID, 1, sizeof(_RID[0]));
		ReleaseDC(_Hwnd, _HDC);
		DestroyWindow(_Hwnd);
		UnregisterClass(_Wc.lpszClassName, _Hinstance);
	}

	LRESULT CALLBACK Win32Window::WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
	{
		Win32Window* w;
		if (msg != WM_NCCREATE)
			w = (Win32Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

		switch (msg)
		{
		case WM_NCCREATE:
			w = static_cast<Win32Window*>(reinterpret_cast<CREATESTRUCT*>(lp)->lpCreateParams);
			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(w));
			DefWindowProc(hwnd, msg, wp, lp);
			break;
		case WM_SIZE:
		{
			int width = LOWORD(lp);
			int height = HIWORD(lp);
			w->_Width = width;
			w->_Height = height;
			w->_CurrentEvent = std::shared_ptr<WindowResizeEvent>(new WindowResizeEvent(width, height));
			break;
		}
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
		{
			int kc = wp;
			int rc = LOWORD(lp) - 1 + (BIT(30) & lp) ? 1 : 0;
			w->_CurrentEvent = std::shared_ptr<KeyPressedEvent>(new KeyPressedEvent(kc, rc));
			break;
		}
		case WM_SYSKEYUP:
		case WM_KEYUP:
		{
			int kc = wp;
			w->_CurrentEvent = std::shared_ptr<KeyReleasedEvent>(new KeyReleasedEvent(kc));
			break;
		}
		case WM_SETFOCUS:
			w->_MouseInWindow = true;
			break;
		case WM_KILLFOCUS:
			w->_MouseInWindow = false;
			break;
		case WM_INPUT:
		{
			if (!w->_MouseInWindow)
				break;
			UINT size = 0;
			RAWINPUT* data;
			GetRawInputData((HRAWINPUT)lp, RID_INPUT, NULL, &size, sizeof(RAWINPUTHEADER));
			data = (RAWINPUT*)malloc(size);
			GetRawInputData((HRAWINPUT)lp, RID_INPUT, data, &size, sizeof(RAWINPUTHEADER));
			if (data->header.dwType == RIM_TYPEMOUSE)
			{
				int dx, dy;
				if (data->data.mouse.usFlags & MOUSE_MOVE_ABSOLUTE)
				{
					dx = data->data.mouse.lLastX - w->_AbsoluteX;
					dy = data->data.mouse.lLastY - w->_AbsoluteY;
				}
				else
				{
					dx = data->data.mouse.lLastX;
					dy = data->data.mouse.lLastY;
				}
				if (dx != 0 || dy != 0)
				{
					w->_CurrentEvent = std::shared_ptr<MouseMovedEvent>(new MouseMovedEvent(w->_AbsoluteX + dx, w->_AbsoluteY + dy));
					w->_AbsoluteX += dx;
					w->_AbsoluteY += dy;
				}
				else
				{
					switch (data->data.mouse.usButtonFlags)
					{
					case RI_MOUSE_LEFT_BUTTON_DOWN:
					{
						w->_CurrentEvent = std::shared_ptr<MouseButtonPressedEvent>(new MouseButtonPressedEvent(0));
						break;
					}
					case RI_MOUSE_LEFT_BUTTON_UP:
					{
						w->_CurrentEvent = std::shared_ptr<MouseButtonReleasedEvent>(new MouseButtonReleasedEvent(0));
						break;
					}
					case RI_MOUSE_MIDDLE_BUTTON_DOWN:
					{
						w->_CurrentEvent = std::shared_ptr<MouseButtonPressedEvent>(new MouseButtonPressedEvent(1));
						break;
					}
					case RI_MOUSE_MIDDLE_BUTTON_UP:
					{
						w->_CurrentEvent = std::shared_ptr<MouseButtonReleasedEvent>(new MouseButtonReleasedEvent(1));
						break;
					}
					case RI_MOUSE_RIGHT_BUTTON_DOWN:
					{
						w->_CurrentEvent = std::shared_ptr<MouseButtonPressedEvent>(new MouseButtonPressedEvent(2));
						break;
					}
					case RI_MOUSE_RIGHT_BUTTON_UP:
					{
						w->_CurrentEvent = std::shared_ptr<MouseButtonReleasedEvent>(new MouseButtonReleasedEvent(2));
						break;
					}
					case RI_MOUSE_BUTTON_4_DOWN:
					{
						w->_CurrentEvent = std::shared_ptr<MouseButtonPressedEvent>(new MouseButtonPressedEvent(3));
						break;
					}
					case RI_MOUSE_BUTTON_4_UP:
					{
						w->_CurrentEvent = std::shared_ptr<MouseButtonReleasedEvent>(new MouseButtonReleasedEvent(3));
						break;
					}
					case RI_MOUSE_BUTTON_5_DOWN:
					{
						w->_CurrentEvent = std::shared_ptr<MouseButtonPressedEvent>(new MouseButtonPressedEvent(4));
						break;
					}
					case RI_MOUSE_BUTTON_5_UP:
					{
						w->_CurrentEvent = std::shared_ptr<MouseButtonReleasedEvent>(new MouseButtonReleasedEvent(4));
						break;
					}
					case RI_MOUSE_WHEEL:
					{
						w->_CurrentEvent = std::shared_ptr<MouseScrolledEvent>(new MouseScrolledEvent(0, data->data.mouse.usButtonData));
						break;
					}
					case RI_MOUSE_HWHEEL:
					{
						w->_CurrentEvent = std::shared_ptr<MouseScrolledEvent>(new MouseScrolledEvent(data->data.mouse.usButtonData, 0));
						break;
					}
					default:
						break;
					}
				}
			}
			free(data);
			break;
		}
		default:
			return DefWindowProc(hwnd, msg, wp, lp);
		}

		return TRUE;
	}
}