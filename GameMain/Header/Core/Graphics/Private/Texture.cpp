#include "../Texture.h"

namespace XusoryEngine
{
	Texture::Texture(const std::wstring_view& path)
	{
		m_textureFilePath = path;
	}

	const std::wstring& Texture::GetTextureFilePath() const
	{
		return m_textureFilePath;
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
