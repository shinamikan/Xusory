#include "../Dx12DescriptorAllocator.h"
#include "../Dx12DescriptorHeap.h"

namespace XusoryEngine
{
	Dx12DescriptorAllocator::Dx12DescriptorAllocator(D3D12_DESCRIPTOR_HEAP_TYPE descHeapType, BOOL shaderVisible) :
		m_descHeapType(descHeapType), m_shaderVisible(shaderVisible){ }

	Dx12DescriptorAllocator::~Dx12DescriptorAllocator()
	{
		if (m_heap)
		{
			delete m_heap;
			m_heap = nullptr;
		}
	}

	void Dx12DescriptorAllocator::Reset()
	{
		m_heapList.clear();
	}

	D3D12_DESCRIPTOR_HEAP_TYPE Dx12DescriptorAllocator::GetHeapType() const
	{
		return m_descHeapType;
	}

	BOOL Dx12DescriptorAllocator::GetShaderVisible() const
	{
		return m_shaderVisible;
	}

	Dx12DescriptorHandle Dx12DescriptorAllocator::AllocateDescriptor(const Dx12Device* device, UINT descriptorNum)
	{
		if (m_heap == nullptr)
		{
			m_heap = new Dx12DescriptorHeap(m_descHeapType, m_shaderVisible);
			switch (m_descHeapType)
			{
			case D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV:
				m_heap->Create(device, DEFAULT_CBV_SRV_UAV_HEAP_SIZE);
				break;

			case D3D12_DESCRIPTOR_HEAP_TYPE_RTV:
			case D3D12_DESCRIPTOR_HEAP_TYPE_DSV:
				m_heap->Create(device, DEFAULT_RTV_DSV_SIZE);
				break;

			default:
				m_heap->Create(device, DEFAULT_SAMPLER_HEAP_SIZE);
				break;
			}

			m_heap->SetDescriptorAllocated(0, descriptorNum, true);
			return (*m_heap)[0];
		}

		while (m_heap->GetNumOfFreeSlots() < descriptorNum)
		{
			ExpandHeap(device);
		}

		BOOL findFlag = false;
		UINT findIndex = 0;

		while (!findFlag)
		{
			while (findIndex <= m_heap->GetHeapSize() - descriptorNum)
			{
				UINT indexTemp = findIndex;
				while (indexTemp - findIndex < descriptorNum)
				{
					if (!m_heap->GetDescriptorAllocated(indexTemp))
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

			if (!findFlag)
			{
				ExpandHeap(device);
			}
		}

		m_heap->SetDescriptorAllocated(findIndex, descriptorNum, true);
		return (*m_heap)[findIndex];
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

	void Dx12DescriptorAllocator::ExpandHeap(const Dx12Device* device)
	{
		auto* heap = new Dx12DescriptorHeap(m_descHeapType, m_shaderVisible);
		heap->Create(device, m_heap->GetHeapSize() * 2);
		heap->m_descriptorNum = m_heap->GetNumOfDescriptors();

		Dx12DescriptorHeap::CopyDescriptor(device, heap, 0, m_heap, 0, m_heap->GetHeapSize());
		std::copy(m_heap->m_descriptorAllocatedList.begin(), m_heap->m_descriptorAllocatedList.end(), heap->m_descriptorAllocatedList.begin());

		delete m_heap;
		m_heap = heap;
	}
}
