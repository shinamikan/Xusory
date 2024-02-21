#include "../GraphicsManager.h"
#include "../Shader.h"

namespace XusoryEngine
{
	GraphicsLibrary GraphicsManager::GetGraphicsLibrary() const
	{
		return m_graphicsLibrary;
	}

	GiDx12GraphicsManager::GiDx12GraphicsManager() : GraphicsManager(GraphicsLibrary::Direct3D_12) { }

	void GiDx12GraphicsManager::InitGraphicsObject(void* renderWindow)
	{
		CreateFactoryAndDevice();
		CreateCommonObjects();
		CreateDescriptorAllocator();
		CreateSwapChain(static_cast<WinId>(renderWindow));
		CreateInputLayout();
		CreateCommonRootSignature();

		Resize(1, 1);
	}

	void GiDx12GraphicsManager::Resize(UINT width, UINT height)
	{
		m_commandQueue->SignalAndWaitForNextFence(m_fence.get());
		m_commandList->ResetCommandList(m_commandAllocator.get(), nullptr);

		if (m_backBufferList.size() == 0 || !m_depthStencilBuffer)
		{
			m_backBufferList.resize(2);
			for (auto& rtBuffer : m_backBufferList)
			{
				rtBuffer = std::make_unique<Dx12RenderTargetBuffer>();
			}
			m_depthStencilBuffer = std::make_unique<Dx12DepthStencilBuffer>();
		}

		for (const auto& rtBuffer : m_backBufferList)
		{
			rtBuffer->ReSetBuffer(m_rtvAllocator.get());
		}
		m_depthStencilBuffer->ReSetBuffer(m_dsvAllocator.get());
		m_swapChain->ResizeBuffer(width, height);

		for (UINT i = 0; i < m_backBufferList.size(); i++)
		{
			m_backBufferList[i]->CreateFromSwapChain(m_swapChain.get(), i);
			m_backBufferList[i]->DescribeAsRtv(m_device.get(), m_rtvAllocator.get());
		}
		m_depthStencilBuffer->CreateDepthStencilBuffer(m_device.get(), D3D12_RESOURCE_STATE_COMMON, 1.0f, 0, width, height);
		m_depthStencilBuffer->DescribeAsDsv(m_device.get(), m_dsvAllocator.get());

		m_commandList->TranslationBufferState(m_depthStencilBuffer.get(), D3D12_RESOURCE_STATE_DEPTH_WRITE, false);
		m_commandList->EndCommand();

		m_commandQueue->ExecuteCommandList({ m_commandList.get() });
		m_commandQueue->SignalAndWaitForNextFence(m_fence.get());

		m_screenViewport.TopLeftX = 0;
		m_screenViewport.TopLeftY = 0;
		m_screenViewport.Width = static_cast<FLOAT>(width);
		m_screenViewport.Height = static_cast<FLOAT>(height);
		m_screenViewport.MinDepth = 0.0f;
		m_screenViewport.MaxDepth = 1.0f;

		m_scissorRect = { 0, 0, static_cast<LONG>(width), static_cast<LONG>(height) };
	}

	void GiDx12GraphicsManager::BuildShader(const Shader* shader)
	{
		DxShaderCompiler shaderCompiler;
		shaderCompiler.CompileShader(shader->GetShaderFilePath(), shader->GetShaderEntryPoint(), nullptr);

		const auto rootSignature = new Dx12RootSignature;
		for (const auto& cBufferDesc : shaderCompiler.m_constantBufferDescMap)
		{
			rootSignature->AddConstantBufferView(cBufferDesc.first.bindPoint, cBufferDesc.first.space);
		}
		for (const auto& resourceDesc : shaderCompiler.m_shaderResourceDescList)
		{
			rootSignature->AddDescriptorRange(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, resourceDesc.BindPoint, resourceDesc.Space);
		}
		rootSignature->AddDescriptorTable();
		rootSignature->AddStaticSampler(0, D3D12_FILTER_MIN_MAG_MIP_LINEAR, D3D12_TEXTURE_ADDRESS_MODE_WRAP);
		rootSignature->Create(m_device.get());

		const auto pipelineState = new Dx12GraphicsPipelineState;
		pipelineState->SetInputLayout({ m_inputLayoutList.data(), static_cast<UINT>(m_inputLayoutList.size()) });
		pipelineState->SetRootSignature(rootSignature);

		if (auto* vertexShader = shaderCompiler.GetVertexShader(); vertexShader != nullptr) pipelineState->SetVertexShader(vertexShader->GetBufferPointer(), vertexShader->GetBufferSize());
		if (auto* pixelShader = shaderCompiler.GetPixelShader(); pixelShader != nullptr) pipelineState->SetPixelShader(pixelShader->GetBufferPointer(), pixelShader->GetBufferSize());
		if (auto* domainShader = shaderCompiler.GetDomainShader(); domainShader != nullptr) pipelineState->SetDomainShader(domainShader->GetBufferPointer(), domainShader->GetBufferSize());
		if (auto* hullShader = shaderCompiler.GetHullShader(); hullShader != nullptr) pipelineState->SetHullShader(hullShader->GetBufferPointer(), hullShader->GetBufferSize());
		if (auto* geometryShader = shaderCompiler.GetGeometryShader(); geometryShader != nullptr) pipelineState->SetGeometryShader(geometryShader->GetBufferPointer(), geometryShader->GetBufferSize());

		pipelineState->SetBlendState(CD3DX12_BLEND_DESC(D3D12_DEFAULT));
		pipelineState->SetDepthStencilState(CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT));
		pipelineState->SetFillMode(static_cast<D3D12_FILL_MODE>(shader->GetFillMode()));
		pipelineState->SetCullMode(static_cast<D3D12_CULL_MODE>(shader->GetCullMode()));
		pipelineState->SetFrontCounterClockwise(static_cast<BOOL>(shader->GetTriangleWindingOrder()));

