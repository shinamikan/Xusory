#pragma once

#include "../../RHI/RHI.h"
#include "Common/GraphicsDefine.h"

namespace XusoryEngine
{
	class Material;
	class Mesh;
	class Texture;
	class Shader;
	DLL_CLASS(RhiManager)
	{
	public:
		DELETE_COPY_OPERATOR(RhiManager);
		DELETE_MOVE_OPERATOR(RhiManager);
		virtual ~RhiManager() = default;

		virtual void InitGraphicsObject(void* renderWindow) = 0;
		virtual void Resize(UINT width, UINT height) = 0;

		virtual void ReSetRuntimeResourceHeap(UINT heapNum) = 0;
		virtual UINT GetRuntimeResourceHeapIndex() = 0;
		virtual void AddRuntimeResourceHeapIndex(UINT resourceNum) = 0;

		virtual void ReSetCommandList() = 0;
		virtual void ExecuteCommandAndWait() = 0;
		virtual void PresentBackBuffer() = 0;

		virtual void BuildMaterial(Material* material) = 0;
		virtual void BuildMesh(Mesh* mesh) = 0;
		virtual void BuildTexture(Texture* texture) = 0;
		virtual void BuildShader(Shader* shader) = 0;

		virtual BOOL IsMaterialBuilt(Material* material) = 0;
		virtual BOOL IsMeshBuilt(Mesh* mesh) = 0;
		virtual BOOL IsTextureBuilt(Texture* texture) = 0;
		virtual BOOL IsShaderBuilt(Shader* shader) = 0;

		virtual void DestroyMaterial(Material* material) = 0;
		virtual void DestroyMesh(Mesh* mesh) = 0;
		virtual void DestroyShader(Shader* shader) = 0;
		virtual void DestroyTexture(Texture* texture) = 0;

		GraphicsLibrary GetGraphicsLibrary() const;

	protected:
		explicit RhiManager(GraphicsLibrary graphicsLibrary) : m_graphicsLibrary(graphicsLibrary) { }

	private:
		GraphicsLibrary m_graphicsLibrary = GraphicsLibrary::UNKNOWN;
	};

	DLL_CLASS(GiDx12RhiManager) : public RhiManager
	{
		friend class GiDx12CommandContext;
		using RootSignaturePipelineStatePair = std::pair<std::unique_ptr<Dx12RootSignature>, std::unique_ptr<Dx12GraphicsPipelineState>>;

	public:
		GiDx12RhiManager();
		DELETE_COPY_OPERATOR(GiDx12RhiManager);
		DELETE_MOVE_OPERATOR(GiDx12RhiManager);
		~GiDx12RhiManager() override = default;

		void InitGraphicsObject(void* renderWindow) override;
		void Resize(UINT width, UINT height) override;

		void ReSetRuntimeResourceHeap(UINT heapNum) override;
		UINT GetRuntimeResourceHeapIndex() override;
		void AddRuntimeResourceHeapIndex(UINT resourceNum) override;

		void ExecuteCommandAndWait() override;
		void ReSetCommandList() override;
		void PresentBackBuffer() override;

		void BuildMaterial(Material* material) override;
		void BuildMesh(Mesh* mesh) override;
		void BuildTexture(Texture* texture) override;
		void BuildShader(Shader* shader) override;

		BOOL IsMaterialBuilt(Material* material) override;
		BOOL IsMeshBuilt(Mesh* mesh) override;
		BOOL IsTextureBuilt(Texture* texture) override;
		BOOL IsShaderBuilt(Shader* shader) override;

		void DestroyMaterial(Material* material) override;
		void DestroyMesh(Mesh* mesh) override;
		void DestroyShader(Shader* shader) override;
		void DestroyTexture(Texture* texture) override;

	private:
		void CreateInputLayout();
		void CreateFactoryAndDevice();
		void CreateCommonObjects();
		void CreateSwapChain(const WinId& winId);
		void CreateDescriptorAllocator();

		D3D12_VIEWPORT m_screenViewport = D3D12_VIEWPORT();
		D3D12_RECT m_scissorRect = D3D12_RECT();
		std::vector<D3D12_INPUT_ELEMENT_DESC> m_inputLayoutList;

		std::unique_ptr<DxFactory> m_factory = nullptr;
		std::unique_ptr<Dx12Device> m_device = nullptr;

		std::unique_ptr<Dx12CommandAllocator> m_commandAllocator = nullptr;
		std::unique_ptr<Dx12CommandQueue> m_commandQueue = nullptr;
		std::unique_ptr<Dx12GraphicsCommandList> m_commandList = nullptr;
		std::unique_ptr<Dx12Fence> m_fence = nullptr;
		std::unique_ptr<DxSwapChain> m_swapChain = nullptr;

		std::unique_ptr<Dx12DescriptorAllocator> m_cbvSrvUavAllocator = nullptr;
		std::unique_ptr<Dx12DescriptorHeap> m_runTimeCbvSrvUavHeap = nullptr;
		UINT m_runTimeResourceHeapIndex = 0;

		std::unique_ptr<Dx12DescriptorAllocator> m_rtvAllocator = nullptr;
		std::unique_ptr<Dx12DescriptorAllocator> m_dsvAllocator = nullptr;

		std::vector<std::unique_ptr<Dx12RenderTargetBuffer>> m_backBufferList;
		std::vector<std::unique_ptr<Dx12RenderTargetBuffer>> m_renderTargetList;
		std::unique_ptr<Dx12DepthStencilBuffer> m_depthStencilBuffer = nullptr;

		std::unordered_map<void*, std::unique_ptr<Dx12UploadBuffer>> m_constantBufferMap;
		std::unordered_map<Mesh*, std::unique_ptr<Dx12MeshBuffer>> m_meshBufferMap;
		std::unordered_map<Shader*, RootSignaturePipelineStatePair> m_shaderPipelineStateMap;
		std::unordered_map<Texture*, std::unique_ptr<Dx12TextureBuffer>> m_textureMap;
	};
}
