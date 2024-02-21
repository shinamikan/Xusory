#pragma once

namespace XusoryEngine
{
	class CommandContext;
	class RenderPipeline
	{
	public:
		RenderPipeline() = default;
		DELETE_COPY_OPERATOR(RenderPipeline);
		DELETE_MOVE_OPERATOR(RenderPipeline);
		virtual ~RenderPipeline() = default;

		virtual void Render(CommandContext* commandContext) = 0;
	};
}
