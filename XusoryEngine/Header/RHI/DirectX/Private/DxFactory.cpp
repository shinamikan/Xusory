#include "../DxFactory.h"

namespace XusoryEngine
{
	void DxFactory::Create()
	{
		ThrowIfDxFailed(CreateDXGIFactory1(IID_PPV_ARGS(m_dxObject.GetAddressOf())));
	}
}
