#pragma once

#include "../Common/PlatformDefine.h"

namespace XusoryEngine
{
	using CompleteTime = SYSTEMTIME;

	enum class FileOpenMode : DWORD
	{
		UNKNOWN = NULL,
		READ = GENERIC_READ,
		WRITE = GENERIC_WRITE,
		APPEND = FILE_APPEND_DATA,
		READ_ADD = READ + 1,
		WRITE_ADD = WRITE + 1,
		APPEND_ADD = APPEND + 1
	};

	enum class FileTimeInfo
	{
		CREATION_TIME = 0,
		LAST_ACCESS_TIME,
		LAST_WRITE_TIME
	};

	DLL_CLASS(File)
	{
	public:
		File() = default;
		File(const std::wstring_view& path, FileOpenMode openMode);
		DEFAULT_COPY_OPERATOR(File);
		DEFAULT_MOVE_OPERATOR(File);
		~File();

		void Open(const std::wstring_view& path, FileOpenMode openMode);
		void Close() const;
		void Read(void* pData) const;
		void ReadText(std::string& str) const;
		std::string ReadText() const;
		void Write(const void* data, SIZE_T size) const;

		static INT64 GetSize(const std::wstring_view& path);
		static CompleteTime GetTime(const std::wstring_view& path, FileTimeInfo timeInfo);
		static void SetTime(const std::wstring_view& path, const CompleteTime& CompTime, FileTimeInfo timeInfo);

		static void Copy(const std::wstring_view& srcPath, const std::wstring_view& dstPath);
		static void Create(const std::wstring_view& path);
		static void Delete(const std::wstring_view& path);
		static void Move(const std::wstring_view& srcPath, const std::wstring_view& dstPath);

		static BOOL ExistFile(const std::wstring_view& path);
		static void ThrowIfFileExist(const std::wstring_view& path);
		static void TryToFindFile(const std::wstring_view& path);

	private:
		HANDLE m_fileHandle = nullptr;
		FileOpenMode m_openMode = FileOpenMode::UNKNOWN;
	};
}
