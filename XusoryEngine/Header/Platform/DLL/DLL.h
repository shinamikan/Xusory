#pragma once

#include <iostream>
#include <Windows.h>

namespace XusoryEngine::Platform
{
	class DLL
	{
	public:
		DLL() = default;
		DLL(const std::wstring_view& path);

		void LoadDLL(const std::wstring_view& path);
		template <typename FuncT>
		FuncT* GetFuncFromDLL(const std::string_view& funcName);

	private:
		HINSTANCE m_dllHandle;
	};

	template<typename FuncT>
	FuncT* DLL::GetFuncFromDLL(const std::string_view& funcName)
	{
		return reinterpret_cast<FuncT*>(GetProcAddress(m_dllHandle, funcName.data()));
	}
}
