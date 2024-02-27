#include "../File.h"
#include "../Common/FileDefine.h"
#include "../../Time/Time.h"

namespace XusoryEngine
{
	using FileTime = FILETIME;

	template <typename... Args>
	void ThrowIfOpenModeError(HANDLE handle, FileOpenMode mode, Args... args)
	{
		ThrowIfObjectNotCreated(handle, "file");

		if (!((mode == args ||  mode == static_cast<FileOpenMode>(static_cast<DWORD>(args) + 1)) || ...))
		{
			ThrowWithErrName(LogicError, "Open mode does not current");
		}
	}

	File::File(const std::wstring_view& path, FileOpenMode openMode)
	{
		Open(path, openMode);
	}

	File::~File()
	{
		Close();
	}

	void File::Open(const std::wstring_view& path, FileOpenMode openMode)
	{
		UINT dwDisposition = NULL;

		switch (openMode)
		{
		case FileOpenMode::UNKNOWN:
		case FileOpenMode::READ:
		case FileOpenMode::APPEND:
			TryToFindFile(path);
			dwDisposition = OPEN_EXISTING;
			break;
		case FileOpenMode::WRITE:
			TryToFindFile(path);
			dwDisposition = CREATE_ALWAYS;
			break;
		case FileOpenMode::READ_ADD:
		case FileOpenMode::WRITE_ADD:
		case FileOpenMode::APPEND_ADD:
			dwDisposition = OPEN_ALWAYS;
			break;
		}

		m_openMode = openMode;
		m_fileHandle = CreateFile(path.data(), static_cast<DWORD>(openMode), NULL, nullptr,
			dwDisposition, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (m_fileHandle == INVALID_HANDLE_VALUE)
		{
			ThrowWithErrName(RuntimeError, WinFailedInfo("open file"));
		}
	}

	void File::Close() const
	{
		if (m_fileHandle)
		{
			CloseHandle(m_fileHandle);
		}
	}

	void File::Read(void* pData) const
	{
		ThrowIfOpenModeError(m_fileHandle, m_openMode, FileOpenMode::READ, FileOpenMode::READ_ADD);

		const DWORD fileSize = GetFileSize(m_fileHandle, nullptr);
		ThrowIfWinFuncFailed(ReadFile(m_fileHandle, pData, fileSize, nullptr, nullptr), "read file");
	}

	void File::ReadText(std::string& str) const
	{
		ThrowIfOpenModeError(m_fileHandle, m_openMode, FileOpenMode::READ, FileOpenMode::READ_ADD);

		const DWORD fileSize = GetFileSize(m_fileHandle, nullptr);
		str.resize(fileSize, 0);

		ThrowIfWinFuncFailed(ReadFile(m_fileHandle, str.data(), fileSize, nullptr, nullptr), "read file");
	}

	void File::Write(const void* data, SIZE_T size) const
	{
		ThrowIfOpenModeError(m_fileHandle, m_openMode, FileOpenMode::WRITE, FileOpenMode::APPEND);

		DWORD writtenBytes;
		const std::string str(static_cast<const char*>(data), size);
		const auto strBytes = static_cast<DWORD>(str.size());

		const BOOL result = WriteFile(m_fileHandle, str.data(), strBytes, &writtenBytes, nullptr);
		ThrowIfWinFuncFailed(result, "write file");
	}

	INT64 File::GetSize(const std::wstring_view& path)
	{
		TryToFindFile(path);

		File fileTemp;
		fileTemp.Open(path, FileOpenMode::UNKNOWN);

		LARGE_INTEGER large;
		ThrowIfWinFuncFailed(GetFileSizeEx(fileTemp.m_fileHandle, &large), "get file size");

		return large.QuadPart;
	}

	CompleteTime File::GetTime(const std::wstring_view& path, FileTimeInfo timeInfo)
	{
		TryToFindFile(path);

		File fileTemp;
		fileTemp.Open(path, FileOpenMode::UNKNOWN);

		BY_HANDLE_FILE_INFORMATION info;
		GetFileInformationByHandle(fileTemp.m_fileHandle, &info);

		BOOL result = false;
		FileTime fileTime;
		switch (timeInfo)
		{
		case FileTimeInfo::CREATION_TIME:
			result = GetFileTime(fileTemp.m_fileHandle, &fileTime, nullptr, nullptr);
			break;
		case FileTimeInfo::LAST_ACCESS_TIME:
			result = GetFileTime(fileTemp.m_fileHandle, nullptr, &fileTime, nullptr);
			break;
		case FileTimeInfo::LAST_WRITE_TIME:
			result = GetFileTime(fileTemp.m_fileHandle, nullptr, nullptr, &fileTime);
			break;
		}

		ThrowIfWinFuncFailed(result, "get file time");

		const auto compTime = Time::FileTimeToCompTime(fileTime, true);
		return compTime;
	}

	void File::SetTime(const std::wstring_view& path, const CompleteTime& CompTime, FileTimeInfo timeInfo)
	{
		TryToFindFile(path);

		const HANDLE handle = CreateFile(path.data(), GENERIC_WRITE, NULL, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		const FileTime fileTime = Time::CompTimeToFileTime(CompTime, true);

		BOOL result = false;
		switch (timeInfo)
		{
		case FileTimeInfo::CREATION_TIME:
			result = SetFileTime(handle, &fileTime, nullptr, nullptr);
			break;
		case FileTimeInfo::LAST_ACCESS_TIME:
			result = SetFileTime(handle, nullptr, &fileTime, nullptr);
			break;
		case FileTimeInfo::LAST_WRITE_TIME:
			result = SetFileTime(handle, nullptr, nullptr, &fileTime);
			break;
		}

		ThrowIfWinFuncFailed(result, "get file time");
	}

	void File::Copy(const std::wstring_view& srcPath, const std::wstring_view& dstPath)
	{
		TryToFindFile(srcPath);
		ThrowIfFileExist(dstPath);

		ThrowIfWinFuncFailed(CopyFile(srcPath.data(), dstPath.data(), true), "copy file");
	}

	void File::Create(const std::wstring_view& path)
	{
		ThrowIfFileExist(path);

		const auto handle = CreateFile(path.data(), static_cast<DWORD>(FileOpenMode::UNKNOWN), NULL, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (!handle)
		{
			ThrowWithErrName(RuntimeError, WinFailedInfo("create file"));
		}

		CloseHandle(handle);
	}

	void File::Delete(const std::wstring_view& path)
	{
		TryToFindFile(path);
		ThrowIfWinFuncFailed(DeleteFile(path.data()), "delete file");
	}

	void File::Move(const std::wstring_view& srcPath, const std::wstring_view& dstPath)
	{
		TryToFindFile(srcPath);
		ThrowIfFileExist(dstPath);

		ThrowIfWinFuncFailed(MoveFile(srcPath.data(), dstPath.data()), "move file");
	}

	BOOL File::ExistFile(const std::wstring_view& path)
	{
		const DWORD dwAttribute = GetFileAttributes(path.data());
		return dwAttribute != INVALID_FILE_ATTRIBUTES && !(dwAttribute & FILE_ATTRIBUTE_DIRECTORY);
	}

	void File::ThrowIfFileExist(const std::wstring_view& path)
	{
		if (ExistFile(path))
		{
			ThrowWithErrName(PathExistError, GetPathErrorCompInfo(PATH_EXIST_ERROR_INFO, path));
		}
	}

	void File::TryToFindFile(const std::wstring_view& path)
	{
		const DWORD dwAttribute = GetFileAttributes(path.data());
		if (dwAttribute == INVALID_FILE_ATTRIBUTES)
		{
			ThrowWithErrName(PathNotFoundError, GetPathErrorCompInfo(NO_SUCH_PATH_ERROR_INFO, path));
		}
		if (dwAttribute & FILE_ATTRIBUTE_DIRECTORY)
		{
			ThrowWithErrName(PathError, GetPathErrorCompInfo("Requesting file operations on the directory", path));
		}
	}
}
