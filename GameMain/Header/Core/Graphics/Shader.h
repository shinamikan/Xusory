#pragma once

#include <iostream>
#include "../../RHI/RHI.h"

namespace XusoryEngine
{
	enum class GraphicsFillMode
	{
		FILL_MODE_WIRE_FRAME = 2,
		FILL_MODE_SOLID = 3
	};

	enum class GraphicsCullMode
	{
		CULL_MODE_NONE = 1,
		CULL_MODE_FRONT = 2,
		CULL_MODE_BACK = 3
	};

	enum class TriangleWindingOrder
	{
		ANTI_CLOCK_WISE = 0,
		CLOCK_WISE
	};

	class Shader
	{
	public:
		Shader() = default;
		explicit Shader(const std::wstring_view& path);

		const std::wstring& GetShaderFilePath() const;

		const std::array<std::string, 5>& GetShaderEntryPoint() const;
		const std::string& GetVertexShaderEntryPoint() const;
		const std::string& GetPixelShaderEntryPoint() const;
		const std::string& GetDomainShaderEntryPoint() const;
		const std::string& GetHullShaderEntryPoint() const;
		const std::string& GetGeometryShaderEntryPoint() const;

		GraphicsFillMode GetFillMode() const;
		GraphicsCullMode GetCullMode() const;
		TriangleWindingOrder GetTriangleWindingOrder() const;

		void SetShaderFilePath(const std::wstring_view& path);
		void SetVertexShaderEntryPoint(const std::string_view& entryPoint);
		void SetPixelShaderEntryPoint(const std::string_view& entryPoint);
		void SetDomainShaderEntryPoint(const std::string_view& entryPoint);
		void SetHullShaderEntryPoint(const std::string_view& entryPoint);
		void SetGeometryShaderEntryPoint(const std::string_view& entryPoint);

		void SetFillMode(GraphicsFillMode fillMode);
		void SetCullMode(GraphicsCullMode cullMode);
		void SetTriangleWindingOrder(TriangleWindingOrder triangleWindingOrder);

	private:
		std::wstring m_shaderFilePath;
		std::array<std::string, 5> m_shaderEntryPointList;

		GraphicsFillMode m_fillMode = GraphicsFillMode::FILL_MODE_SOLID;
		GraphicsCullMode m_cullMode = GraphicsCullMode::CULL_MODE_BACK;
		TriangleWindingOrder m_triangleWindingOrder = TriangleWindingOrder::CLOCK_WISE;
	};
}
