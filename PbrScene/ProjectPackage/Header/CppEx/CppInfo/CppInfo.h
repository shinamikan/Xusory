#pragma once

#include <iostream>

// compilers and platforms macros
#if defined(__clang__) || defined(__GNUC__)
#define CPP_STANDARD __cplusplus
#elif defined(_MSC_VER)
#define CPP_STANDARD _MSVC_LANG
#endif

constexpr uint32_t WINDOWS_ID = 0;
constexpr uint32_t LINUX_ID = 1;
constexpr uint32_t APPLE_MAC_ID = 2;

#if defined(__WINDOWS__) || defined(_WIN32) || defined(WIN32) || defined(_WIN64) || \
    defined(WIN64) || defined(__WIN32__) || defined(__TOS_WIN__)
#define NATIVE_OS WINDOWS_ID
#elif defined(__linux__) || defined(linux) || defined(__linux) || defined(__LINUX__) || \
	defined(LINUX) || defined(_LINUX)
#define NATIVE_OS LINUX_ID
#elif defined(__MACOSX) || defined(__MACOS_CLASSIC__) || defined(__APPLE__) || defined(__apple__)
#define NATIVE_OS APPLE_MAC_ID
#endif
