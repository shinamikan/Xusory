#include "../Dx12DescriptorAllocator.h"
#include "../Dx12DescriptorHeap.h"

namespace XusoryEngine
{
	Dx12DescriptorAllocator::Dx12DescriptorAllocator(D3D12_DESCRIPTOR_HEAP_TYPE descHeapType, BOOL shaderVisible) :
		m_descHeapType(descHeapType), m_shaderVisible(shaderVisible){ }

	void Dx12DescriptorAllocator::Reset()
	{
		m_heapList.clear();
	}

	D3D12_DESCRIPTOR_HEAP_TYPE Dx12DescriptorAllocator::GetHeapType()
	{
		return m_descHeapType;
	}

	BOOL Dx12DescriptorAllocator::GetShaderVisible()
	{
		return m_shaderVisible;
	}

	Dx12DescriptorHandle Dx12DescriptorAllocator::AllocateDescriptor(const Dx12Device* device, UINT descriptorNum)
	{
		BOOL findFlag = false;
		for (auto& heap : m_heapList)
		{
			if (heap.GetNumOfFreeSlots() < descriptorNum)
			{
				continue;
			}

			UINT findIndex = 0;
			while (findIndex < heap.GetHeapSize())
			{
				UINT indexTemp = findIndex;
				while (indexTemp - findIndex < descriptorNum)
				{
					if (!heap.GetDescriptorAllocated(indexTemp))
					{
						indexTemp++;
					}
					else
					{
						break;
					}
				}

				if (indexTemp - findIndex < descriptorNum)
				{
					findIndex = indexTemp + 1;
				}
				else
				{
					findFlag = true;
					break;
				}
			}

			if (findFlag)
			{
				heap.SetDescriptorAllocated(findIndex, descriptorNum, true);
				return heap[findIndex];
			}
		}

		auto* pHeap = AddDefaultHeap(device);
		pHeap->SetDescriptorAllocated(0, descriptorNum, true);
		return (*pHeap)[0];
	}

	void Dx12DescriptorAllocator::ReleaseDescriptor(const Dx12DescriptorHandle& startDescriptor, UINT descriptorNum)
	{
		for (auto& heap : m_heapList)
		{
			if (const UINT index = heap.FindDescriptor(startDescriptor); index != -1)
			{
				heap.SetDescriptorAllocated(index, descriptorNum, false);
				return;
			}
		}
	}

	Dx12DescriptorHeap* Dx12DescriptorAllocator::AddDefaultHeap(const Dx12Device* device)
	{
		auto heap = Dx12DescriptorHeap(m_descHeapType, m_shaderVisible);
		switch (m_descHeapType)
		{
		case D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV:
			heap.Create(device, DEFAULT_CBV_SRV_UAV_HEAP_SIZE);
			break;

		case D3D12_DESCRIPTOR_HEAP_TYPE_RTV:
		case D3D12_DESCRIPTOR_HEAP_TYPE_DSV:
			heap.Create(device, DEFAULT_RTV_DSV_SIZE);
			break;

		default:
			heap.Create(device, DEFAULT_SAMPLER_HEAP_SIZE);
			break;
		}

		m_heapList.push_back(std::move(heap));
		return &*(m_heapList.end() - 1);
	}
}
