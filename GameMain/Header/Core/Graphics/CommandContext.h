#pragma once

#include "../../RHI/RHI.h"
#include "../Math/Vector4.h"

namespace XusoryEngine
{
	class RhiManager;

	class Material;
	class Mesh;
	class Shader;
	class CommandContext
	{
	public:
		CommandContext() = default;
		DELETE_COPY_OPERATOR(CommandContext);
		DELETE_MOVE_OPERATOR(CommandContext);
		virtual ~CommandContext() = default;

		virtual void InitCommandContext(RhiManager* graphicsManager) = 0;

		virtual void BeginCommand() = 0;
		virtual void EndCommand() = 0;

		virtual void ClearRenderTarget(Float4 color) = 0;
		virtual void ClearDepth(FLOAT depth) = 0;
		virtual void ClearStencil(UINT8 stencil) = 0;

		virtual void DrawMesh() = 0;

		virtual void SetMaterial(const Material* material) = 0;
		virtual void SetMesh(const Mesh* mesh) = 0;
	};

	class GiDx12RhiManager;
	class GiDx12CommandContext : public CommandContext
	{
	public:
		GiDx12CommandContext() = default;

		void InitCommandContext(RhiManager* graphicsManager) override;

		void BeginCommand() override;
		void EndCommand() override;

		void ClearRenderTarget(Float4 color) override;
		void ClearDepth(FLOAT depth) override;
		void ClearStencil(UINT8 stencil) override;

		void DrawMesh() override;

		void SetMaterial(const Material* material) override;
		void SetMesh(const Mesh* mesh) override;

	private:
		GiDx12RhiManager* m_dx12Manager = nullptr;
		Dx12GraphicsCommandList* m_commandList = nullptr;

		Dx12RenderTargetBuffer* m_currentBackBuffer = nullptr;
		const Mesh* m_activeMesh = nullptr;
		const Shader* m_activeShader = nullptr;
	};
}
