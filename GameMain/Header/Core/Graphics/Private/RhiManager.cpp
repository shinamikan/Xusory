#include "../RhiManager.h"
#include "../Common/GraphicsDefine.h"
#include "../Material.h"
#include "../Mesh.h"
#include "../Shader.h"
#include "../Texture.h"

namespace XusoryEngine
{
	GraphicsLibrary RhiManager::GetGraphicsLibrary() const
	{
		return m_graphicsLibrary;
	}

	GiDx12RhiManager::GiDx12RhiManager() : RhiManager(GraphicsLibrary::Direct3D_12) { }

	void GiDx12RhiManager::InitGraphicsObject(void* renderWindow)
	{
		CreateInputLayout();
		CreateFactoryAndDevice();
		CreateCommonObjects();
		CreateSwapChain(static_cast<WinId>(renderWindow));
		CreateDescriptorAllocator();

		Resize(1, 1);
	}

	void GiDx12RhiManager::Resize(UINT width, UINT height)
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
			rtBuffer->ReSetBuffer(m_rtvAllocator.get(), m_cbvSrvUavAllocator.get());
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

		m_commandList->TranslationBufferState(m_depthStencilBuffer.get(), D3D12_RESOURCE_STATE_DEPTH_WRITE);
		
		ExecuteCommandAndWait();

		m_screenViewport.TopLeftX = 0;
		m_screenViewport.TopLeftY = 0;
		m_screenViewport.Width = static_cast<FLOAT>(width);
		m_screenViewport.Height = static_cast<FLOAT>(height);
		m_screenViewport.MinDepth = 0.0f;
		m_screenViewport.MaxDepth = 1.0f;

