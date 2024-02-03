#include "../Dx12Manager.h"

namespace XusoryEngine
{
	Dx12Manager::Dx12Manager() : IGraphicsManager(GraphicsLibrary::DirectX12) { }

	Dx12Manager::~Dx12Manager()
	{
		delete m_factory;
		delete m_device;
		delete m_commonRootSignature;
	}

	void Dx12Manager::InitGraphicsObject(const void* renderWindow)
	{
		CreateFactoryDevice();
		CreateCommonRootSignature();
	}

	void Dx12Manager::Resize(UINT width, UINT height)
	{
		
	}

	void Dx12Manager::Render()
	{
		
	}

	void Dx12Manager::CreateFactoryDevice()
	{
		m_factory = new DxFactory;
		m_device = new Dx12Device;

		m_factory->Create();
		m_device->Create(m_factory);
	}

	void Dx12Manager::CreateCommonRootSignature()
	{
		m_commonRootSignature = new Dx12RootSignature;
		//m_commonRootSignature.AddDescriptorRange(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);
		m_commonRootSignature->AddConstantBufferView(0);
		m_commonRootSignature->Create(m_device);
	}

}
