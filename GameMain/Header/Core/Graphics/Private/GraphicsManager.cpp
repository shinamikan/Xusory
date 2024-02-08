#include "../GraphicsManager.h"

namespace XusoryEngine
{
	GraphicsLibrary GraphicsManager::GetGraphicsLibrary() const
	{
		return m_graphicsLibrary;
	}

	GiDx12GraphicsManager::GiDx12GraphicsManager() : GraphicsManager(GraphicsLibrary::DirectX12) { }

	void GiDx12GraphicsManager::InitGraphicsObject(const void* renderWindow)
	{
		CreateFactoryAndDevice();
		CreateDescriptorAllocator();

		CreateCommonRootSignature();
	}

	void GiDx12GraphicsManager::Resize(UINT width, UINT height)
	{

	}

	void GiDx12GraphicsManager::CreateFactoryAndDevice()
	{
		m_factory = std::make_unique<DxFactory>();
		m_device = std::make_unique<Dx12Device>();

		m_factory->Create();
		m_device->Create(m_factory.get());
	}

	void GiDx12GraphicsManager::CreateDescriptorAllocator()
	{
		m_cbvSrvUavAllocator = std::make_unique<Dx12DescriptorAllocator>(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, true);
		m_rtvAllocator = std::make_unique<Dx12DescriptorAllocator>(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, false);
		m_dsvAllocator = std::make_unique<Dx12DescriptorAllocator>(D3D12_DESCRIPTOR_HEAP_TYPE_DSV, false);

		m_cbvSrvUavAllocator->AllocateDescriptor(m_device.get(), 10);
	}

	void GiDx12GraphicsManager::CreateCommonRootSignature()
	{
		m_commonRootSignature = new Dx12RootSignature;
		//m_commonRootSignature.AddDescriptorRange(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);
		m_commonRootSignature->AddConstantBufferView(0);
		m_commonRootSignature->Create(m_device.get());
	}

	

}
