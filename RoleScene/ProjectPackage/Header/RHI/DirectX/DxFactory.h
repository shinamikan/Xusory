#pragma once

#include "Common/DxObject.h"

namespace XusoryEngine
{
	DLL_CLASS(DxFactory) : public DxObject<IDXGIFactory4>
	{
	public:
		DxFactory() = default;
		void Create();
	};
}
