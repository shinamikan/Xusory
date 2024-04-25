#include "../CommandContext.h"
#include "../RhiManager.h"
#include "../Material.h"
#include "../Mesh.h"

namespace XusoryEngine
{
	void GiDx12CommandContext::InitCommandContext(RhiManager* graphicsManager)
	{
		m_dx12Manager = dynamic_cast<GiDx12RhiManager*>(graphicsManager);
		m_commandList = m_dx12Manager->m_commandList.get();
	}

	void GiDx12CommandContext::BeginCommand()
	{
		m_dx12Manager->m_commandAllocator->ReSetCommandAllocator();
		m_commandList->ResetCommandList(m_dx12Manager->m_commandAllocator.get(), nullptr);

		m_commandList->SetViewport(m_dx12Manager->m_screenViewport);
		m_commandList->SetScissorRect(m_dx12Manager->m_scissorRect);

		const UINT currentBackBufferIndex = m_dx12Manager->m_swapChain->GetCurrentBackBufferIndex();
		m_currentBackBuffer = m_dx12Manager->m_backBufferList[currentBackBufferIndex].get();
		m_commandList->TranslationBufferState(m_currentBackBuffer, D3D12_RESOURCE_STATE_RENDER_TARGET);

		m_commandList->SetRenderTarget(m_currentBackBuffer, m_dx12Manager->m_depthStencilBuffer.get());

		if (m_dx12Manager->m_runTimeCbvSrvUavHeap->GetHeapSize() != 0)
		{
			m_commandList->SetDescriptorHeaps(m_dx12Manager->m_runTimeCbvSrvUavHeap.get(), nullptr);
		}
	}

	void GiDx12CommandContext::EndCommand()
	{
		m_commandList->TranslationBufferState(m_currentBackBuffer, D3D12_RESOURCE_STATE_PRESENT);

		m_dx12Manager->ExecuteCommandAndWait();
		m_dx12Manager->PresentBackBuffer();

		m_activeMesh = nullptr;
		m_activeShader = nullptr;
	}

	void GiDx12CommandContext::ClearRenderTarget(Float4 color)
	{
		m_commandList->ClearRenderTarget(m_currentBackBuffer, reinterpret_cast<FLOAT*>(&color));
	}

	void GiDx12CommandContext::ClearDepth(FLOAT depth)
	{
		m_commandList->ClearDepth(m_dx12Manager->m_depthStencilBuffer.get(), depth);
	}

	void GiDx12CommandContext::ClearStencil(UINT8 stencil)
	{
		m_commandList->ClearStencil(m_dx12Manager->m_depthStencilBuffer.get(), stencil);
	}

	void GiDx12CommandContext::DrawMesh()
	{
		m_commandList->DrawIndexedInstanced(m_activeMesh->GetIndicesNum(), 1, 0, 0, 0);
	}

	void GiDx12CommandContext::SetMaterial(const Material* material)
	{
		const auto* shader = material->GetShader();
		auto& [rootSignature, pipelineState] = m_dx12Manager->m_shaderPipelineStateMap.at(const_cast<Shader*>(shader));

		if (m_activeShader != shader)
		{
			m_activeShader = shader;

			m_commandList->SetGraphicsRootSignature(rootSignature.get());
			m_commandList->SetGraphicsPipelineState(pipelineState.get());
		}

		UINT rootParameterIndex = 0;
		for (const auto& cBuffer : material->m_constantBufferList)
		{
			const auto* dxCBuffer = m_dx12Manager->m_constantBufferMap.at(cBuffer.get()).get();
			dxCBuffer->CopyDataToBuffer(cBuffer.get());
			m_commandList->SetGraphicsRootCbv(rootParameterIndex, dxCBuffer);

			rootParameterIndex++;
		}

		if (material->GetTexturePropertyNum() == 0)
		{
			return;
		}

		const UINT runtimeHeapIndex = m_dx12Manager->GetRuntimeResourceHeapIndex();
		for (UINT textureIndex = material->GetConstantPropertyNum(); textureIndex < rootSignature->GetParameterNum(); textureIndex++)
		{
			const Texture* texture = material->GetTextureByIndex(textureIndex);
			const auto* dxTexBuffer = m_dx12Manager->m_textureMap.at(const_cast<Texture*>(texture)).get();

			const auto* srcHeap = m_dx12Manager->m_cbvSrvUavAllocator->GetHeap();
			const INT srcHeapIndex = srcHeap->FindDescriptor(dxTexBuffer->GetTextureBuffer()->GetSrvHandle());
			Dx12DescriptorHeap::CopyDescriptor(m_dx12Manager->m_device.get(), m_dx12Manager->m_runTimeCbvSrvUavHeap.get(), m_dx12Manager->GetRuntimeResourceHeapIndex(),
				srcHeap, static_cast<UINT>(srcHeapIndex), 1);

			m_dx12Manager->AddRuntimeResourceHeapIndex(1);
		}

		m_commandList->SetGraphicsRootDescriptorTable(rootParameterIndex, (*m_dx12Manager->m_runTimeCbvSrvUavHeap)[runtimeHeapIndex]);
	}

	void GiDx12CommandContext::SetMesh(const Mesh* mesh)
	{
		if (m_activeMesh != mesh)
		{
			m_activeMesh = mesh;

			const auto* meshBuffer = m_dx12Manager->m_meshBufferMap.at(const_cast<Mesh*>(mesh)).get();
			m_commandList->SetMeshBuffer(meshBuffer);
			m_commandList->SetPrimitiveTopology(static_cast<D3D12_PRIMITIVE_TOPOLOGY>(mesh->GetPrimitiveTopology()));
		}
	}
}
