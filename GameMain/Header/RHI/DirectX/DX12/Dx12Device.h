#pragma once

#include "../Common/DxObject.h"

namespace XusoryEngine
{
	class DxFactory;
	class Dx12Device : public DxObject<ID3D12Device>
	{
	public:
		Dx12Device() = default;
		void Create(const DxFactory* factory);
	};
}
