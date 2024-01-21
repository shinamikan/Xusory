#include "../Directory.h"
#include "../File.h"
#include "../Common/FileDefine.h"

namespace XusoryEngine
{
	void Directory::Copy(const std::wstring_view& srcPath, const std::wstring_view& dstPath, BOOL skipFindDir)
	{
		if (!skipFindDir)
		{
			TryToFindDir(srcPath);
			ThrowIfDirExist(dstPath);
		}

		Create(dstPath);
		if (!IsEmpty(srcPath))
		{
			const auto fileList = ListFiles(srcPath);
			for (const auto& fileName : fileList)
			{
				std::wstring nextSrcPath = std::wstring(srcPath) + TEXT("/") + fileName;
				std::wstring nextDstPath = std::wstring(dstPath) + TEXT("/") + fileName;

				if (ExistDir(nextSrcPath))
				{
					Copy(nextSrcPath, nextDstPath, true);
				}
				else
				{
					File::Copy(nextSrcPath, nextDstPath);
				}
			}
		}
	}

	void Directory::Create(const std::wstring_view& path)
	{
		ThrowIfDirExist(path);
		ThrowIfWinFuncFailed(CreateDirectory(path.data(), nullptr), "create directory");
	}

	void Directory::Delete(const std::wstring_view& path, BOOL skipFindDir)
	{
		if (!skipFindDir)
		{
			TryToFindDir(path);
		}

		if (!IsEmpty(path))
		{
			const auto fileList = ListFiles(path);
			for (const auto& fileName : fileList)
			{
				std::wstring nextPath = std::wstring(path) + TEXT("/") + fileName;
				if (ExistDir(nextPath))
				{
					Delete(nextPath, true);
				}
				else
				{
					File::Delete(nextPath);
				}
			}
		}

		ThrowIfWinFuncFailed(RemoveDirectory(path.data()), "delete directory");
	}

	void Directory::Move(const std::wstring_view& srcPath, const std::wstring_view& dstPath)
	{
		TryToFindDir(srcPath);
		ThrowIfDirExist(dstPath);

		ThrowIfWinFuncFailed(MoveFile(srcPath.data(), dstPath.data()), "move directory");
	}

	BOOL Directory::ExistDir(const std::wstring_view& path)
	{
		const DWORD dwAttribute = GetFileAttributes(path.data());
		return dwAttribute != INVALID_FILE_ATTRIBUTES && dwAttribute & FILE_ATTRIBUTE_DIRECTORY;
	}

	BOOL Directory::IsEmpty(const std::wstring_view& path)
	{
		TryToFindDir(path);

		const auto pathTemp = StringEx::Format<std::wstring>(TEXT("%s/%s"), path.data(), TEXT("*.*"));

		WIN32_FIND_DATA findDataFirst;
		WIN32_FIND_DATA findDataSecond;
		const HANDLE handle = FindFirstFile(pathTemp.data(), &findDataFirst);
		FindNextFile(handle, &findDataSecond);

		WIN32_FIND_DATA findData;
		const BOOL ifFound = FindNextFile(handle, &findData);
		FindClose(handle);

		return !ifFound;
	}

	void Directory::ThrowIfDirExist(const std::wstring_view& path)
	{
		if (ExistDir(path))
		{
			ThrowWithErrName(PathExistError, GetPathErrorCompInfo(PATH_EXIST_ERROR_INFO, path));
		}
	}

	void Directory::TryToFindDir(const std::wstring_view& path)
	{
		const DWORD dwAttribute = GetFileAttributes(path.data());
		if (dwAttribute == INVALID_FILE_ATTRIBUTES)
		{
			ThrowWithErrName(PathNotFoundError, GetPathErrorCompInfo(NO_SUCH_PATH_ERROR_INFO, path));
		}
		if (!(dwAttribute & FILE_ATTRIBUTE_DIRECTORY))
		{
			ThrowWithErrName(PathError, GetPathErrorCompInfo("Requesting directory operations on the file", path));
		}
	}

	FILE_NOTIFY_INFORMATION Directory::MonitorDirChanges(const std::wstring_view& path)
	{
		TryToFindDir(path);

		const HANDLE dirHandle = CreateFile(path.data(), FILE_LIST_DIRECTORY, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr, OPEN_EXISTING,
			FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, nullptr);

		constexpr DWORD bufSize = 1024;
		BYTE buffer[bufSize];
		DWORD bytesReturned = 0;

		const BOOL result = ReadDirectoryChangesW(dirHandle, buffer, bufSize, true,
			FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_ATTRIBUTES | FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_LAST_WRITE,
			&bytesReturned, nullptr, nullptr);
		ThrowIfWinFuncFailed(result, "monitor dir changes");

		CloseHandle(dirHandle);
		return *reinterpret_cast<FILE_NOTIFY_INFORMATION*>(buffer);
	}

	std::vector<std::wstring> Directory::ListFiles(const std::wstring_view& path, const std::wstring_view& fileType)
	{
		TryToFindDir(path);

		const auto pathTemp = StringEx::Format<std::wstring>(TEXT("%s/%s"), path.data(), fileType.data());
		std::vector<std::wstring> fileList;

		WIN32_FIND_DATA findDataFirst;
		const HANDLE handle = FindFirstFile(pathTemp.data(), &findDataFirst);
		if (StringEx::EndWith<std::wstring>(fileType, TEXT('*')))
		{
			WIN32_FIND_DATA findDataSecond;
			FindNextFile(handle, &findDataSecond);
		}
		else
		{
			fileList.emplace_back(findDataFirst.cFileName);
		}

		WIN32_FIND_DATA findData;
		while (FindNextFile(handle, &findData))
		{
			fileList.emplace_back(findData.cFileName);
		}
		FindClose(handle);

		return fileList;
	}
}
