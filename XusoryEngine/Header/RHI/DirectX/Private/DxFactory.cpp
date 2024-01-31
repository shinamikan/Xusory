#include "../DxFactory.h"
#include "../Common/DxDefine.h"

namespace XusoryEngine
{
	void DxFactory::Create()
	{
		ThrowIfDxFuncFailed(CreateDXGIFactory(IID_PPV_ARGS(m_dxObject.GetAddressOf())));
	}
}
