#pragma once

#include "Common/IDxObject.h"

namespace XusoryEngine
{
	DLL_CLASS(DxFactory) : public IDxObject<IDXGIFactory4>
	{
	public:
		DxFactory() = default;
		void Create();
	};
}
