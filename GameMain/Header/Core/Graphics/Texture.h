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
		Texture(const std::wstring_view& path);

		const std::wstring& GetTextureFilePath() const;

		TextureDimension m_dimension = TextureDimension::UNKNOWN;
		AddressMode m_addressModeU = AddressMode::WRAP;
		AddressMode m_addressModeV = AddressMode::WRAP;
		AddressMode m_addressModeW = AddressMode::WRAP;
		FilterMode m_filterMode = FilterMode::LINEAR;

		UINT m_width = 0;
		UINT m_height = 0;
		UINT16 m_mipLevels = 0;

	private:
		std::wstring m_textureFilePath;
	};
}
