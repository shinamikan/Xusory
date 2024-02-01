#include "../Dll.h"
#include "../../File/File.h"

namespace XusoryEngine
{
	Dll::Dll(const std::wstring_view& path)
	{
		LoadDll(path);
	}

	void Dll::LoadDll(const std::wstring_view& path)
	{
		File::TryToFindFile(path);

		m_dllHandle = LoadLibrary(path.data());
		if (!m_dllHandle)
		{
			ThrowWithErrName(RuntimeError, WinFailedInfo("load Dll"));
		}
	}
}
