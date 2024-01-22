#pragma once

//#define DLL_EXPORT

#if defined(DLL_EXPORT)
#define DLL_FUNC __declspec(dllexport)
#elif defined(DLL_IMPORT)
#define DLL_FUNC __declspec(dllimport)
#else
#define DLL_FUNC
#endif
#define C_DLL_FUNC extern "C" DLL_FUNC
