#pragma once

#ifdef NO_DSHOWWRAPPER_EXPORTS
#define DSHOWWRAPPER_API
#else
#ifdef DSHOWWRAPPER_EXPORTS
#define DSHOWWRAPPER_API __declspec(dllexport)
#else
#define DSHOWWRAPPER_API __declspec(dllimport)
#endif // DSHOWWRAPPER_EXPORTS
#endif // NO_DSHOWWRAPPER_EXPORTS

#ifndef _WIN32
#ifndef __cdecl
#ifdef cdecl
#define __cdecl __attribute__((cdecl))
#else
#define __cdecl
#endif // cdecl
#endif // !__cdecl
#endif // _WIN32
