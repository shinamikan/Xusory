#pragma once

namespace XusoryEngine
{
	enum class GraphicsLibrary
	{
		UNKNOWN = 0,
		Direct3D_12,
		Direct3D_11,
		OpenGL
	};

	enum class TextureDimension
	{
		UNKNOWN = 0,
		TEX_2D = 4,
		TEX_2D_ARRAY = 5,
		TEX_3D = 8,
		TEX_CUBE = 9,
		TEX_CUBE_ARRAY = 10
	};
}
