#pragma once

#include "../../RHI/RHI.h"
#include "../Math/Vector4.h"

namespace XusoryEngine
{
	class GraphicsManager;

	class Material;
	class Mesh;
	class CommandContext
	{
	public:
		CommandContext() = default;
		DELETE_COPY_OPERATOR(CommandContext);
		DELETE_MOVE_OPERATOR(CommandContext);
		virtual ~CommandContext() = default;

		virtual void InitCommandContext(const GraphicsManager* graphicsManager) = 0;

		virtual void BeginCommand() = 0;
		virtual void EndCommand() = 0;

		virtual void ClearRenderTarget(BOOL ifClearRenderTarget, BOOL ifClearDepth, Float4 color, FLOAT depth) = 0;
		virtual void DrawRenderer(const Material* material, const Mesh* mesh) = 0;
	};

	class GiDx12GraphicsManager;
	class GiDx12CommandContext : public CommandContext
	{
	public:
		GiDx12CommandContext() = default;

		void InitCommandContext(const GraphicsManager* graphicsManager) override;

		void BeginCommand() override;
		void EndCommand() override;

		void ClearRenderTarget(BOOL ifClearRenderTarget, BOOL ifClearDepth, Float4 color, FLOAT depth) override;
		void DrawRenderer(const Material* material, const Mesh* mesh) override;

	private:
		const GiDx12GraphicsManager* m_dx12Manager = nullptr;
		Dx12GraphicsCommandList* m_commandList = nullptr;

		Dx12RenderTargetBuffer* m_currentBackBuffer;
	};
}
