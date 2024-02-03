#pragma once

#include "../Platform/Platform.h"

namespace XusoryEngine
{
	enum class GraphicsLibrary
	{
		UNKNOWN = 0,
		DirectX12,
		OpenGL
	};

	class IGraphicsManager
	{
	public:
		DELETE_COPY_OPERATOR(IGraphicsManager);
		DELETE_MOVE_OPERATOR(IGraphicsManager);
		virtual ~IGraphicsManager() = default;

		virtual void InitGraphicsObject(const void* renderWindow) = 0;
		virtual void Resize(UINT width, UINT height) = 0;
		virtual void Render() = 0;

		GraphicsLibrary m_graphicsLibrary = GraphicsLibrary::UNKNOWN;

	protected:
		explicit IGraphicsManager(GraphicsLibrary graphicsLibrary) : m_graphicsLibrary(graphicsLibrary) { }
	};
}
