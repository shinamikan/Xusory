#pragma once

#include <vector>
#include "FileCom.h"

namespace XusoryEngine
{
	DLL_STATIC_CLASS(Directory)
	{
	public:
		static void Copy(const std::wstring_view& srcPath, const std::wstring_view& dstPath, BOOL skipFindDir = false);
		static void Create(const std::wstring_view& path);
		static void Delete(const std::wstring_view& path, BOOL skipFindDir = false);
		static void Move(const std::wstring_view & srcPath, const std::wstring_view & dstPath);

		static BOOL ExistDir(const std::wstring_view& path);
		static BOOL IsEmpty(const std::wstring_view& path);
		static void ThrowIfDirExist(const std::wstring_view& path);
		static void TryToFindDir(const std::wstring_view& path);

		static std::vector<std::wstring> ListFiles(const std::wstring_view & path, const std::wstring_view & fileType = TEXT("*.*"));
	};
}
