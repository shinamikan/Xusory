#include "../CommandContext.h"
#include "../GraphicsManager.h"

namespace XusoryEngine
{
	void GiDx12CommandContext::InitCommandContext(const GraphicsManager* graphicsManager)
	{
		m_dx12Manager = dynamic_cast<const GiDx12GraphicsManager*>(graphicsManager);
	}

	void GiDx12CommandContext::BeginCommand()
	{
		m_dx12Manager->m_commandAllocator->ReSetCommandAllocator();
		m_dx12Manager->m_commandList->ResetCommandList(m_dx12Manager->m_commandAllocator.get(), nullptr);

		const UINT currentBackBufferIndex = m_dx12Manager->m_swapChain->GetCurrentBackBufferIndex();
		m_currentBackBuffer = m_dx12Manager->m_backBufferList[currentBackBufferIndex].get();
		m_dx12Manager->m_commandList->TranslationBufferState(m_currentBackBuffer, D3D12_RESOURCE_STATE_RENDER_TARGET);

		m_dx12Manager->m_commandList->SetRenderTarget(m_currentBackBuffer, m_dx12Manager->m_depthStencilBuffer.get());
	}

	void GiDx12CommandContext::EndCommand()
	{
		m_dx12Manager->m_commandList->TranslationBufferState(m_currentBackBuffer, D3D12_RESOURCE_STATE_PRESENT, false);
		m_dx12Manager->m_commandList->EndCommand();

		m_dx12Manager->m_commandQueue->ExecuteCommandList({ m_dx12Manager->m_commandList.get() });
		m_dx12Manager->m_swapChain->Present(0);
		m_dx12Manager->m_commandQueue->SignalAndWaitForNextFence(m_dx12Manager->m_fence.get());
	}

	void GiDx12CommandContext::ClearRenderTarget(BOOL ifClearRenderTarget, BOOL ifClearDepth, Float4 color, FLOAT depth)
	{
		if (ifClearRenderTarget)
		{
			m_dx12Manager->m_commandList->ClearRenderTarget(m_currentBackBuffer, reinterpret_cast<FLOAT*>(&color));
		}
		if (ifClearDepth)
		{
			m_dx12Manager->m_commandList->ClearDepthStencil(m_dx12Manager->m_depthStencilBuffer.get(), depth, 0);
		}
	}
}
