#ifdef TL_DLL
void _declspec( dllexport ) test();
#endif
#ifndef TL_DLL
void _declspec( dllimport ) test();
#endif