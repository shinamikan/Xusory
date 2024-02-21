#include "../Shader.h"

namespace XusoryEngine
{
	Shader::Shader(const std::wstring_view& path)
	{
		m_shaderFilePath = path;
	}

	const std::wstring& Shader::GetShaderFilePath() const
	{
		return m_shaderFilePath;
	}

	const std::array<std::string, 5>& Shader::GetShaderEntryPoint() const
	{
		return m_shaderEntryPointList;
	}

	const std::string& Shader::GetVertexShaderEntryPoint() const
	{
		return m_shaderEntryPointList.at(0);
	}

	const std::string& Shader::GetPixelShaderEntryPoint() const
	{
		return m_shaderEntryPointList.at(1);
	}

	const std::string& Shader::GetDomainShaderEntryPoint() const
	{
		return m_shaderEntryPointList.at(2);
	}

	const std::string& Shader::GetHullShaderEntryPoint() const
	{
		return m_shaderEntryPointList.at(3);
	}

	const std::string& Shader::GetGeometryShaderEntryPoint() const
	{
		return m_shaderEntryPointList.at(4);
	}

	void Shader::SetFillMode(GraphicsFillMode fillMode)
	{
		m_fillMode = fillMode;
	}

	void Shader::SetCullMode(GraphicsCullMode cullMode)
	{
		m_cullMode = cullMode;
	}

	void Shader::SetTriangleWindingOrder(TriangleWindingOrder triangleWindingOrder)
	{
		m_triangleWindingOrder = triangleWindingOrder;
	}

	void Shader::SetShaderFilePath(const std::wstring_view& path)
	{
		m_shaderFilePath = path;
	}

	void Shader::SetVertexShaderEntryPoint(const std::string_view& entryPoint)
	{
		m_shaderEntryPointList.at(0) = entryPoint;
	}

	void Shader::SetPixelShaderEntryPoint(const std::string_view& entryPoint)
	{
		m_shaderEntryPointList.at(1) = entryPoint;
	}

	void Shader::SetDomainShaderEntryPoint(const std::string_view& entryPoint)
	{
		m_shaderEntryPointList.at(2) = entryPoint;
	}

	void Shader::SetHullShaderEntryPoint(const std::string_view& entryPoint)
	{
		m_shaderEntryPointList.at(3) = entryPoint;
	}

	void Shader::SetGeometryShaderEntryPoint(const std::string_view& entryPoint)
	{
		m_shaderEntryPointList.at(4) = entryPoint;
	}

	GraphicsFillMode Shader::GetFillMode() const
	{
		return m_fillMode;
	}

	GraphicsCullMode Shader::GetCullMode() const
	{
		return m_cullMode;
	}

	TriangleWindingOrder Shader::GetTriangleWindingOrder() const
	{
		return m_triangleWindingOrder;
	}
}
