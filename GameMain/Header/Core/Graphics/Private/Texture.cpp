#include "../Texture.h"

namespace XusoryEngine
{
	const std::string& Texture::GetName() const
	{
		return m_name;
	}

	TextureDimension Texture::GetDimension() const
	{
		return m_dimension;
	}

	AddressMode Texture::GetAddressModeU() const
	{
		return m_addressModeU;
	}

	AddressMode Texture::GetAddressModeV() const
	{
		return m_addressModeV;
	}

	AddressMode Texture::GetAddressModeW() const
	{
		return m_addressModeW;
	}

	FilterMode Texture::GetFilterMode() const
	{
		return m_filterMode;
	}

	UINT Texture::GetTextureWidth() const
	{
		return m_width;
	}

	UINT Texture::GetTextureHeight() const
	{
		return m_height;
	}
}
