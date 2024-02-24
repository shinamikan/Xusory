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

		TextureDimension dimension = TextureDimension::UNKNOWN;
		AddressMode addressModeU = AddressMode::WRAP;
		AddressMode addressModeV = AddressMode::WRAP;
		AddressMode addressModeW = AddressMode::WRAP;
		FilterMode filterMode = FilterMode::LINEAR;

		UINT width = 0;
		UINT height = 0;
		UINT16 mipLevels = 0;

	private:
		std::wstring m_textureFilePath;
	};
}
