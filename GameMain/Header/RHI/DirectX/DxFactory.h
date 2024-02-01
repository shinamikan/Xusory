#pragma once

#include "Common/IDxObject.h"

namespace XusoryEngine
{
	class DxFactory : public IDxObject<IDXGIFactory4>
	{
	public:
		DxFactory() = default;
		void Create();
	};
}
