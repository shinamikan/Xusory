#include "../Dx12CommandList.h"

#include <vector>

#include "../Buffer/Dx12Buffer.h"
#include "../Buffer/Dx12ConstantBuffer.h"
#include "../Buffer/Dx12DepthStencilBuffer.h"
#include "../Buffer/Dx12MeshBuffer.h"
#include "../Buffer/Dx12RenderTargetBuffer.h"
#include "../Buffer/Dx12ShaderResourceBuffer.h"
#include "../Buffer/Dx12UnorderedAccessBuffer.h"

#include "../Dx12CommandAllocator.h"
#include "../Dx12DescriptorHeap.h"
#include "../Dx12Device.h"
#include "../Dx12RootSignature.h"

#include "../Dx12PipelineState.h"

namespace XusoryEngine
{
	void Dx12CommandList::Create(const Dx12Device* device, const Dx12CommandAllocator* allocator, D3D12_COMMAND_LIST_TYPE cmdListType, UINT nodeMask)
	{
		if (cmdListType != allocator->GetCommandListType())
		{
			ThrowWithErrName(DxLogicError, "The type of command list and command allocator is not match");
		}

		ThrowIfDxFailed((*device)->CreateCommandList(nodeMask, cmdListType, allocator->GetDxObjectPtr(),
			nullptr, IID_PPV_ARGS(GetDxObjectAddressOf())));
	}

	void Dx12CommandList::ResetCommandList(const Dx12CommandAllocator* allocator, const Dx12PipelineState* pipelineState) const
	{
		ThrowIfDxFailed((*this)->Reset(allocator->GetDxObjectPtr(), pipelineState ? pipelineState->GetDxObjectPtr() : nullptr));
	}

	void Dx12CommandList::ReSet()
	{
		DxObject::ReSet();
		m_activeViewDescHeap = nullptr;
		m_activeSamplerDescHeap = nullptr;

		m_cmdListType = D3D12_COMMAND_LIST_TYPE_UNKNOWN;
	}

	D3D12_COMMAND_LIST_TYPE Dx12CommandList::GetCommandListType() const
	{
		return m_cmdListType;
	}

	void Dx12CommandList::CopyBuffer(Dx12Buffer* destBuffer, Dx12Buffer* srcBuffer)
	{
		TranslationBufferState(destBuffer, D3D12_RESOURCE_STATE_COPY_DEST);
		TranslationBufferState(srcBuffer, D3D12_RESOURCE_STATE_COPY_SOURCE);

		(*this)->CopyResource(destBuffer->GetDxObjectPtr(), srcBuffer->GetDxObjectPtr());

		TranslationBufferState(destBuffer, destBuffer->GetCurrentState());
		TranslationBufferState(srcBuffer, srcBuffer->GetCurrentState());
	}

	void Dx12CommandList::CopyBufferRegion(Dx12Buffer* destBuffer, Dx12Buffer* srcBuffer, UINT64 dstOffset, UINT64 srcOffset, UINT64 copySize)
	{
		TranslationBufferState(destBuffer, D3D12_RESOURCE_STATE_COPY_DEST);
		TranslationBufferState(srcBuffer, D3D12_RESOURCE_STATE_COPY_SOURCE);

		(*this)->CopyBufferRegion(destBuffer->GetDxObjectPtr(), dstOffset, srcBuffer->GetDxObjectPtr(), srcOffset, copySize);

		TranslationBufferState(destBuffer, destBuffer->GetCurrentState());
		TranslationBufferState(srcBuffer, srcBuffer->GetCurrentState());
	}

	void Dx12CommandList::SetDescriptorHeaps(const Dx12DescriptorHeap* viewDescHeap, const Dx12DescriptorHeap* samplerDescHeap) const
	{
		const UINT heapNum = samplerDescHeap->GetDxObjectPtr() ? 2 : 1;
		ID3D12DescriptorHeap* descriptorHeaps[2];
		descriptorHeaps[0] = viewDescHeap->GetDxObjectPtr();
		descriptorHeaps[1] = samplerDescHeap->GetDxObjectPtr();

		(*this)->SetDescriptorHeaps(heapNum, descriptorHeaps);
	}

	void Dx12CommandList::TranslationBufferState(Dx12Buffer* buffer, D3D12_RESOURCE_STATES translationState, BOOL hasTransBeforeEnd)
	{
		if (buffer->GetCurrentState() == translationState || buffer->GetTransitioningState() == translationState)
		{
			return;
		}

		const auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(buffer->GetDxObjectPtr(),
			buffer->GetTransitioningState() == D3D12_RESOURCE_STATES_UNKNOWN ? buffer->GetCurrentState() : buffer->GetTransitioningState(), translationState);
		(*this)->ResourceBarrier(1, &barrier);

		buffer->m_transitioningState = translationState;

		if (!hasTransBeforeEnd)
		{
			auto finishEvent = [=]() -> void
			{
				buffer->m_usingState = buffer->m_transitioningState;
				buffer->m_transitioningState = D3D12_RESOURCE_STATES_UNKNOWN;
			};

			m_delegationList.push_back(std::move(finishEvent));
		}
	}

