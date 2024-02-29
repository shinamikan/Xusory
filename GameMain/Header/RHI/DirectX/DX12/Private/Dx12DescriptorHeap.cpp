#include "../Dx12DescriptorHeap.h"
#include "../Dx12Device.h"

namespace XusoryEngine
{
    Dx12DescriptorHandle::Dx12DescriptorHandle(D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle) : m_cpuHandle(cpuHandle) { }
    Dx12DescriptorHandle::Dx12DescriptorHandle(D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle)
        : m_cpuHandle(cpuHandle), m_gpuHandle(gpuHandle){ }

    const D3D12_CPU_DESCRIPTOR_HANDLE& Dx12DescriptorHandle::GetCpuDescriptorHandle() const
    {
        return m_cpuHandle;
    }

    const D3D12_GPU_DESCRIPTOR_HANDLE& Dx12DescriptorHandle::GetGpuDescriptorHandle() const
    {
        return m_gpuHandle;
    }

    D3D12_CPU_DESCRIPTOR_PTR Dx12DescriptorHandle::GetCpuDescriptorHandlePtr() const
    {
        return m_cpuHandle.ptr;
    }

    D3D12_GPU_DESCRIPTOR_PTR Dx12DescriptorHandle::GetGpuDescriptorHandlePtr() const
    {
        return m_gpuHandle.ptr;
    }

    BOOL Dx12DescriptorHandle::IsNull() const
    {
        return m_cpuHandle.ptr == NULL;
    }

    BOOL Dx12DescriptorHandle::GetShaderVisible() const
    {
        return m_gpuHandle.ptr != NULL;
    }

    Dx12DescriptorHandle Dx12DescriptorHandle::operator+(INT scaledByDescriptorSize) const
    {
        Dx12DescriptorHandle handle = *this;
        handle += scaledByDescriptorSize;
        return handle;
    }

    void Dx12DescriptorHandle::operator+=(INT scaledByDescriptorSize)
    {
        Offset(scaledByDescriptorSize);
    }

    void Dx12DescriptorHandle::Offset(INT scaledByDescriptorSize)
    {
        m_cpuHandle.ptr += scaledByDescriptorSize;
        if (GetShaderVisible())
        {
            m_gpuHandle.ptr += scaledByDescriptorSize;
        }
    }

    Dx12DescriptorHeap::Dx12DescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE descHeapType, BOOL shaderVisible) :
		m_descHeapType(descHeapType), m_shaderVisible(shaderVisible) { }

    Dx12DescriptorHandle Dx12DescriptorHeap::operator[](UINT descriptorIndex) const
    {
        return m_firstDescriptorHandle + static_cast<INT>(descriptorIndex * m_descriptorSize);
    }

    void Dx12DescriptorHeap::Create(const Dx12Device* device, UINT heapSize)
    {
        m_descriptorSize = (*device)->GetDescriptorHandleIncrementSize(m_descHeapType);

        D3D12_DESCRIPTOR_HEAP_DESC heapDesc;
        heapDesc.Type = m_descHeapType;
        heapDesc.NumDescriptors = heapSize;
        heapDesc.Flags = static_cast<D3D12_DESCRIPTOR_HEAP_FLAGS>(m_shaderVisible);
        heapDesc.NodeMask = 0;
        ThrowIfDxFailed((*device)->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(GetDxObjectAddressOf())));

        m_descriptorAllocatedList.resize(heapSize);
        m_firstDescriptorHandle.m_cpuHandle = (*this)->GetCPUDescriptorHandleForHeapStart();
        if (m_shaderVisible)
        {
            m_firstDescriptorHandle.m_gpuHandle = (*this)->GetGPUDescriptorHandleForHeapStart();
        }

        m_heapSize = heapSize;
    }

    void Dx12DescriptorHeap::ReSet()
    {
        DxObject::ReSet();

        m_descriptorAllocatedList.clear();
        m_firstDescriptorHandle = Dx12DescriptorHandle();

        m_heapSize = 0;
        m_descriptorNum = 0;
    }

    D3D12_DESCRIPTOR_HEAP_TYPE Dx12DescriptorHeap::GetHeapType() const
    {
        return m_descHeapType;
    }

    BOOL Dx12DescriptorHeap::GetShaderVisible() const
    {
        return m_shaderVisible;
    }

    UINT Dx12DescriptorHeap::GetHeapSize() const
    {
        return m_heapSize;
    }

    UINT Dx12DescriptorHeap::GetDescriptorSize() const
    {
        return m_descriptorSize;
    }

    UINT Dx12DescriptorHeap::GetNumOfDescriptors() const
    {
        return m_descriptorNum;
    }

    UINT Dx12DescriptorHeap::GetNumOfFreeSlots() const
    {
        return m_heapSize - m_descriptorNum;
    }

    BOOL Dx12DescriptorHeap::GetDescriptorAllocated(UINT index) const
    {
        return m_descriptorAllocatedList.at(index);
    }

    INT Dx12DescriptorHeap::FindDescriptor(const Dx12DescriptorHandle& handle) const
    {
        if ((handle.GetCpuDescriptorHandlePtr() - m_firstDescriptorHandle.GetCpuDescriptorHandlePtr()) % m_descriptorSize != 0)
        {
            return -1;
        }

        const D3D12_CPU_DESCRIPTOR_PTR endCpuPtr = (*this)[m_heapSize - 1].GetCpuDescriptorHandlePtr();
        if (handle.GetCpuDescriptorHandlePtr() < m_firstDescriptorHandle.GetCpuDescriptorHandlePtr() || handle.GetCpuDescriptorHandlePtr() > endCpuPtr)
        {
            return -1;
        }

        const INT index = static_cast<INT>(((handle.GetCpuDescriptorHandlePtr() - m_firstDescriptorHandle.GetCpuDescriptorHandlePtr()) / m_descriptorSize));
        return index;
    }

    void Dx12DescriptorHeap::CopyDescriptor(const Dx12Device* device, const Dx12DescriptorHeap* destHeap, UINT destStartIndex, const Dx12DescriptorHeap* srcHeap, UINT srcStartIndex, UINT descriptorNum)
    {
        if (destHeap->m_shaderVisible != srcHeap->m_shaderVisible || destHeap->m_descHeapType != srcHeap->m_descHeapType)
        {
            ThrowWithErrName(DxLogicError, "The source descriptor heap type is different from the dest descriptor heap type");
        }

        const Dx12DescriptorHandle destHandle = (*destHeap)[destStartIndex];
        const Dx12DescriptorHandle srcHandle = (*srcHeap)[srcStartIndex];
        (*device)->CopyDescriptorsSimple(descriptorNum, destHandle.GetCpuDescriptorHandle(),
            srcHandle.GetCpuDescriptorHandle(), srcHeap->m_descHeapType);
    }

    void Dx12DescriptorHeap::SetDescriptorAllocated(UINT startIndex, UINT descriptorNum, CHAR isAllocated)
    {
        if (startIndex + descriptorNum > m_heapSize)
        {
            ThrowWithErrName(DxLogicError, "The descriptor to be set is out of range");
        }
        for (UINT i = startIndex; i < startIndex + descriptorNum; i++)
        {
            m_descriptorAllocatedList.at(i) = isAllocated;
        }
        m_descriptorNum = isAllocated ? m_descriptorNum + descriptorNum : m_descriptorNum - descriptorNum;
    }
}
