#pragma once

#include "../../Common/DxDefine.h"

namespace XusoryEngine
{
	class Dx12Buffer1D;
	class Dx12CommandList;
	class Dx12Device;
	class Dx12MeshBuffer
	{
	public:
		Dx12MeshBuffer();
		DELETE_COPY_OPERATOR(Dx12MeshBuffer);
		DELETE_MOVE_OPERATOR(Dx12MeshBuffer);
		~Dx12MeshBuffer();

		const Dx12Buffer1D* GetVertexBuffer() const;
		const Dx12Buffer1D* GetIndexBuffer() const;
		D3D12_VERTEX_BUFFER_VIEW GetVertexBufferView() const;
		D3D12_INDEX_BUFFER_VIEW	GetIndexBufferView() const;
		UINT64 GetVertexBufferSize() const;
		UINT64 GetIndexBufferSize() const;

		void CreateMeshBuffer(const Dx12Device* device, UINT vertexNum, UINT vertexSize, UINT indexNum, DXGI_FORMAT indexFormat);
		void UploadMeshResource(const Dx12Device* device, Dx12CommandList* commandList, const void* vertexList, const void* indexList) const;
		void Reset();

	private:
		Dx12Buffer1D* m_vertexBuffer = nullptr;
		Dx12Buffer1D* m_indexBuffer = nullptr;

		UINT m_vertexNum = 0;
		UINT m_vertexSize = 0;
		UINT m_indexNum = 0;
		UINT m_indexSize = 0;
		DXGI_FORMAT m_indexFormat = DXGI_FORMAT_UNKNOWN;
	};
}
