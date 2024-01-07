#pragma once

#include "FileCom.h"
#include "../Time/TimeCom.h"

namespace XusoryEngine::Platform
{
	DLL_CLASS(File)
	{
	public:
		File() = default;
		File(const std::wstring_view& path, OPEN_MODE openMode);
		DEFAULT_COPY_OPERATOR(File);
		~File();

		void Open(const std::wstring_view& path, OPEN_MODE openMode);
		void Close() const;
		void Read(void* pData) const;
		void ReadText(std::string& pStr) const;
		void Write(const void* data, SIZE_T size) const;

		static INT64 GetSize(const std::wstring_view& path);
		static CompleteTime GetTime(const std::wstring_view& path, FILE_TIME_INFO timeInfo);
		static void SetTime(const std::wstring_view& path, const CompleteTime & CompTime, FILE_TIME_INFO timeInfo);

		static void Copy(const std::wstring_view& srcPath, const std::wstring_view& dstPath);
		static void Create(const std::wstring_view& path);
		static void Delete(const std::wstring_view& path);
		static void Move(const std::wstring_view & srcPath, const std::wstring_view & dstPath);

		static BOOL ExistFile(const std::wstring_view& path);
		static void ThrowIfFileExist(const std::wstring_view& path);
		static void TryToFindFile(const std::wstring_view& path);

	private:
		void ReadData(void* pData, DWORD dataSize) const;

		HANDLE		m_fileHandle = nullptr;
		OPEN_MODE	m_openMode;
	};
}
