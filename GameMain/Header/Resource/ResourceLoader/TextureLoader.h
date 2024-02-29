#pragma once

#include "../../Core/Core.h"

namespace XusoryEngine
{
	class Texture;
	class ITextureLoader
	{
	public:
		DELETE_COPY_OPERATOR(ITextureLoader);
		DELETE_MOVE_OPERATOR(ITextureLoader);
		virtual ~ITextureLoader() = default;

		virtual Texture* LoadTextureFile(const std::wstring& filePath) = 0;
	};
}
