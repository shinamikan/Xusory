#include "../Dx12MeshBuffer.h"
#include "../Dx12Buffer.h"
#include "../Dx12Buffer1D.h"
#include "../../Dx12CommandList.h"
#include "../../Dx12Device.h"

namespace XusoryEngine
{
	Dx12MeshBuffer::Dx12MeshBuffer()
	{
		m_vertexBuffer = new Dx12Buffer1D();
		m_indexBuffer = new Dx12Buffer1D();

		m_vertexUploadBuffer = new Dx12Buffer(D3D12_HEAP_TYPE_UPLOAD);
		m_indexUploadBuffer = new Dx12Buffer(D3D12_HEAP_TYPE_UPLOAD);
	}

	Dx12MeshBuffer::~Dx12MeshBuffer()
	{
		delete m_vertexBuffer;
		delete m_indexBuffer;

		delete m_vertexUploadBuffer;
		delete m_indexUploadBuffer;
	}

	void Dx12MeshBuffer::CreateMeshBuffer(const Dx12Device* device, UINT vertexNum, UINT vertexSize, UINT indexNum, DXGI_FORMAT indexFormat)
	{
		UINT indexSize = 0;
		switch (indexFormat)
		{
		case DXGI_FORMAT_R16_UINT:
			indexSize = 2;
			break;
		case DXGI_FORMAT_R32_UINT:
			indexSize = 4;
			break;
		default:
			ThrowWithErrName(DxLogicError, "index format is not match");
		}

		m_vertexBuffer->CreateFixedBuffer(device, D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_FLAG_NONE, static_cast<UINT64>(vertexNum) * vertexSize);
		m_indexBuffer->CreateFixedBuffer(device, D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_FLAG_NONE, static_cast<UINT64>(indexNum) * indexSize);

		m_vertexNum = vertexNum;
		m_vertexSize = vertexSize;
		m_indexNum = indexNum;
		m_indexSize = indexSize;
		m_indexFormat = indexFormat;

		const auto heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		const auto vertexResourceDesc = m_vertexBuffer->GetBufferDesc();
		ThrowIfDxFailed((*device)->CreateCommittedResource(
			&heapProperties, D3D12_HEAP_FLAG_NONE,
			&vertexResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
			IID_PPV_ARGS(m_vertexUploadBuffer->GetDxObjectAddressOf())));

		const auto indexResourceDesc = m_indexBuffer->GetBufferDesc();
		ThrowIfDxFailed((*device)->CreateCommittedResource(
			&heapProperties, D3D12_HEAP_FLAG_NONE,
			&indexResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
			IID_PPV_ARGS(m_indexUploadBuffer->GetDxObjectAddressOf())));

		m_vertexUploadBuffer->m_usingState = D3D12_RESOURCE_STATE_GENERIC_READ;
		m_indexUploadBuffer->m_usingState = D3D12_RESOURCE_STATE_GENERIC_READ;
	}

	void Dx12MeshBuffer::UploadMeshResource(const Dx12CommandList* commandList, const void* vertexList, const void* indexList) const
	{
		m_vertexBuffer->UploadResource(commandList, D3D12_RESOURCE_STATE_GENERIC_READ, m_vertexUploadBuffer, vertexList, GetVertexBufferSize());
		m_indexBuffer->UploadResource(commandList, D3D12_RESOURCE_STATE_GENERIC_READ, m_indexUploadBuffer, indexList, GetIndexBufferSize());
	}

	void Dx12MeshBuffer::Reset()
	{
		m_vertexBuffer->ReSet();
		m_indexBuffer->ReSet();

		m_vertexNum = 0;
		m_vertexSize = 0;
		m_indexNum = 0;
		m_indexSize = 0;
		m_indexFormat = DXGI_FORMAT_UNKNOWN;
	}

	const Dx12Buffer1D* Dx12MeshBuffer::GetVertexBuffer() const
	{
		return m_vertexBuffer;
	}

	const Dx12Buffer1D* Dx12MeshBuffer::GetIndexBuffer() const
	{
		return m_indexBuffer;
	}

	D3D12_VERTEX_BUFFER_VIEW Dx12MeshBuffer::GetVertexBufferView() const
	{
		D3D12_VERTEX_BUFFER_VIEW vbv;
		vbv.BufferLocation = m_vertexBuffer->GetGpuVirtualAddress();
		vbv.SizeInBytes = m_vertexNum * m_vertexSize;
		vbv.StrideInBytes = m_vertexSize;
		return vbv;
	}

	D3D12_INDEX_BUFFER_VIEW Dx12MeshBuffer::GetIndexBufferView() const
	{
		D3D12_INDEX_BUFFER_VIEW ibv;
		ibv.BufferLocation = m_indexBuffer->GetGpuVirtualAddress();
		ibv.SizeInBytes = m_indexNum * m_indexSize;
		ibv.Format = DXGI_FORMAT_R32_UINT;
		return ibv;
	}

	UINT64 Dx12MeshBuffer::GetVertexBufferSize() const
	{
		return (*m_vertexBuffer)->GetDesc().Width;
	}

	UINT64 Dx12MeshBuffer::GetIndexBufferSize() const
	{
		return (*m_indexBuffer)->GetDesc().Width;
	}
}
