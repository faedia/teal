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

#ifdef TL_DEBUG
#define TL_DEBUG_EXCP __debugbreak()
#define TL_ASSERT(x, ...) if (!(x)) { TL_CORE_ERROR("Assert Error: {0}", __VA_ARGS__); TL_DEBUG_EXCP;}
#else
#define TL_ASSERT(x, msg)
#endif

#include "Logger.h"
#include <string>