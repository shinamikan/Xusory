#include "../DxFactory.h"

namespace XusoryEngine
{
	void DxFactory::Create()
	{
		ThrowIfDxFailed(CreateDXGIFactory(IID_PPV_ARGS(m_dxObject.GetAddressOf())));
	}
}
