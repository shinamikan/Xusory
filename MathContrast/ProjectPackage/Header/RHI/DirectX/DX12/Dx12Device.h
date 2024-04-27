#pragma once

#include "../Common/DxObject.h"

namespace XusoryEngine
{
	class DxFactory;
	DLL_CLASS(Dx12Device) : public DxObject<ID3D12Device>
	{
	public:
		Dx12Device() = default;
		void Create(const DxFactory* factory);
	};
}
