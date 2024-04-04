#pragma once

#include "../Common/DxObject.h"

namespace XusoryEngine
{
	class Dx12Device;
	DLL_CLASS(Dx12CommandAllocator) : public DxObject<ID3D12CommandAllocator>
	{
	public:
		Dx12CommandAllocator() = default;

		void Create(const Dx12Device* device, D3D12_COMMAND_LIST_TYPE cmdListType);
		void ReSetCommandAllocator() const;
		void ReSet() override;

		D3D12_COMMAND_LIST_TYPE GetCommandListType() const;

	private:
		D3D12_COMMAND_LIST_TYPE m_cmdListType = D3D12_COMMAND_LIST_TYPE_UNKNOWN;
	};
}
