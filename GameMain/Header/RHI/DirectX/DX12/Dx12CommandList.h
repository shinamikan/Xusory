#pragma once

#include <functional>
#include "../Common/DxObject.h"

namespace XusoryEngine
{
	class Dx12Buffer;
	class Dx12ConstantBuffer;
	class Dx12DepthStencilBuffer;
	class Dx12MeshBuffer;
	class Dx12RenderTargetBuffer;
	class Dx12ShaderResourceBuffer;
	class Dx12UnorderedAccessBuffer;

	class Dx12CommandAllocator;
	class Dx12DescriptorHandle;
	class Dx12DescriptorHeap;
	class Dx12Device;
	class Dx12RootSignature;

	class Dx12GraphicsPipelineState;
	class Dx12ComputePipelineState;

	class Dx12CommandList : public DxObject<ID3D12GraphicsCommandList>
	{
	public:
		Dx12CommandList() = default;

		void Create(const Dx12Device* device, const Dx12CommandAllocator* allocator, D3D12_COMMAND_LIST_TYPE cmdListType, UINT nodeMask = 0);
		void ReSet() override;

		D3D12_COMMAND_LIST_TYPE GetCommandListType() const;

		void CopyBuffer(Dx12Buffer* destBuffer, Dx12Buffer* srcBuffer);
		void CopyBufferRegion(Dx12Buffer* destBuffer, Dx12Buffer* srcBuffer, UINT64 dstOffset, UINT64 srcOffset, UINT64 copySize);

		void SetDescriptorHeaps(const Dx12DescriptorHeap* viewDescHeap, const Dx12DescriptorHeap* samplerDescHeap) const;
		void TranslationBufferState(Dx12Buffer* buffer, D3D12_RESOURCE_STATES translationState, BOOL hasTransBeforeEnd = true);

		void EndCommand() const;

	protected:
		std::vector<std::function<void()>> m_delegationList;
		Dx12RootSignature* m_rootSignature = nullptr;

	private:
		D3D12_COMMAND_LIST_TYPE m_cmdListType = D3D12_COMMAND_LIST_TYPE_UNKNOWN;

		Dx12DescriptorHeap* m_activeViewDescHeap = nullptr;
		Dx12DescriptorHeap* m_activeSamplerDescHeap = nullptr;
	};

	class Dx12GraphicsCommandList : public Dx12CommandList
	{
	public:
		void ClearDepth(const Dx12DepthStencilBuffer* buffer, FLOAT depth) const;
		void ClearStencil(const Dx12DepthStencilBuffer* buffer, UINT8 stencil) const;
		void ClearDepthStencil(const Dx12DepthStencilBuffer* buffer, FLOAT depth, UINT8 stencil) const;
		void ClearRenderTarget(const Dx12RenderTargetBuffer* buffer, const FLOAT color[4]) const;
		void ClearUnorderedAccessUint(const Dx12UnorderedAccessBuffer* buffer, const UINT clearValue[4]) const;
		void ClearUnorderedAccessFloat(const Dx12UnorderedAccessBuffer* buffer, const FLOAT clearValue[4]) const;

		void SetVertexBuffer(const D3D12_VERTEX_BUFFER_VIEW& vbView) const;
		void SetIndexBuffer(const D3D12_INDEX_BUFFER_VIEW& ibView) const;
		void SetMeshBuffer(const Dx12MeshBuffer* buffer) const;
		void SetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY primitiveTopology) const;

		void SetViewport(const D3D12_VIEWPORT& viewport) const;
		void SetViewport(FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT minDepth, FLOAT maxDepth) const;
		void SetScissorRect(const D3D12_RECT& rect) const;
		void SetScissorRect(LONG left, LONG top, LONG right, LONG bottom) const;

		void SetBlendFactor(const FLOAT BlendFactor[4]) const;
		void SetRenderTarget(const Dx12RenderTargetBuffer* rtBuffer, const Dx12DepthStencilBuffer* dsBuffer) const;
		void SetRenderTargets(UINT renderTargetNum, const Dx12RenderTargetBuffer* rtBuffer[], const Dx12DepthStencilBuffer* dsBuffer) const;
		void SetStencilRef(UINT stencilRef) const;

		void DrawInstanced();
		void DrawIndexedInstanced();

		void SetGraphicsPipelineState(const Dx12GraphicsPipelineState* pipelineState) const;
		void SetGraphicsRootSignature(Dx12RootSignature* rootSignature);

		void SetGraphicsRootConstant(UINT parameterIndex, UINT data, UINT offset) const;
		void SetGraphicsRootConstants(UINT parameterIndex, UINT dataNum, const UINT* data, UINT offset) const;
		void SetGraphicsRootCbv(UINT parameterIndex, const Dx12ConstantBuffer* buffer) const;
		void SetGraphicsRootSrv(UINT parameterIndex, const Dx12ShaderResourceBuffer* buffer) const;
		void SetGraphicsRootUav(UINT parameterIndex, const Dx12UnorderedAccessBuffer* buffer) const;
		void SetGraphicsRootDescriptorTable(UINT parameterIndex, const Dx12DescriptorHandle& handle) const;

	private:
		Dx12GraphicsPipelineState* m_pipelineState = nullptr;
	};
}