		m_scissorRect = { 0, 0, static_cast<LONG>(width), static_cast<LONG>(height) };
	}

	void GiDx12RhiManager::ReSetRuntimeResourceHeap(UINT heapNum)
	{
		m_runTimeResourceHeapIndex = 0;

		m_runTimeCbvSrvUavHeap->ReSet();
		m_runTimeCbvSrvUavHeap->Create(m_device.get(), heapNum);
	}

	UINT GiDx12RhiManager::GetRuntimeResourceHeapIndex()
	{
		return m_runTimeResourceHeapIndex;
	}

	void GiDx12RhiManager::AddRuntimeResourceHeapIndex(UINT resourceNum)
	{
		m_runTimeResourceHeapIndex += resourceNum;
	}

	void GiDx12RhiManager::ExecuteCommandAndWait()
	{
		m_commandList->EndCommand();
		m_commandQueue->ExecuteCommandList({ m_commandList.get() });
		m_commandQueue->SignalAndWaitForNextFence(m_fence.get());
	}

	void GiDx12RhiManager::ReSetCommandList()
	{
		m_commandList->ResetCommandList(m_commandAllocator.get(), nullptr);
	}

	void GiDx12RhiManager::PresentBackBuffer()
	{
		m_swapChain->Present(0);
	}

	void GiDx12RhiManager::BuildMaterial(Material* material)
	{
		if (IsMaterialBuilt(material))
		{
			return;
		}

		const auto* shader = material->GetShader();

		for (UINT i = 0; i < shader->GetCBufferCount(); i++)
		{
			auto& property = shader->GetCBufferProperty(i);

			auto* uploadBuffer = new Dx12UploadBuffer(true);
			uploadBuffer->CreateUploadBuffer(m_device.get(), property.size);

			m_constantBufferMap.emplace(material->m_constantBufferList.at(i).get(), uploadBuffer);
		}
	}

	void GiDx12RhiManager::BuildMesh(Mesh* mesh)
	{
		if (IsMeshBuilt(mesh))
		{
			return;
		}

		auto& vertices = mesh->GetVertices();
		auto& indices = mesh->GetIndices();

		auto* meshBuffer = new Dx12MeshBuffer;
		meshBuffer->CreateMeshBuffer(m_device.get(), static_cast<UINT>(vertices.size()), sizeof(Vertex),
			static_cast<UINT>(indices.size()), static_cast<DXGI_FORMAT>(mesh->GetIndexFormat()));
		meshBuffer->UploadMeshResource(m_commandList.get(), vertices.data(), indices.data());

		m_meshBufferMap.emplace(mesh, meshBuffer);
	}

	void GiDx12RhiManager::BuildShader(Shader* shader)
	{
		if (IsShaderBuilt(shader))
		{
			return;
		}

		auto* rootSignature = new Dx12RootSignature;

		UINT shaderPropertyIndex = 0;
		for (UINT i = 0; i < shader->GetCBufferCount(); i++)
		{
			auto& cBufferProperty = shader->GetCBufferProperty(i);
			rootSignature->AddConstantBufferView(cBufferProperty.slot, cBufferProperty.space);

			shaderPropertyIndex += cBufferProperty.variableNum;
		}
		for (; shaderPropertyIndex < shader->GetPropertyCount(); shaderPropertyIndex++)
		{
			auto& shaderProperty = shader->GetPropertyByIndex(shaderPropertyIndex);
			rootSignature->AddDescriptorRange(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, shaderProperty.slot, shaderProperty.space);
		}
		
		if (!rootSignature->IsRangeTempListNull())
		{
			rootSignature->AddDescriptorTable();
		}
		rootSignature->AddStaticSampler(0, D3D12_FILTER_MIN_MAG_MIP_LINEAR, D3D12_TEXTURE_ADDRESS_MODE_WRAP);
		rootSignature->Create(m_device.get());

		auto* pipelineState = new Dx12GraphicsPipelineState;
		pipelineState->SetInputLayout({ m_inputLayoutList.data(), static_cast<UINT>(m_inputLayoutList.size()) });
		pipelineState->SetRootSignature(rootSignature);

		if (const auto& vertexShader = shader->m_shaderByteList.at(0); vertexShader.byteSize != NULL) pipelineState->SetVertexShader(vertexShader.byteCode.data(), vertexShader.byteSize);
		if (const auto& pixelShader = shader->m_shaderByteList.at(1); pixelShader.byteSize != NULL) pipelineState->SetPixelShader(pixelShader.byteCode.data(), pixelShader.byteSize);
		if (const auto& domainShader = shader->m_shaderByteList.at(2); domainShader.byteSize != NULL) pipelineState->SetDomainShader(domainShader.byteCode.data(), domainShader.byteSize);
		if (const auto& hullShader = shader->m_shaderByteList.at(3); hullShader.byteSize != NULL) pipelineState->SetHullShader(hullShader.byteCode.data(), hullShader.byteSize);
		if (const auto& geometryShader = shader->m_shaderByteList.at(4); geometryShader.byteSize != NULL) pipelineState->SetGeometryShader(geometryShader.byteCode.data(), geometryShader.byteSize);

		pipelineState->SetBlendState(CD3DX12_BLEND_DESC(D3D12_DEFAULT));
		pipelineState->SetDepthStencilState(CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT));
		pipelineState->SetFillMode(static_cast<D3D12_FILL_MODE>(shader->GetGraphicsFillMode()));
		pipelineState->SetCullMode(static_cast<D3D12_CULL_MODE>(shader->GetGraphicsCullMode()));
		pipelineState->SetFrontCounterClockwise(static_cast<BOOL>(shader->GetTriangleWindingOrder()));

		pipelineState->SetPrimitiveTopologyType(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE);
		pipelineState->SetRenderTargetNum(1);
		pipelineState->SetRenderTargetFormat(m_swapChain->GetFormat());
		pipelineState->SetDepthFormat(m_depthStencilBuffer->GetFormat());
		pipelineState->Create(m_device.get());

		m_shaderPipelineStateMap.emplace(shader, std::make_pair(rootSignature, pipelineState));
		shader->m_shaderByteList.clear();
	}

	void GiDx12RhiManager::BuildTexture(Texture* texture)
	{
		if (IsTextureBuilt(texture))
		{
			return;
		}

		auto* textureBuffer = new Dx12TextureBuffer;
		const auto textureNameW = StringEx::StringToWString(texture->GetName());

		const auto pathListTemp = StringEx::SplitView<std::string>(texture->m_name, "/");
		texture->m_name = StringEx::SplitView<std::string>(*(pathListTemp.end() - 1), ".").at(0);

		if (StringEx::EndWith<std::wstring>(textureNameW, TEXT(".dds")))
		{
			DxTextureLoader::LoadDdsTextureFile(textureNameW, m_device.get(), m_commandList.get(),
				const_cast<Dx12ShaderResourceBuffer*>(textureBuffer->GetTextureBuffer()), const_cast<Dx12Buffer*>(textureBuffer->GetTextureUploadBuffer()));

			const auto desc = (*textureBuffer->GetTextureBuffer())->GetDesc();
			texture->m_width = static_cast<UINT>(desc.Width);
			texture->m_height = desc.Height;

			textureBuffer->DescribeShaderResource(m_device.get(), m_cbvSrvUavAllocator.get());
		}

		m_textureMap.emplace(texture, textureBuffer);
	}

	BOOL GiDx12RhiManager::IsMaterialBuilt(Material* material)
	{
		const auto* shader = material->GetShader();

		if (material->m_constantBufferList.empty())
		{
			return false;
		}

		for (UINT i = 0; i < shader->GetCBufferCount(); i++)
		{
			if (m_constantBufferMap.find(material->m_constantBufferList.at(i).get()) == m_constantBufferMap.end())
			{
				return false;
			}
		}

		return true;
	}

	BOOL GiDx12RhiManager::IsMeshBuilt(Mesh* mesh)
	{
		return m_meshBufferMap.find(mesh) != m_meshBufferMap.end();
	}

	BOOL GiDx12RhiManager::IsTextureBuilt(Texture* texture)
	{
		return m_textureMap.find(texture) != m_textureMap.end();
	}

	BOOL GiDx12RhiManager::IsShaderBuilt(Shader* shader)
	{
		return m_shaderPipelineStateMap.find(shader) != m_shaderPipelineStateMap.end();
	}

	void GiDx12RhiManager::DestroyMaterial(Material* material)
	{
		material->BindShader();
		const auto* shader = material->GetShader();

		for (UINT i = 0; i < shader->GetCBufferCount(); i++)
		{
			m_constantBufferMap.erase(material->m_constantBufferList.at(i).get());
		}
	}

	void GiDx12RhiManager::DestroyMesh(Mesh* mesh)
	{
		m_meshBufferMap.erase(mesh);
	}

	void GiDx12RhiManager::DestroyTexture(Texture* texture)
	{
		m_textureMap.erase(texture);
	}

	void GiDx12RhiManager::DestroyShader(Shader* shader)
	{
		m_shaderPipelineStateMap.erase(shader);
	}

	void GiDx12RhiManager::CreateInputLayout()
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

	void GiDx12RhiManager::CreateFactoryAndDevice()
	{
		m_factory = std::make_unique<DxFactory>();
		m_device = std::make_unique<Dx12Device>();

		m_factory->Create();
		m_device->Create(m_factory.get());
	}

	void GiDx12RhiManager::CreateCommonObjects()
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

	void GiDx12RhiManager::CreateSwapChain(const WinId& winId)
	{
		m_swapChain = std::make_unique<DxSwapChain>();
		m_swapChain->Create(m_factory.get(), m_commandQueue.get()->GetDxObjectPtr(), winId, 1, 1, DXGI_FORMAT_R8G8B8A8_UNORM, 2);
	}

	void GiDx12RhiManager::CreateDescriptorAllocator()
	{
		m_cbvSrvUavAllocator = std::make_unique<Dx12DescriptorAllocator>(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, false);
		m_runTimeCbvSrvUavHeap = std::make_unique<Dx12DescriptorHeap>(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, true);

		m_rtvAllocator = std::make_unique<Dx12DescriptorAllocator>(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, false);
		m_dsvAllocator = std::make_unique<Dx12DescriptorAllocator>(D3D12_DESCRIPTOR_HEAP_TYPE_DSV, false);

		m_cbvSrvUavAllocator->Create(m_device.get());
		m_rtvAllocator->Create(m_device.get());
		m_dsvAllocator->Create(m_device.get());
	}
}
