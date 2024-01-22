#pragma once

#include "../Common/PlatformDefine.h"

namespace XusoryEngine
{
	using CompleteTime = SYSTEMTIME;

	enum OpenMode : DWORD
	{
		OPEN_MODE_NULL = NULL,
		OPEN_MODE_READ = GENERIC_READ,
		OPEN_MODE_WRITE = GENERIC_WRITE,
		OPEN_MODE_APPEND = FILE_APPEND_DATA,
		OPEN_MODE_READ_ADD = OPEN_MODE_READ + 1,
		OPEN_MODE_WRITE_ADD = OPEN_MODE_WRITE + 1,
		OPEN_MODE_APPEND_ADD = OPEN_MODE_APPEND + 1
	};

	enum FileTimeInfo
	{
		FILE_CREATION_TIME = 0,
		FILE_LAST_ACCESS_TIME,
		FILE_LAST_WRITE_TIME
	};

	DLL_CLASS(File)
	{
	public:
		File() = default;
		File(const std::wstring_view& path, OpenMode openMode);
		DEFAULT_COPY_OPERATOR(File);
		DEFAULT_MOVE_OPERATOR(File);
		~File();

		void Open(const std::wstring_view& path, OpenMode openMode);
		void Close() const;
		void Read(void* pData) const;
		void ReadText(std::string& str) const;
		void Write(const void* data, SIZE_T size) const;

		static INT64 GetSize(const std::wstring_view& path);
		static CompleteTime GetTime(const std::wstring_view& path, FileTimeInfo timeInfo);
		static void SetTime(const std::wstring_view& path, const CompleteTime & CompTime, FileTimeInfo timeInfo);

		static void Copy(const std::wstring_view& srcPath, const std::wstring_view& dstPath);
		static void Create(const std::wstring_view& path);
		static void Delete(const std::wstring_view& path);
		static void Move(const std::wstring_view & srcPath, const std::wstring_view & dstPath);

		static BOOL ExistFile(const std::wstring_view& path);
		static void ThrowIfFileExist(const std::wstring_view& path);
		static void TryToFindFile(const std::wstring_view& path);

	private:
		HANDLE		m_fileHandle = nullptr;
		OpenMode	m_openMode;
	};
}
