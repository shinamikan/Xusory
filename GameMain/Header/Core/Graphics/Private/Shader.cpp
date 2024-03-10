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

	UINT Shader::GetCBufferCount() const
	{
		return static_cast<UINT>(m_shaderCBufferPropertyList.size());
	}

	const ShaderCBufferProperty& Shader::GetCBufferProperty(UINT index) const
	{
		ThrowIfOutOfCBufferRange(index);
		return m_shaderCBufferPropertyList.at(index);
	}

	UINT Shader::GetPropertyCount() const
	{
		return static_cast<UINT>(m_shaderPropertyList.size());
	}

	const std::string& Shader::GetPropertyNameByIndex(UINT index) const
	{
		ThrowIfOutOfPropertyRange(index);
		return m_shaderPropertyList.at(index).name;
	}

	const ShaderProperty& Shader::GetPropertyByIndex(UINT index) const
	{
		ThrowIfOutOfPropertyRange(index);
		return m_shaderPropertyList.at(index);
	}

	ShaderPropertyType Shader::GetPropertyTypeByIndex(UINT index) const
	{
		ThrowIfOutOfPropertyRange(index);
		return m_shaderPropertyList.at(index).propertyType;
	}

	UINT Shader::GetPropertyOffsetByIndex(UINT index) const
	{
		ThrowIfOutOfPropertyRange(index);
		return m_shaderPropertyList.at(index).offset;
	}

	UINT Shader::GetPropertySlotByIndex(UINT index) const
	{
		ThrowIfOutOfPropertyRange(index);
		return m_shaderPropertyList.at(index).slot;
	}

	UINT Shader::GetPropertySpaceByIndex(UINT index) const
	{
		ThrowIfOutOfPropertyRange(index);
		return m_shaderPropertyList.at(index).space;
	}

	UINT Shader::GetPropertyIndexByName(const std::string_view& name) const
	{
		CaptureNoReturnFunc(return m_shaderPropertyMap.at(name.data()).index);
	}

	const ShaderProperty& Shader::GetPropertyByName(const std::string_view& name) const
	{
		CaptureNoReturnFunc(return m_shaderPropertyMap.at(name.data()));
	}

	ShaderPropertyType Shader::GetPropertyTypeByName(const std::string_view& name) const
	{
		CaptureNoReturnFunc(return m_shaderPropertyMap.at(name.data()).propertyType);
	}

	UINT Shader::GetPropertyOffsetByName(const std::string_view& name) const
	{
		CaptureNoReturnFunc(return m_shaderPropertyMap.at(name.data()).offset);
	}

	UINT Shader::GetPropertySlotByName(const std::string_view& name) const
	{
		CaptureNoReturnFunc(return m_shaderPropertyMap.at(name.data()).slot);
	}

	UINT Shader::GetPropertySpaceByName(const std::string_view& name) const
	{
		CaptureNoReturnFunc(return m_shaderPropertyMap.at(name.data()).space);
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

	void Shader::ThrowIfOutOfCBufferRange(UINT index) const
	{
		if (index >= m_shaderCBufferPropertyList.size())
		{
			ThrowWithErrName(RuntimeError, "Index out of constant buffer property list range");
		}
	}

	void Shader::ThrowIfOutOfPropertyRange(UINT index) const
	{
		if (index >= m_shaderPropertyList.size())
		{
			ThrowWithErrName(RuntimeError, "Index out of shader property list range");
		}
	}
}
