#pragma once

#define DLL_EXPORT

#ifdef DLL_EXPORT
#define DLL_FUNC __declspec(dllexport)
#define C_DLL_FUNC extern "C" DLL_FUNC
#else
#define DLL_FUNC __declspec(dllimport)
#define C_DLL_FUNC extern "C" DLL_FUNC
#endif
