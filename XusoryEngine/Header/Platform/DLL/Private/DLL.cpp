#include "../DLL.h"
#include "../../File/File.h"

namespace XusoryEngine::Platform
{
	DLL::DLL(const std::wstring_view& path)
	{
		LoadDLL(path);
	}

	void DLL::LoadDLL(const std::wstring_view& path)
	{
		File::TryToFindFile(path);

		m_dllHandle = LoadLibrary(path.data());
		if (!m_dllHandle)
		{
			ThrowWithErrName(RuntimeError, "DLL loading failed");
		}
	}
}
