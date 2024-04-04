#pragma once

#include "../../Core/Core.h"

namespace XusoryEngine
{
	DLL_CLASS(ITextureLoader)
	{
	public:
		ITextureLoader() = default;
		DELETE_COPY_OPERATOR(ITextureLoader);
		DELETE_MOVE_OPERATOR(ITextureLoader);
		virtual ~ITextureLoader() = default;

		virtual std::shared_ptr<Texture> LoadTexture(const std::wstring_view& path) = 0;
	};

	DLL_CLASS(DdsTextureLoader) : public ITextureLoader
	{
	public:
		std::shared_ptr<Texture> LoadTexture(const std::wstring_view& path) override;
		CREATE_FACTORY(ITextureLoader, DdsTextureLoader);
	};

	typedef FactoryBase<ITextureLoader> TextureLoaderFactory;
	REGISTER_FACTORY(TextureLoaderFactory, DdsTextureLoader, TEXT("dds"));
}
