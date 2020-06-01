#pragma once

#include "teal/core/KeyCode.h"
#include <Windows.h>

static int ConvCode(int code)
{
	switch (code)
	{
	case VK_BACK: return TL_KB_BACKSPACE;
	case VK_TAB: return TL_KB_TAB;
	case VK_RETURN: return TL_KB_ENTER;
	case VK_PAUSE: return TL_KB_PAUSE;
	case VK_CAPITAL: return TL_KB_CAPS_LOCK;
	case VK_ESCAPE: return TL_KB_ESCAPE;
	case VK_SPACE: return TL_KB_SPACE;
	case VK_PRIOR: return TL_KB_PAGE_UP;
	case VK_NEXT: return TL_KB_PAGE_DOWN;
	case VK_END: return TL_KB_END;
	case VK_HOME: return TL_KB_HOME;
	case VK_LEFT: return TL_KB_LEFT;
	case VK_UP: return TL_KB_UP;
	case VK_RIGHT: return TL_KB_RIGHT;
	case VK_DOWN: return TL_KB_DOWN;
	case VK_SNAPSHOT: return TL_KB_PRINT_SCREEN;
	case VK_INSERT: return TL_KB_INSERT;
	case VK_DELETE: return TL_KB_DELETE;
	case 0x30: return TL_KB_0;
	case 0x31: return TL_KB_1;
	case 0x32: return TL_KB_2;
	case 0x33: return TL_KB_3;
	case 0x34: return TL_KB_4;
	case 0x35: return TL_KB_5;
	case 0x36: return TL_KB_6;
	case 0x37: return TL_KB_7;
	case 0x38: return TL_KB_8;
	case 0x39: return TL_KB_9;
	case 0x41: return TL_KB_A;
	case 0x42: return TL_KB_B;
	case 0x43: return TL_KB_C;
	case 0x44: return TL_KB_D;
	case 0x45: return TL_KB_E;
	case 0x46: return TL_KB_F;
	case 0x47: return TL_KB_G;
	case 0x48: return TL_KB_H;
	case 0x49: return TL_KB_I;
	case 0x4A: return TL_KB_J;
	case 0x4B: return TL_KB_K;
	case 0x4C: return TL_KB_L;
	case 0x4D: return TL_KB_M;
	case 0x4E: return TL_KB_N;
	case 0x4F: return TL_KB_O;
	case 0x50: return TL_KB_P;
	case 0x51: return TL_KB_Q;
	case 0x52: return TL_KB_R;
	case 0x53: return TL_KB_S;
	case 0x54: return TL_KB_T;
	case 0x55: return TL_KB_U;
	case 0x56: return TL_KB_V;
	case 0x57: return TL_KB_W;
	case 0x58: return TL_KB_X;
	case 0x59: return TL_KB_Y;
	case 0x5A: return TL_KB_Z;
	case VK_LWIN: return TL_KB_LEFT_SUPER;
	case VK_RWIN: return TL_KB_RIGHT_SUPER;
	case VK_APPS: return TL_KB_MENU;
	/*
	TODO NUMPAD
	VK_NUMPAD0
	VK_NUMPAD1
	VK_NUMPAD2
	VK_NUMPAD3
	VK_NUMPAD4
	VK_NUMPAD5
	VK_NUMPAD6
	VK_NUMPAD7
	VK_NUMPAD8
	VK_NUMPAD9
	VK_MULTIPLY
	VK_ADD
	VK_SEPARATOR
	VK_SUBTRACT
	VK_DECIMAL
	VK_DIVIDE
	*/
	case VK_F1: return TL_KB_F1;
	case VK_F2: return TL_KB_F2;
	case VK_F3: return TL_KB_F3;
	case VK_F4: return TL_KB_F4;
	case VK_F5: return TL_KB_F5;
	case VK_F6: return TL_KB_F6;
	case VK_F7: return TL_KB_F7;
	case VK_F8: return TL_KB_F8;
	case VK_F9: return TL_KB_F9;
	case VK_F10: return TL_KB_F10;
	case VK_F11: return TL_KB_F11;
	case VK_F12: return TL_KB_F12;
	case VK_F13: return TL_KB_F13;
	case VK_F14: return TL_KB_F14;
	case VK_F15: return TL_KB_F15;
	case VK_F16: return TL_KB_F16;
	case VK_F17: return TL_KB_F17;
	case VK_F18: return TL_KB_F18;
	case VK_F19: return TL_KB_F19;
	case VK_F20: return TL_KB_F20;
	case VK_F21: return TL_KB_F21;
	case VK_F22: return TL_KB_F22;
	case VK_F23: return TL_KB_F23;
	case VK_F24: return TL_KB_F24;
	case VK_NUMLOCK: return TL_KB_NUM_LOCK;
	case VK_SCROLL: return TL_KB_SCROLL_LOCK;
	case VK_LSHIFT: return TL_KB_LEFT_SHIFT;
	case VK_RSHIFT: return TL_KB_RIGHT_SHIFT;
	case VK_SHIFT: return TL_KB_LEFT_SHIFT;
	case VK_LCONTROL: return TL_KB_LEFT_CONTROL;
	case VK_RCONTROL: return TL_KB_RIGHT_CONTROL;
	case VK_CONTROL: return TL_KB_LEFT_CONTROL;
	case VK_LMENU: return TL_KB_LEFT_ALT;
	case VK_RMENU: return TL_KB_RIGHT_ALT;
	case VK_MENU: return TL_KB_LEFT_ALT;
	case VK_OEM_1: return TL_KB_SEMICOLON;
	case VK_OEM_PLUS: return TL_KB_EQUAL;
	case VK_OEM_COMMA: return TL_KB_COMMA;
	case VK_OEM_MINUS: return TL_KB_MINUS;
	case VK_OEM_PERIOD: return TL_KB_PERIOD;
	case VK_OEM_2: return TL_KB_SLASH;
	case VK_OEM_3: return TL_KB_GRAVE_ACCENT;
	case VK_OEM_4: return TL_KB_LEFT_BRACKET;
	case VK_OEM_5: return TL_KB_BACKSLASH;
	case VK_OEM_6: return TL_KB_RIGHT_BRACKET;
	case VK_OEM_7: return TL_KB_APOSTROPHE;
	default: return TK_KB_UNKNOWN;
	}
}