#include "../GraphicsManager.h"

#include "../Material.h"
#include "../Common/GraphicsDefine.h"
#include "../Mesh.h"
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
		CreateInputLayout();
		CreateFactoryAndDevice();
		CreateCommonObjects();
		CreateSwapChain(static_cast<WinId>(renderWindow));
		CreateDescriptorAllocator();

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

	void GiDx12GraphicsManager::ExecuteCommandAndWait()
	{
		m_commandList->EndCommand();
		m_commandQueue->ExecuteCommandList({ m_commandList.get() });
		m_commandQueue->SignalAndWaitForNextFence(m_fence.get());
	}

	void GiDx12GraphicsManager::ReSetCommandList()
	{
		m_commandList->ResetCommandList(m_commandAllocator.get(), nullptr);
	}

	void GiDx12GraphicsManager::BuildMaterial(Material* material)
	{
		material->BindShader();
		const auto* shader = material->GetShader();

		for (UINT i = 0; i < shader->GetCBufferCount(); i++)
		{
			auto& property = shader->GetCBufferProperty(i);

			auto* uploadBuffer = new Dx12UploadBuffer(true);
			uploadBuffer->CreateUploadBuffer(m_device.get(), property.size);

			m_constantBufferMap.emplace(material->m_constantBufferList.at(i).get(), uploadBuffer);
		}
	}

	void GiDx12GraphicsManager::BuildMesh(Mesh* mesh)
	{
		auto& vertices = mesh->GetVertices();
		auto& indices = mesh->GetIndices();

		auto* meshBuffer = new Dx12MeshBuffer;
		meshBuffer->CreateMeshBuffer(m_device.get(), static_cast<UINT>(vertices.size()), sizeof(Vertex),
			static_cast<UINT>(indices.size()), static_cast<DXGI_FORMAT>(mesh->indexFormat));
		meshBuffer->UploadMeshResource(m_commandList.get(), vertices.data(), indices.data());

		m_meshBufferMap.emplace(mesh, meshBuffer);
	}

	void GiDx12GraphicsManager::BuildTexture(Texture* texture)
	{

	}

	void GiDx12GraphicsManager::BuildShader(Shader* shader)
	{
		DxShaderCompiler shaderCompiler;
		shaderCompiler.CompileShader(shader->GetShaderFilePath(), shader->GetShaderEntryPoint(), nullptr);

		UINT propertyIndexTemp = 0;
		for (const auto& cBuffer : shaderCompiler.m_constantBufferDescMap)
		{
			const auto& cBufferDesc = cBuffer.first;
			ShaderCBufferProperty cBufferProperty;
			cBufferProperty.name = cBufferDesc.bufferName;
			cBufferProperty.size = cBufferDesc.Size;
			cBufferProperty.variableNum = cBufferDesc.Variables;
			shader->m_shaderCBufferPropertyList.push_back(std::move(cBufferProperty));

			for (const auto& variableDesc : cBuffer.second)
			{
				ShaderProperty property;
				property.name = variableDesc.variableName;
				property.index = propertyIndexTemp;
				property.offset = variableDesc.StartOffset;
				property.slot = cBuffer.first.bindPoint;
				property.space = cBuffer.first.space;
				if (variableDesc.typeName == "float") property.propertyType = ShaderPropertyType::FLOAT;
				else if (variableDesc.typeName == "float2") property.propertyType = ShaderPropertyType::FLOAT2;
				else if (variableDesc.typeName == "float3") property.propertyType = ShaderPropertyType::FLOAT3;
				else if (variableDesc.typeName == "float4") property.propertyType = ShaderPropertyType::FLOAT4;
				else if (variableDesc.typeName == "float2x2") property.propertyType = ShaderPropertyType::MATRIX2;
				else if (variableDesc.typeName == "float3x3") property.propertyType = ShaderPropertyType::MATRIX3;
				else if (variableDesc.typeName == "float4x4") property.propertyType = ShaderPropertyType::MATRIX4;
				else
				{
					ThrowWithErrName(RuntimeError, "Unrecognized property type");
				}
				property.dimension = TextureDimension::UNKNOWN;

				propertyIndexTemp++;
				shader->m_shaderPropertyList.push_back(std::move(property));
				shader->m_shaderPropertyMap.emplace(variableDesc.variableName, *(shader->m_shaderPropertyList.end() - 1));
			}
		}
		for (const auto& resourceDesc : shaderCompiler.m_shaderResourceDescList)
		{
			ShaderProperty property;
			property.name = resourceDesc.resourceName;
			property.index = propertyIndexTemp;
			property.offset = 0;
			property.slot = resourceDesc.BindPoint;
			property.space = resourceDesc.Space;
			property.propertyType = ShaderPropertyType::TEXTURE;
			property.dimension = static_cast<TextureDimension>(resourceDesc.Dimension);

			propertyIndexTemp++;
			shader->m_shaderPropertyList.push_back(std::move(property));
			shader->m_shaderPropertyMap.emplace(resourceDesc.resourceName, *(shader->m_shaderPropertyList.end() - 1));
		}

		auto* rootSignature = new Dx12RootSignature;
		for (const auto& cBuffer : shaderCompiler.m_constantBufferDescMap)
		{
			rootSignature->AddConstantBufferView(cBuffer.first.bindPoint, cBuffer.first.space);
		}
		for (const auto& resourceDesc : shaderCompiler.m_shaderResourceDescList)
		{
			rootSignature->AddDescriptorRange(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, resourceDesc.BindPoint, resourceDesc.Space);
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

		if (auto* vertexShader = shaderCompiler.GetVertexShader(); vertexShader != nullptr) pipelineState->SetVertexShader(vertexShader->GetBufferPointer(), vertexShader->GetBufferSize());
		if (auto* pixelShader = shaderCompiler.GetPixelShader(); pixelShader != nullptr) pipelineState->SetPixelShader(pixelShader->GetBufferPointer(), pixelShader->GetBufferSize());
		if (auto* domainShader = shaderCompiler.GetDomainShader(); domainShader != nullptr) pipelineState->SetDomainShader(domainShader->GetBufferPointer(), domainShader->GetBufferSize());
		if (auto* hullShader = shaderCompiler.GetHullShader(); hullShader != nullptr) pipelineState->SetHullShader(hullShader->GetBufferPointer(), hullShader->GetBufferSize());
		if (auto* geometryShader = shaderCompiler.GetGeometryShader(); geometryShader != nullptr) pipelineState->SetGeometryShader(geometryShader->GetBufferPointer(), geometryShader->GetBufferSize());

		pipelineState->SetBlendState(CD3DX12_BLEND_DESC(D3D12_DEFAULT));
		pipelineState->SetDepthStencilState(CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT));
		pipelineState->SetFillMode(static_cast<D3D12_FILL_MODE>(shader->fillMode));
		pipelineState->SetCullMode(static_cast<D3D12_CULL_MODE>(shader->cullMode));
		pipelineState->SetFrontCounterClockwise(static_cast<BOOL>(shader->triangleWindingOrder));

		pipelineState->SetPrimitiveTopologyType(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE);
		pipelineState->SetRenderTargetNum(1);
		pipelineState->SetRenderTargetFormat(m_swapChain->GetFormat());
		pipelineState->SetDepthFormat(m_depthStencilBuffer->GetFormat());
		pipelineState->Create(m_device.get());

		m_shaderPipelineStateMap.emplace(shader, std::make_pair(rootSignature, pipelineState));
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

	void GiDx12GraphicsManager::CreateSwapChain(const WinId& winId)
	{
		m_swapChain = std::make_unique<DxSwapChain>();
		m_swapChain->Create(m_factory.get(), m_commandQueue.get()->GetDxObjectPtr(), winId, 1, 1, DXGI_FORMAT_R8G8B8A8_UNORM, 2);
	}

	void GiDx12GraphicsManager::CreateDescriptorAllocator()
	{
		m_cbvSrvUavAllocator = std::make_unique<Dx12DescriptorAllocator>(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, true);
		m_rtvAllocator = std::make_unique<Dx12DescriptorAllocator>(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, false);
		m_dsvAllocator = std::make_unique<Dx12DescriptorAllocator>(D3D12_DESCRIPTOR_HEAP_TYPE_DSV, false);
	}
}
