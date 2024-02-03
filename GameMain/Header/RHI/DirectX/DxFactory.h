#pragma once

#include "Common/DxObject.h"

namespace XusoryEngine
{
	class DxFactory : public DxObject<IDXGIFactory4>
	{
	public:
		DxFactory() = default;
		void Create();
	};
}
