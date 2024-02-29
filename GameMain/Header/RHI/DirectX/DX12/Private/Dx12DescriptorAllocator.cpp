#include "../Dx12DescriptorAllocator.h"
#include "../Dx12DescriptorHeap.h"

namespace XusoryEngine
{
	Dx12DescriptorAllocator::Dx12DescriptorAllocator(D3D12_DESCRIPTOR_HEAP_TYPE descHeapType, BOOL shaderVisible) :
		m_descHeapType(descHeapType), m_shaderVisible(shaderVisible)
	{
		m_heap = new Dx12DescriptorHeap(descHeapType, shaderVisible);
	}

	Dx12DescriptorAllocator::~Dx12DescriptorAllocator()
	{
		ReSet();
	}

	void Dx12DescriptorAllocator::Create(const Dx12Device* device) const
	{
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
	}

	void Dx12DescriptorAllocator::ReSet()
	{
		if (m_heap != nullptr)
		{
			delete m_heap;
			m_heap = nullptr;
		}
		m_descriptorHandleList.clear();
	}

	D3D12_DESCRIPTOR_HEAP_TYPE Dx12DescriptorAllocator::GetHeapType() const
	{
		return m_descHeapType;
	}

	BOOL Dx12DescriptorAllocator::GetShaderVisible() const
	{
		return m_shaderVisible;
	}

	Dx12DescriptorHandle* Dx12DescriptorAllocator::AllocateDescriptor(const Dx12Device* device, UINT descriptorNum)
	{
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

		const INT addDescriptorNum = findIndex + descriptorNum - static_cast<UINT>(m_descriptorHandleList.size());
		if (addDescriptorNum > 0)
		{
			for (INT i = 0; i < addDescriptorNum; i++)
			{
				auto* handle = new Dx12DescriptorHandle;
				*handle = (*m_heap)[static_cast<UINT>(m_descriptorHandleList.size())];
				m_descriptorHandleList.emplace_back(handle);
			}
		}

		return m_descriptorHandleList.at(findIndex).get();
	}

	void Dx12DescriptorAllocator::ReleaseDescriptor(const Dx12DescriptorHandle& startDescriptor, UINT descriptorNum) const
	{
		if (const UINT index = m_heap->FindDescriptor(startDescriptor); index != -1)
		{
			m_heap->SetDescriptorAllocated(index, descriptorNum, false);
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

		for (UINT i = 0; i < m_descriptorHandleList.size(); i++)
		{
			*m_descriptorHandleList.at(i) = (*m_heap)[i];
		}
	}
}
