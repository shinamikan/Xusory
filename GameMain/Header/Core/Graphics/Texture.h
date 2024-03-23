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
		friend class GiDx12RhiManager;
		friend class ResourceLoader;

	public:
		Texture() = default;

		const std::string& GetName() const;

		TextureDimension GetDimension() const;
		AddressMode GetAddressModeU() const;
		AddressMode GetAddressModeV() const;
		AddressMode GetAddressModeW() const;
		FilterMode GetFilterMode() const;

		UINT GetTextureWidth() const;
		UINT GetTextureHeight() const;

	private:
		std::string m_name;

		TextureDimension m_dimension = TextureDimension::UNKNOWN;
		AddressMode m_addressModeU = AddressMode::WRAP;
		AddressMode m_addressModeV = AddressMode::WRAP;
		AddressMode m_addressModeW = AddressMode::WRAP;
		FilterMode m_filterMode = FilterMode::LINEAR;

		void* m_textureData = nullptr;

		UINT m_width = 0;
		UINT m_height = 0;
	};
}
