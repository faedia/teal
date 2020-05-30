#pragma once

#ifdef TL_WIN32
#ifdef TL_DLL
#define TL_API __declspec( dllexport )
#else
#define TL_API __declspec( dllimport )
#endif // TL_DLL
#endif // TL_WINDOWS

#ifndef TL_API
#define TL_API
#endif

#define BIT(x) (1<<x)

#include <string>