#pragma once

#include <vector>
#include "../Common/DxObject.h"

namespace XusoryEngine
{
	typedef SIZE_T D3D12_CPU_DESCRIPTOR_PTR;
	typedef UINT64 D3D12_GPU_DESCRIPTOR_PTR;

	class Dx12DescriptorHandle
	{
		friend class Dx12DescriptorHeap;
		friend class Dx12DescriptorAllocator;

	public:
		Dx12DescriptorHandle() = default;
		Dx12DescriptorHandle(D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle);
		Dx12DescriptorHandle(D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle);

		const D3D12_CPU_DESCRIPTOR_HANDLE& GetCpuDescriptorHandle() const;
		const D3D12_GPU_DESCRIPTOR_HANDLE& GetGpuDescriptorHandle() const;
		D3D12_CPU_DESCRIPTOR_PTR GetCpuDescriptorHandlePtr() const;
		D3D12_GPU_DESCRIPTOR_PTR GetGpuDescriptorHandlePtr() const;

		BOOL IsNull() const;
		BOOL GetShaderVisible() const;

	private:
		Dx12DescriptorHandle operator+(INT scaledByDescriptorSize) const;
		void operator+=(INT scaledByDescriptorSize);

		void Offset(INT scaledByDescriptorSize);

		D3D12_CPU_DESCRIPTOR_HANDLE m_cpuHandle{ NULL };
		D3D12_GPU_DESCRIPTOR_HANDLE m_gpuHandle{ NULL };
	};

	class Dx12Device;
	class Dx12DescriptorHeap : public DxObject<ID3D12DescriptorHeap>
	{
		friend class Dx12DescriptorAllocator;

	public:
		Dx12DescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE descHeapType, BOOL shaderVisible);
		Dx12DescriptorHandle operator[](UINT descriptorIndex) const;

		void Create(const Dx12Device* device, UINT heapSize);
		void ReSet() override;

		D3D12_DESCRIPTOR_HEAP_TYPE GetHeapType() const;
		BOOL GetShaderVisible() const;
		UINT GetHeapSize() const;
		UINT GetDescriptorSize() const;
		UINT GetNumOfDescriptors() const;
		UINT GetNumOfFreeSlots() const;
		BOOL GetDescriptorAllocated(UINT index) const;

		INT FindDescriptor(const Dx12DescriptorHandle& handle) const;
		static void CopyDescriptor(const Dx12Device* device, const Dx12DescriptorHeap* destHeap, UINT destStartIndex,
			const Dx12DescriptorHeap* srcHeap, UINT srcStartIndex, UINT descriptorNum);

	private:
		void SetDescriptorAllocated(UINT startIndex, UINT descriptorNum, CHAR isAllocated);

		D3D12_DESCRIPTOR_HEAP_TYPE m_descHeapType = D3D12_DESCRIPTOR_HEAP_TYPE_UNKNOWN;
		BOOL m_shaderVisible = false;
		UINT m_descriptorSize = 0;

		std::vector<CHAR> m_descriptorAllocatedList;
		Dx12DescriptorHandle m_firstDescriptorHandle;

		UINT m_heapSize = 0;
		UINT m_descriptorNum = 0;
	};
}
