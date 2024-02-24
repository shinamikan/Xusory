#include "../CommandContext.h"
#include "../GraphicsManager.h"
#include "../Material.h"
#include "../Mesh.h"

namespace XusoryEngine
{
	void GiDx12CommandContext::InitCommandContext(const GraphicsManager* graphicsManager)
	{
		m_dx12Manager = dynamic_cast<const GiDx12GraphicsManager*>(graphicsManager);
		m_commandList = m_dx12Manager->m_commandList.get();
	}

	void GiDx12CommandContext::BeginCommand()
	{
		m_dx12Manager->m_commandAllocator->ReSetCommandAllocator();
		m_commandList->ResetCommandList(m_dx12Manager->m_commandAllocator.get(), nullptr);

		const UINT currentBackBufferIndex = m_dx12Manager->m_swapChain->GetCurrentBackBufferIndex();
		m_currentBackBuffer = m_dx12Manager->m_backBufferList[currentBackBufferIndex].get();
		m_commandList->TranslationBufferState(m_currentBackBuffer, D3D12_RESOURCE_STATE_RENDER_TARGET);

		m_commandList->SetRenderTarget(m_currentBackBuffer, m_dx12Manager->m_depthStencilBuffer.get());
	}

	void GiDx12CommandContext::EndCommand()
	{
		m_commandList->TranslationBufferState(m_currentBackBuffer, D3D12_RESOURCE_STATE_PRESENT, false);
		m_commandList->EndCommand();

		m_dx12Manager->m_commandQueue->ExecuteCommandList({ m_dx12Manager->m_commandList.get() });
		m_dx12Manager->m_swapChain->Present(0);
		m_dx12Manager->m_commandQueue->SignalAndWaitForNextFence(m_dx12Manager->m_fence.get());
	}

	void GiDx12CommandContext::ClearRenderTarget(BOOL ifClearRenderTarget, BOOL ifClearDepth, Float4 color, FLOAT depth)
	{
		if (ifClearRenderTarget)
		{
			m_commandList->ClearRenderTarget(m_currentBackBuffer, reinterpret_cast<FLOAT*>(&color));
		}
		if (ifClearDepth)
		{
			m_commandList->ClearDepthStencil(m_dx12Manager->m_depthStencilBuffer.get(), depth, 0);
		}
	}

	void GiDx12CommandContext::DrawRenderer(const Material* material, const Mesh* mesh)
	{
		auto& [rootSignature, pipelineState] = m_dx12Manager->m_shaderPipelineStateMap.at(const_cast<Shader*>(material->GetShader()));
		m_commandList->SetGraphicsRootSignature(rootSignature.get());
		m_commandList->SetGraphicsPipelineState(pipelineState.get());

		const auto* meshBuffer = m_dx12Manager->m_meshBufferMap.at(const_cast<Mesh*>(mesh)).get();
		m_commandList->SetMeshBuffer(meshBuffer);
		m_commandList->SetPrimitiveTopology(static_cast<D3D12_PRIMITIVE_TOPOLOGY>(mesh->primitiveTopology));

		UINT parameterIndex = 0;
		for (const auto& cBuffer : material->m_constantBufferList)
		{
			const auto* dxCBuffer = m_dx12Manager->m_constantBufferMap.at(cBuffer.get()).get();
			m_commandList->SetGraphicsRootCbv(parameterIndex, dxCBuffer);

			parameterIndex++;
		}

		m_commandList->DrawIndexedInstanced(mesh->GetIndicesNum(), 1, 0, 0, 0);
	}
}
