#pragma once

#include "../../RHI/RHI.h"

namespace XusoryEngine
{
	enum class GraphicsLibrary
	{
		UNKNOWN = 0,
		Direct3D_12,
		Direct3D_11,
		OpenGL
	};

	class Shader;
	class GraphicsManager
	{
	public:
		DELETE_COPY_OPERATOR(GraphicsManager);
		DELETE_MOVE_OPERATOR(GraphicsManager);
		virtual ~GraphicsManager() = default;

		virtual void InitGraphicsObject(void* renderWindow) = 0;
		virtual void Resize(UINT width, UINT height) = 0;
		virtual void BuildShader(const Shader* shader) = 0;

		GraphicsLibrary GetGraphicsLibrary() const;

	protected:
		explicit GraphicsManager(GraphicsLibrary graphicsLibrary) : m_graphicsLibrary(graphicsLibrary) { }

	private:
		GraphicsLibrary m_graphicsLibrary = GraphicsLibrary::UNKNOWN;
	};

	class GiDx12GraphicsManager : public GraphicsManager
	{
		using RootSignaturePipelineStatePair = std::pair<std::unique_ptr<Dx12RootSignature>, std::unique_ptr<Dx12GraphicsPipelineState>>;

	public:
		GiDx12GraphicsManager();
		DELETE_COPY_OPERATOR(GiDx12GraphicsManager);
		DELETE_MOVE_OPERATOR(GiDx12GraphicsManager);
		~GiDx12GraphicsManager() override = default;

		void InitGraphicsObject(void* renderWindow) override;
		void Resize(UINT width, UINT height) override;
		void BuildShader(const Shader* shader) override;

		void Render();

	private:
		void CreateFactoryAndDevice();
		void CreateCommonObjects();
		void CreateDescriptorAllocator();
		void CreateSwapChain(const WinId& winId);
		void CreateInputLayout();

		void CreateCommonRootSignature();

		D3D12_VIEWPORT m_screenViewport = D3D12_VIEWPORT();
		D3D12_RECT m_scissorRect = D3D12_RECT();

		std::unique_ptr<DxFactory> m_factory = nullptr;
		std::unique_ptr<Dx12Device> m_device = nullptr;

		std::unique_ptr<Dx12DescriptorAllocator> m_cbvSrvUavAllocator = nullptr;
		std::unique_ptr<Dx12DescriptorAllocator> m_rtvAllocator = nullptr;
		std::unique_ptr<Dx12DescriptorAllocator> m_dsvAllocator = nullptr;

		std::unique_ptr<Dx12CommandAllocator> m_commandAllocator = nullptr;
		std::unique_ptr<Dx12CommandQueue> m_commandQueue = nullptr;
		std::unique_ptr<Dx12GraphicsCommandList> m_commandList = nullptr;
		std::unique_ptr<Dx12Fence> m_fence = nullptr;

		std::unique_ptr<DxSwapChain> m_swapChain = nullptr;

		std::vector<std::unique_ptr<Dx12RenderTargetBuffer>> m_backBufferList;
		std::vector<std::unique_ptr<Dx12RenderTargetBuffer>> m_renderTargetList;
		std::unique_ptr<Dx12DepthStencilBuffer> m_depthStencilBuffer = nullptr;

		std::vector<D3D12_INPUT_ELEMENT_DESC> m_inputLayoutList;
		std::unordered_map<const Shader*, RootSignaturePipelineStatePair> m_shaderPipelineStateMap;

		std::unique_ptr<Dx12RootSignature> m_commonRootSignature = nullptr;
	};
}
