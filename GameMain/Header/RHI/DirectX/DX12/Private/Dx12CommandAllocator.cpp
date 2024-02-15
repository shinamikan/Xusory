#include "../Dx12CommandAllocator.h"
#include "../Dx12Device.h"

namespace XusoryEngine
{
	void Dx12CommandAllocator::Create(const Dx12Device* device, D3D12_COMMAND_LIST_TYPE cmdListType)
	{
		ThrowIfDxFailed((*device)->CreateCommandAllocator(cmdListType, IID_PPV_ARGS(GetDxObjectAddressOf())));
		m_cmdListType = cmdListType;
	}

	void Dx12CommandAllocator::ReSet()
	{
		DxObject::ReSet();
		m_cmdListType = D3D12_COMMAND_LIST_TYPE_UNKNOWN;
	}

	D3D12_COMMAND_LIST_TYPE Dx12CommandAllocator::GetCommandListType() const
	{
		return m_cmdListType;
	}
}
