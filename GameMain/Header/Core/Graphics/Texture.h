#pragma once

#include "../../RHI/RHI.h"
#include "Common/GraphicsDefine.h"

namespace XusoryEngine
{
	enum class AddressMode
	{
		WRAP = 1,
		MIRROR,
		CLAMP,
		BORDER,
		MIRROR_ONCE
	};

	enum class FilterMode
	{
		POINT = 0,
		LINEAR = 21,
		ANISOTROPIC = 85
	};

	class Texture
	{
		friend class GiDx12GraphicsManager;

	public:
		explicit Texture(const std::wstring_view& path);

		const std::wstring& GetTextureFilePath() const;
		UINT GetTextureWidth() const;
		UINT GetTextureHeight() const;

		TextureDimension dimension = TextureDimension::UNKNOWN;
		AddressMode addressModeU = AddressMode::WRAP;
		AddressMode addressModeV = AddressMode::WRAP;
		AddressMode addressModeW = AddressMode::WRAP;
		FilterMode filterMode = FilterMode::LINEAR;

		UINT16 mipLevels = 0;

	private:
		std::wstring m_textureFilePath;
		void* m_textureData = nullptr;

		UINT m_width = 0;
		UINT m_height = 0;
	};
}
