#pragma once

// Use the following macro to prefix or suffix an identifier

#if !defined(PREFIX_NAME) && !defined(SUFFIX_NAME)
#define PREFIX_NAME(prefix, name) prefix##name
#define SUFFIX_NAME(name, suffix) name##suffix
#endif

// Using nameof obtains a string of an identifier

#define nameof(target) #target
#define nameofT(type) typeid(type).name()

constexpr char ENTER_FUNC_MAIN[] = "main";
constexpr char ENTER_FUNC_WIN_MAIN[] = "WinMain";
