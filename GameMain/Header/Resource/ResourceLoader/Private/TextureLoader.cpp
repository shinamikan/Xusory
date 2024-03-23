#include "../TextureLoader.h"

namespace XusoryEngine
{
	REGISTER_FACTORY(TextureLoaderFactory, DdsTextureLoader, TEXT("dds"));
	std::shared_ptr<Texture> DdsTextureLoader::LoadTexture(const std::wstring_view& path)
	{
		const auto texture = std::make_shared<Texture>();
		return texture;
	}
}
