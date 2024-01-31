#pragma once

#include <iostream>
#include <Windows.h>

#include "../../CppEx/ClassEx/ClassEx.h"

namespace XusoryEngine::Platform
{
	DLL_CLASS(Dll)
	{
	public:
		Dll() = default;
		Dll(const std::wstring_view& path);

		void LoadDll(const std::wstring_view& path);
		template <typename FuncT>
		FuncT* GetFuncFromDll(const std::string_view& funcName);

	private:
		HINSTANCE m_dllHandle;
	};

	template<typename FuncT>
	FuncT* Dll::GetFuncFromDll(const std::string_view& funcName)
	{
		return reinterpret_cast<FuncT*>(GetProcAddress(m_dllHandle, funcName.data()));
	}
}
