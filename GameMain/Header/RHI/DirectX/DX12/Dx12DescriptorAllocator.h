#pragma once

#include "../Common/DxDefine.h"

namespace XusoryEngine
{
	constexpr UINT DEFAULT_CBV_SRV_UAV_HEAP_SIZE = 128;
	constexpr UINT DEFAULT_SAMPLER_HEAP_SIZE = 16;
	constexpr UINT DEFAULT_RTV_DSV_SIZE = 8;

	class Dx12Device;
	class Dx12DescriptorHandle;
	class Dx12DescriptorHeap;
	class Dx12DescriptorAllocator
	{
	public:
		Dx12DescriptorAllocator(D3D12_DESCRIPTOR_HEAP_TYPE descHeapType, BOOL shaderVisible);
		DELETE_COPY_OPERATOR(Dx12DescriptorAllocator);
		DELETE_MOVE_OPERATOR(Dx12DescriptorAllocator);
		~Dx12DescriptorAllocator();

		void Create(const Dx12Device* device) const;
		void ReSet();

		Dx12DescriptorHeap* GetHeap() const;
		D3D12_DESCRIPTOR_HEAP_TYPE GetHeapType() const;
		BOOL GetShaderVisible() const;

		Dx12DescriptorHandle* AllocateDescriptor(const Dx12Device* device, UINT descriptorNum);
		void ReleaseDescriptor(const Dx12DescriptorHandle& startDescriptor, UINT descriptorNum) const;

	private:
		void ExpandHeap(const Dx12Device* device);

		D3D12_DESCRIPTOR_HEAP_TYPE m_descHeapType = D3D12_DESCRIPTOR_HEAP_TYPE_UNKNOWN;
		BOOL m_shaderVisible = false;

		Dx12DescriptorHeap* m_heap = nullptr;
		std::vector<std::unique_ptr<Dx12DescriptorHandle>> m_descriptorHandleList;
	};
}
