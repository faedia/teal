#pragma once

#ifdef TL_WINDOWS
#ifdef TL_DLL
#define TL_API __declspec( dllexport )
#else
#define TL_API __declspec( dllexport )
#endif // TL_DLL
#endif // TL_WINDOWS
