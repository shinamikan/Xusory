#pragma once

#include "../Common/IDxObject.h"

namespace XusoryEngine
{
	class DxFactory;
	class Dx12Device : public IDxObject<ID3D12Device>
	{
	public:
		Dx12Device() = default;
		void Create(const DxFactory& factory);
	};
}