		pipelineState->SetPrimitiveTopologyType(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE);
		pipelineState->SetRenderTargetNum(1);
		pipelineState->SetRenderTargetFormat(m_swapChain->GetFormat());
		pipelineState->SetDepthFormat(m_depthStencilBuffer->GetFormat());
		pipelineState->Create(m_device.get());

		m_shaderPipelineStateMap.emplace(shader, std::make_pair(rootSignature, pipelineState));
	}

	void GiDx12GraphicsManager::Render()
	{
		m_commandAllocator->ReSetCommandAllocator();
		m_commandList->ResetCommandList(m_commandAllocator.get(), nullptr);

		auto* currentBackBuffer = m_backBufferList[m_swapChain->GetCurrentBackBufferIndex()].get();
		m_commandList->TranslationBufferState(currentBackBuffer, D3D12_RESOURCE_STATE_RENDER_TARGET);

		m_commandList->SetViewport(m_screenViewport);
		m_commandList->SetScissorRect(m_scissorRect);

		m_commandList->ClearRenderTarget(currentBackBuffer, DirectX::Colors::LightSteelBlue);
		m_commandList->ClearDepthStencil(m_depthStencilBuffer.get(), 1.0f, 0);

		m_commandList->SetRenderTarget(currentBackBuffer, m_depthStencilBuffer.get());

		m_commandList->TranslationBufferState(currentBackBuffer, D3D12_RESOURCE_STATE_PRESENT, false);

		m_commandList->EndCommand();
		m_commandQueue->ExecuteCommandList({ m_commandList.get() });

		m_swapChain->Present(0);

		m_commandQueue->SignalAndWaitForNextFence(m_fence.get());
	}

	void GiDx12GraphicsManager::CreateFactoryAndDevice()
	{
		m_factory = std::make_unique<DxFactory>();
		m_device = std::make_unique<Dx12Device>();

		m_factory->Create();
		m_device->Create(m_factory.get());
	}

	void GiDx12GraphicsManager::CreateCommonObjects()
	{
		m_commandAllocator = std::make_unique<Dx12CommandAllocator>();
		m_commandQueue = std::make_unique<Dx12CommandQueue>();
		m_commandList = std::make_unique<Dx12GraphicsCommandList>();

		m_commandAllocator->Create(m_device.get(), D3D12_COMMAND_LIST_TYPE_DIRECT);
		m_commandQueue->Create(m_device.get(), D3D12_COMMAND_LIST_TYPE_DIRECT);
		m_commandList->Create(m_device.get(), m_commandAllocator.get(), D3D12_COMMAND_LIST_TYPE_DIRECT);

		m_commandList->EndCommand();

		m_fence = std::make_unique<Dx12Fence>();
		m_fence->Create(m_device.get());
	}

	void GiDx12GraphicsManager::CreateDescriptorAllocator()
	{
		m_cbvSrvUavAllocator = std::make_unique<Dx12DescriptorAllocator>(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, true);
		m_rtvAllocator = std::make_unique<Dx12DescriptorAllocator>(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, false);
		m_dsvAllocator = std::make_unique<Dx12DescriptorAllocator>(D3D12_DESCRIPTOR_HEAP_TYPE_DSV, false);
	}

	void GiDx12GraphicsManager::CreateSwapChain(const WinId& winId)
	{
		m_swapChain = std::make_unique<DxSwapChain>();
		m_swapChain->Create(m_factory.get(), m_commandQueue.get()->GetDxObjectPtr(), winId, 1, 1, DXGI_FORMAT_R8G8B8A8_UNORM, 2);
	}

	void GiDx12GraphicsManager::CreateInputLayout()
	{
		m_inputLayoutList =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 36, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 52, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 0, 60, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 2, DXGI_FORMAT_R32G32_FLOAT, 0, 68, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 3, DXGI_FORMAT_R32G32_FLOAT, 0, 76, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 4, DXGI_FORMAT_R32G32_FLOAT, 0, 84, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};
	}

	void GiDx12GraphicsManager::CreateCommonRootSignature()
	{
		m_commonRootSignature = std::make_unique<Dx12RootSignature>();
		m_commonRootSignature->AddDescriptorRange(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);
		m_commonRootSignature->AddDescriptorRange(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 1);
		m_commonRootSignature->AddDescriptorTable();
		m_commonRootSignature->AddConstantBufferView(1);
		m_commonRootSignature->AddStaticSampler(0, D3D12_FILTER_MIN_MAG_MIP_LINEAR, D3D12_TEXTURE_ADDRESS_MODE_WRAP);
		m_commonRootSignature->Create(m_device.get());
	}
}
