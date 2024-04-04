#include "../TextureLoader.h"

namespace XusoryEngine
{
	std::shared_ptr<Texture> DdsTextureLoader::LoadTexture(const std::wstring_view& path)
	{
		const auto texture = std::make_shared<Texture>();
		return texture;
	}
}
