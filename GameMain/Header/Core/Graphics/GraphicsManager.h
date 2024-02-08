#pragma once

#include "../../RHI/RHI.h"

namespace XusoryEngine
{
	enum class GraphicsLibrary
	{
		UNKNOWN = 0,
		DirectX12,
		DirectX11,
		OpenGL
	};

	class GraphicsManager
	{
	public:
		DELETE_COPY_OPERATOR(GraphicsManager);
		DELETE_MOVE_OPERATOR(GraphicsManager);
		virtual ~GraphicsManager() = default;

		virtual void InitGraphicsObject(const void* renderWindow) = 0;
		virtual void Resize(UINT width, UINT height) = 0;

		GraphicsLibrary GetGraphicsLibrary() const;

	protected:
		explicit GraphicsManager(GraphicsLibrary graphicsLibrary) : m_graphicsLibrary(graphicsLibrary) { }

	private:
		GraphicsLibrary m_graphicsLibrary = GraphicsLibrary::UNKNOWN;
	};

	class GiDx12GraphicsManager : public GraphicsManager
	{
	public:
		GiDx12GraphicsManager();
		DELETE_COPY_OPERATOR(GiDx12GraphicsManager);
		DELETE_MOVE_OPERATOR(GiDx12GraphicsManager);
		~GiDx12GraphicsManager() override = default;

		void InitGraphicsObject(const void* renderWindow) override;
		void Resize(UINT width, UINT height) override;

	private:
		void CreateFactoryAndDevice();
		void CreateDescriptorAllocator();

		void CreateCommonRootSignature();

		std::unique_ptr<DxFactory> m_factory = nullptr;
		std::unique_ptr<Dx12Device> m_device = nullptr;

		std::unique_ptr<Dx12DescriptorAllocator> m_cbvSrvUavAllocator = nullptr;
		std::unique_ptr<Dx12DescriptorAllocator> m_rtvAllocator = nullptr;
		std::unique_ptr<Dx12DescriptorAllocator> m_dsvAllocator = nullptr;

		Dx12RootSignature* m_commonRootSignature = nullptr;
	};
}