	void Dx12CommandList::EndCommand() const
	{
		ThrowIfDxFailed((*this)->Close());
	}

	void Dx12GraphicsCommandList::ClearDepth(const Dx12DepthStencilBuffer* buffer, FLOAT depth) const
	{
		const auto dsvHandle = buffer->GetDsvHandle().GetCpuDescriptorHandle();
		(*this)->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, depth, 0, 0, nullptr);
	}

	void Dx12GraphicsCommandList::ClearStencil(const Dx12DepthStencilBuffer* buffer, UINT8 stencil) const
	{
		const auto dsvHandle = buffer->GetDsvHandle().GetCpuDescriptorHandle();
		(*this)->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_STENCIL, 1.0f, stencil, 0, nullptr);
	}

	void Dx12GraphicsCommandList::ClearDepthStencil(const Dx12DepthStencilBuffer* buffer, FLOAT depth, UINT8 stencil) const
	{
		const auto dsvHandle = buffer->GetDsvHandle().GetCpuDescriptorHandle();
		(*this)->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, depth, stencil, 0, nullptr);
	}

	void Dx12GraphicsCommandList::ClearRenderTarget(const Dx12RenderTargetBuffer* buffer, const FLOAT color[4]) const
	{
		const auto rtvHandle = buffer->GetRtvHandle().GetCpuDescriptorHandle();
		(*this)->ClearRenderTargetView(rtvHandle, color, 0, nullptr);
	}

	void Dx12GraphicsCommandList::ClearUnorderedAccessUint(const Dx12UnorderedAccessBuffer* buffer, const UINT clearValue[4]) const
	{
		const auto cpuHandle = buffer->GetUavHandle().GetCpuDescriptorHandle();
		const auto gpuHandle = buffer->GetUavHandle().GetGpuDescriptorHandle();
		(*this)->ClearUnorderedAccessViewUint(gpuHandle, cpuHandle, buffer->GetDxObjectPtr(), clearValue, 0, nullptr);
	}

	void Dx12GraphicsCommandList::ClearUnorderedAccessFloat(const Dx12UnorderedAccessBuffer* buffer, const FLOAT clearValue[4]) const
	{
		const auto cpuHandle = buffer->GetUavHandle().GetCpuDescriptorHandle();
		const auto gpuHandle = buffer->GetUavHandle().GetGpuDescriptorHandle();
		(*this)->ClearUnorderedAccessViewFloat(gpuHandle, cpuHandle, buffer->GetDxObjectPtr(), clearValue, 0, nullptr);
	}

	void Dx12GraphicsCommandList::SetVertexBuffer(const D3D12_VERTEX_BUFFER_VIEW& vbView) const
	{
		(*this)->IASetVertexBuffers(0, 1, &vbView);
	}

	void Dx12GraphicsCommandList::SetIndexBuffer(const D3D12_INDEX_BUFFER_VIEW& ibView) const
	{
		(*this)->IASetIndexBuffer(&ibView);
	}

	void Dx12GraphicsCommandList::SetMeshBuffer(const Dx12MeshBuffer* buffer) const
	{
		SetVertexBuffer(buffer->GetVertexBufferView());
		SetIndexBuffer(buffer->GetIndexBufferView());
	}

	void Dx12GraphicsCommandList::SetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY primitiveTopology) const
	{
		(*this)->IASetPrimitiveTopology(primitiveTopology);
	}

	void Dx12GraphicsCommandList::SetViewport(const D3D12_VIEWPORT& viewport) const
	{
		(*this)->RSSetViewports(1, &viewport);
	}

	void Dx12GraphicsCommandList::SetViewport(FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT minDepth, FLOAT maxDepth) const
	{
		D3D12_VIEWPORT t_viewport;
		t_viewport.TopLeftX = x;
		t_viewport.TopLeftY = y;
		t_viewport.Width = width;
		t_viewport.Height = height;
		t_viewport.MinDepth = minDepth;
		t_viewport.MaxDepth = maxDepth;
		(*this)->RSSetViewports(1, &t_viewport);
	}

	void Dx12GraphicsCommandList::SetScissorRect(const D3D12_RECT& rect) const
	{
		(*this)->RSSetScissorRects(1, &rect);
	}

	void Dx12GraphicsCommandList::SetScissorRect(LONG left, LONG top, LONG right, LONG bottom) const
	{
		D3D12_RECT rect;
		rect.left = left;
		rect.top = top;
		rect.right = right;
		rect.bottom = bottom;
		(*this)->RSSetScissorRects(1, &rect);
	}

	void Dx12GraphicsCommandList::SetBlendFactor(const FLOAT BlendFactor[4]) const
	{
		(*this)->OMSetBlendFactor(BlendFactor);
	}

	void Dx12GraphicsCommandList::SetRenderTarget(const Dx12RenderTargetBuffer* rtBuffer, const Dx12DepthStencilBuffer* dsBuffer) const
	{
		const auto rtvHandle = rtBuffer->GetRtvHandle().GetCpuDescriptorHandle();
		const auto dsvHandle = dsBuffer->GetDsvHandle().GetCpuDescriptorHandle();

		(*this)->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);
	}

	void Dx12GraphicsCommandList::SetRenderTargets(UINT renderTargetNum, const Dx12RenderTargetBuffer* rtBuffer[], const Dx12DepthStencilBuffer* dsBuffer) const
	{
		const auto dsvHandle = dsBuffer->GetDsvHandle().GetCpuDescriptorHandle();
		auto rtvHandleList = std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>(renderTargetNum);

		for (UINT i = 0; i < renderTargetNum; i++)
		{
			rtvHandleList.push_back(rtBuffer[i]->GetRtvHandle().GetCpuDescriptorHandle());
		}

		(*this)->OMSetRenderTargets(renderTargetNum, rtvHandleList.data(), false, &dsvHandle);
	}

	void Dx12GraphicsCommandList::SetStencilRef(UINT stencilRef) const
	{
		(*this)->OMSetStencilRef(stencilRef);
	}

	void Dx12GraphicsCommandList::DrawInstanced(UINT vertexNumPerInstance, UINT instanceNum, UINT startVertexLocation, UINT startInstanceLocation) const
	{
		(*this)->DrawInstanced(vertexNumPerInstance, instanceNum, startVertexLocation, startInstanceLocation);
	}

	void Dx12GraphicsCommandList::DrawIndexedInstanced(UINT indexNumPerInstance, UINT instanceNum, UINT startIndexLocation, INT baseVertexLocation, UINT startInstanceLocation) const
	{
		(*this)->DrawIndexedInstanced(indexNumPerInstance, instanceNum, startInstanceLocation, baseVertexLocation, startInstanceLocation);
	}

	void Dx12GraphicsCommandList::SetGraphicsPipelineState(const Dx12GraphicsPipelineState* pipelineState) const
	{
		(*this)->SetPipelineState(pipelineState->GetDxObjectPtr());
	}

	void Dx12GraphicsCommandList::SetGraphicsRootSignature(Dx12RootSignature* rootSignature)
	{
		m_rootSignature = rootSignature;
		(*this)->SetGraphicsRootSignature(rootSignature->GetDxObjectPtr());
	}

	void Dx12GraphicsCommandList::SetGraphicsRootConstant(UINT parameterIndex, UINT data, UINT offset) const
	{
		if (m_rootSignature->GetParameterType(parameterIndex) != D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS)
		{
			ThrowWithErrName(DxLogicError, "the parameter type is not match");
		}
		(*this)->SetGraphicsRoot32BitConstant(parameterIndex, data, offset);
	}

	void Dx12GraphicsCommandList::SetGraphicsRootConstants(UINT parameterIndex, UINT dataNum, const UINT* data, UINT offset) const
	{
		if (m_rootSignature->GetParameterType(parameterIndex) != D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS)
		{
			ThrowWithErrName(DxLogicError, "the parameter type is not match");
		}
		(*this)->SetGraphicsRoot32BitConstants(parameterIndex, dataNum, data, offset);
	}

	void Dx12GraphicsCommandList::SetGraphicsRootCbv(UINT parameterIndex, const Dx12ConstantBuffer* buffer) const
	{
		if (m_rootSignature->GetParameterType(parameterIndex) != D3D12_ROOT_PARAMETER_TYPE_CBV)
		{
			ThrowWithErrName(DxLogicError, "the parameter type is not match");
		}
		(*this)->SetGraphicsRootConstantBufferView(parameterIndex, buffer->GetGpuVirtualAddress());
	}

	void Dx12GraphicsCommandList::SetGraphicsRootSrv(UINT parameterIndex, const Dx12ShaderResourceBuffer* buffer) const
	{
		if (m_rootSignature->GetParameterType(parameterIndex) != D3D12_ROOT_PARAMETER_TYPE_SRV)
		{
			ThrowWithErrName(DxLogicError, "the parameter type is not match");
		}
		(*this)->SetGraphicsRootShaderResourceView(parameterIndex, buffer->GetGpuVirtualAddress());
	}

	void Dx12GraphicsCommandList::SetGraphicsRootUav(UINT parameterIndex, const Dx12UnorderedAccessBuffer* buffer) const
	{
		if (m_rootSignature->GetParameterType(parameterIndex) != D3D12_ROOT_PARAMETER_TYPE_UAV)
		{
			ThrowWithErrName(DxLogicError, "the parameter type is not match");
		}
		(*this)->SetGraphicsRootUnorderedAccessView(parameterIndex, buffer->GetGpuVirtualAddress());
	}

	void Dx12GraphicsCommandList::SetGraphicsRootDescriptorTable(UINT parameterIndex, const Dx12DescriptorHandle& handle) const
	{
		if (m_rootSignature->GetParameterType(parameterIndex) != D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE)
		{
			ThrowWithErrName(DxLogicError, "the parameter type is not match");
		}
		(*this)->SetGraphicsRootDescriptorTable(parameterIndex, handle.GetGpuDescriptorHandle());
	}
}
