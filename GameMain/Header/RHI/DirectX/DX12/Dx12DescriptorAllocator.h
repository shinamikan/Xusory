#pragma once

#include "../Common/DxDefine.h"

namespace XusoryEngine
{
	constexpr UINT DEFAULT_CBV_SRV_UAV_HEAP_SIZE = 1024;
	constexpr UINT DEFAULT_SAMPLER_HEAP_SIZE = 32;
	constexpr UINT DEFAULT_RTV_DSV_SIZE = 16;

	class Dx12Device;
	class Dx12DescriptorHandle;
	class Dx12DescriptorHeap;
	class Dx12DescriptorAllocator
	{
	public:
		Dx12DescriptorAllocator(D3D12_DESCRIPTOR_HEAP_TYPE descHeapType, BOOL shaderVisible);
		void Reset();

		D3D12_DESCRIPTOR_HEAP_TYPE GetHeapType();
		BOOL GetShaderVisible();

		Dx12DescriptorHandle AllocateDescriptor(const Dx12Device* device, UINT descriptorNum);
		void ReleaseDescriptor(const Dx12DescriptorHandle& startDescriptor, UINT descriptorNum);

	private:
		Dx12DescriptorHeap* AddDefaultHeap(const Dx12Device* device);

		D3D12_DESCRIPTOR_HEAP_TYPE m_descHeapType = D3D12_DESCRIPTOR_HEAP_TYPE_UNKNOWN;
		BOOL m_shaderVisible;

		std::vector<Dx12DescriptorHeap> m_heapList;
	};
}
