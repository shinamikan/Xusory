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

	UINT Shader::GetCBufferCount() const
	{
		return static_cast<UINT>(m_shaderCBufferPropertyList.size());
	}

	const ShaderCBufferProperty& Shader::GetCBufferProperty(UINT index) const
	{
		return m_shaderCBufferPropertyList.at(index);
	}

	UINT Shader::GetPropertyCount() const
	{
		return static_cast<UINT>(m_shaderPropertyList.size());
	}

	const std::string& Shader::GetPropertyNameByIndex(UINT index) const
	{
		return m_shaderPropertyList.at(index).name;
	}

	UINT Shader::GetPropertyIndexByName(const std::string_view& name) const
	{
		return m_shaderPropertyMap.at(name.data()).index;
	}

	const ShaderProperty& Shader::GetPropertyByIndex(UINT index) const
	{
		return m_shaderPropertyList.at(index);
	}

	const ShaderProperty& Shader::GetPropertyByName(const std::string_view& name) const
	{
		return m_shaderPropertyMap.at(name.data());
	}

	ShaderPropertyType Shader::GetPropertyTypeByIndex(UINT index) const
	{
		return m_shaderPropertyList.at(index).propertyType;
	}

	ShaderPropertyType Shader::GetPropertyTypeByName(const std::string_view& name) const
	{
		return m_shaderPropertyMap.at(name.data()).propertyType;
	}

	UINT Shader::GetPropertyOffsetByIndex(UINT index) const
	{
		return m_shaderPropertyList.at(index).offset;
	}

	UINT Shader::GetPropertyOffsetByName(const std::string_view& name) const
	{
		return m_shaderPropertyMap.at(name.data()).offset;
	}

	UINT Shader::GetPropertySlotByIndex(UINT index) const
	{
		return m_shaderPropertyList.at(index).slot;
	}

	UINT Shader::GetPropertySlotByName(const std::string_view& name) const
	{
		return m_shaderPropertyMap.at(name.data()).slot;
	}

	UINT Shader::GetPropertySpaceByIndex(UINT index) const
	{
		return m_shaderPropertyList.at(index).space;
	}

	UINT Shader::GetPropertySpaceByName(const std::string_view& name) const
	{
		return m_shaderPropertyMap.at(name.data()).space;
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
}
