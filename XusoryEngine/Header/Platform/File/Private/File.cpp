#include "../File.h"
#include "../../Time/Time.h"

namespace NovaEngine::Platform
{
	inline void ThrowIfHandleNull(HANDLE handle)
	{
		if (!handle)
		{
			ThrowWithErrName(FileNotOpenedError, "File handle is null");
		}
	}

	template <typename... Args>
	void ThrowIfOpenModeError(OPEN_MODE mode, Args... args)
	{
		if (!((mode == args || mode == args + 1) || ...))
		{
			ThrowWithErrName(OpenModeError, "Open mode does not current");
		}
	}

	File::File(const std::wstring_view& path, OPEN_MODE openMode)
	{
		Open(path, openMode);
	}

	File::~File()
	{
		Close();
	}

	void File::Open(const std::wstring_view& path, OPEN_MODE openMode)
	{
		UINT dwDisposition = NULL;

		switch (openMode)
		{
		case OPEN_MODE_NULL:
		case OPEN_MODE_READ:
		case OPEN_MODE_APPEND:
			TryToFindFile(path);
			dwDisposition = OPEN_EXISTING;
			break;
		case OPEN_MODE_WRITE:
			TryToFindFile(path);
			dwDisposition = CREATE_ALWAYS;
			break;
		case OPEN_MODE_READ_ADD:
		case OPEN_MODE_WRITE_ADD:
		case OPEN_MODE_APPEND_ADD:
			dwDisposition = OPEN_ALWAYS;
			break;
		}

		m_openMode = openMode;
		m_fileHandle = CreateFile(path.data(), openMode, NULL, nullptr,
			dwDisposition, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (m_fileHandle == INVALID_HANDLE_VALUE)
		{
			ThrowWithErrName(FileOperationError, WinFailedInfo("open file"));
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
		ThrowIfHandleNull(m_fileHandle);
		ThrowIfOpenModeError(m_openMode, OPEN_MODE_READ, OPEN_MODE_READ_ADD);

		const DWORD fileSize = GetFileSize(m_fileHandle, nullptr);
		ReadData(pData, fileSize);
	}

	void File::ReadText(std::string& pStr) const
	{
		ThrowIfHandleNull(m_fileHandle);
		ThrowIfOpenModeError(m_openMode, OPEN_MODE_READ);

		const DWORD fileSize = GetFileSize(m_fileHandle, nullptr);
		pStr.resize(fileSize, 0);

		ReadData(pStr.data(), fileSize);
	}

	void File::Write(const void* data, SIZE_T size) const
	{
		ThrowIfHandleNull(m_fileHandle);
		ThrowIfOpenModeError(m_openMode, OPEN_MODE_WRITE, OPEN_MODE_APPEND);

		DWORD writtenBytes;
		const std::string str(static_cast<const char*>(data), size);
		const auto strBytes = static_cast<DWORD>(str.size());

		if (!WriteFile(m_fileHandle, str.data(), strBytes, &writtenBytes, nullptr))
		{
			ThrowWithErrName(FileOperationError, WinFailedInfo("write file"));
		}
	}

	INT64 File::GetSize(const std::wstring_view& path)
	{
		TryToFindFile(path);

		File fileTemp;
		fileTemp.Open(path, OPEN_MODE_NULL);

		LARGE_INTEGER large;
		GetFileSizeEx(fileTemp.m_fileHandle, &large);

		return large.QuadPart;
	}

	CompleteTime File::GetTime(const std::wstring_view& path, FILE_TIME_INFO timeInfo)
	{
		TryToFindFile(path);

		File fileTemp;
		fileTemp.Open(path, OPEN_MODE_NULL);

		BY_HANDLE_FILE_INFORMATION info;
		GetFileInformationByHandle(fileTemp.m_fileHandle, &info);

		FILETIME fileTime;
		BOOL result = false;
		switch (timeInfo)
		{
		case FILE_CREATION_TIME:
			result = GetFileTime(fileTemp.m_fileHandle, &fileTime, nullptr, nullptr);
			break;
		case FILE_LAST_ACCESS_TIME:
			result = GetFileTime(fileTemp.m_fileHandle, nullptr, &fileTime, nullptr);
			break;
		case FILE_LAST_WRITE_TIME:
			result = GetFileTime(fileTemp.m_fileHandle, nullptr, nullptr, &fileTime);
			break;
		}

		if (!result)
		{
			ThrowWithErrName(FileOperationError, WinFailedInfo("get file time"));
		}

		const auto compTime = Time::FileTimeToCompTime(fileTime, true);
		return compTime;
	}

	void File::SetTime(const std::wstring_view& path, const CompleteTime& CompTime, FILE_TIME_INFO timeInfo)
	{
		TryToFindFile(path);

		const HANDLE handle = CreateFile(path.data(), GENERIC_WRITE, NULL, nullptr,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		const FILETIME fileTime = Time::CompTimeToFileTime(CompTime, true);

		BOOL result = false;
		switch (timeInfo)
		{
		case FILE_CREATION_TIME:
			result = SetFileTime(handle, &fileTime, nullptr, nullptr);
			break;
		case FILE_LAST_ACCESS_TIME:
			result = SetFileTime(handle, nullptr, &fileTime, nullptr);
			break;
		case FILE_LAST_WRITE_TIME:
			result = SetFileTime(handle, nullptr, nullptr, &fileTime);
			break;
		}

		if (!result)
		{
			ThrowWithErrName(FileOperationError, WinFailedInfo("set file time"));
		}
	}

	void File::Copy(const std::wstring_view& srcPath, const std::wstring_view& dstPath)
	{
		TryToFindFile(srcPath);
		ThrowIfFileExist(dstPath);

		if (!CopyFile(srcPath.data(), dstPath.data(), true))
		{
			ThrowWithErrName(FileOperationError, WinFailedInfo("copy file"));
		}
	}

	void File::Create(const std::wstring_view& path)
	{
		ThrowIfFileExist(path);
		if (!CreateFile(path.data(), OPEN_MODE_NULL, NULL, nullptr,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr))
		{
			ThrowWithErrName(FileOperationError, WinFailedInfo("create file"));
		}
	}

	void File::Delete(const std::wstring_view& path)
	{
		TryToFindFile(path);
		if (!DeleteFile(path.data()))
		{
			ThrowWithErrName(FileOperationError, WinFailedInfo("delete file"));
		}
	}

	void File::Move(const std::wstring_view& srcPath, const std::wstring_view& dstPath)
	{
		TryToFindFile(srcPath);
		ThrowIfFileExist(dstPath);

		if (!MoveFile(srcPath.data(), dstPath.data()))
		{
			ThrowWithErrName(FileOperationError, WinFailedInfo("move file"));
		}
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

	void File::ReadData(void* pData, DWORD dataSize) const
	{
		const DWORD fileSize = GetFileSize(m_fileHandle, nullptr);

		if (fileSize == INVALID_FILE_SIZE || !ReadFile(m_fileHandle, pData, dataSize, nullptr, nullptr))
		{
			ThrowWithErrName(FileOperationError, WinFailedInfo("read file"));
		}
	}
	
}