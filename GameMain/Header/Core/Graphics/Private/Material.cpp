#include "../Material.h"
#include "../Shader.h"
#include "../Texture.h"

namespace XusoryEngine
{
	Material::Material(const Shader* shader) : m_bindShader(shader)
	{
		UINT propertyIndexTemp = 0;
		for (UINT i = 0; i < shader->GetCBufferCount(); i++)
		{
			auto& cBufferProperty = shader->GetCBufferProperty(i);
			auto* cBuffer = new BYTE(cBufferProperty.size);

			for (UINT j = 0; i < cBufferProperty.variableNum; j++)
			{
				auto& property = shader->GetPropertyByIndex(propertyIndexTemp);
				m_materialValueList.push_back(cBuffer + property.offset);
				m_materialValueMap.emplace(property.name, cBuffer + property.offset);

				propertyIndexTemp++;
			}

			m_constantBufferList.emplace_back(cBuffer);
		}

		const UINT textureCount = shader->GetPropertyCount() - propertyIndexTemp;
		for (UINT i = 0; i < textureCount; i++)
		{
			auto& property = shader->GetPropertyByIndex(propertyIndexTemp);
			m_materialValueList.push_back(nullptr);
			m_materialValueMap.emplace(property.name, nullptr);

			propertyIndexTemp++;
		}
	}

	const std::wstring& Material::GetMaterialFilePath() const
	{
		return m_materialFilePath;
	}

	BOOL Material::existProperty(const std::string_view& name)
	{
		return m_materialValueMap.find(name.data()) == m_materialValueMap.end();
	}

	const Shader* Material::GetShader() const
	{
		return m_bindShader;
	}

	FLOAT Material::GetFloatByIndex(UINT index) const
	{
		return *static_cast<FLOAT*>(m_materialValueList.at(index));
	}

	const Float2& Material::GetFloat2ByIndex(UINT index) const
	{
		return *static_cast<Float2*>(m_materialValueList.at(index));
	}

	const Float3& Material::GetFloat3ByIndex(UINT index) const
	{
		return *static_cast<Float3*>(m_materialValueList.at(index));
	}

	const Float4& Material::GetFloat4ByIndex(UINT index) const
	{
		return *static_cast<Float4*>(m_materialValueList.at(index));
	}

	FLOAT Material::GetFloatByName(const std::string_view& name) const
	{
		return *static_cast<FLOAT*>(m_materialValueMap.at(name.data()));
	}

	const Float2& Material::GetFloat2ByName(const std::string_view& name) const
	{
		return *static_cast<Float2*>(m_materialValueMap.at(name.data()));
	}

	const Float3& Material::GetFloat3ByName(const std::string_view& name) const
	{
		return *static_cast<Float3*>(m_materialValueMap.at(name.data()));
	}

	const Float4& Material::GetFloat4ByName(const std::string_view& name) const
	{
		return *static_cast<Float4*>(m_materialValueMap.at(name.data()));
	}

	const Matrix2x2& Material::GetMatrix2ByIndex(UINT index) const
	{
		return *static_cast<Matrix2x2*>(m_materialValueList.at(index));
	}

	const Matrix3x3& Material::GetMatrix3ByIndex(UINT index) const
	{
		return *static_cast<Matrix3x3*>(m_materialValueList.at(index));
	}

	const Matrix4x4& Material::GetMatrix4ByIndex(UINT index) const
	{
		return *static_cast<Matrix4x4*>(m_materialValueList.at(index));
	}

	const Matrix2x2& Material::GetMatrix2ByName(const std::string_view& name) const
	{
		return *static_cast<Matrix2x2*>(m_materialValueMap.at(name.data()));
	}

	const Matrix3x3& Material::GetMatrix3ByName(const std::string_view& name) const
	{
		return *static_cast<Matrix3x3*>(m_materialValueMap.at(name.data()));
	}

	const Matrix4x4& Material::GetMatrix4ByName(const std::string_view& name) const
	{
		return *static_cast<Matrix4x4*>(m_materialValueMap.at(name.data()));
	}

	const Texture* Material::GetTextureByIndex(UINT index) const
	{
		return static_cast<Texture*>(m_materialValueList.at(index));
	}

	const Texture* Material::GetTextureByName(const std::string_view& name) const
	{
		return static_cast<Texture*>(m_materialValueMap.at(name.data()));
	}

	void Material::SetFloatByIndex(UINT index, FLOAT value) const
	{
		*static_cast<FLOAT*>(m_materialValueList.at(index)) = value;
	}

	void Material::SetFloat2ByIndex(UINT index, const Float2& value) const
	{
		*static_cast<Float2*>(m_materialValueList.at(index)) = value;
	}

	void Material::SetFloat3ByIndex(UINT index, const Float3& value) const
	{
		*static_cast<Float3*>(m_materialValueList.at(index)) = value;
	}

	void Material::SetFloat4ByIndex(UINT index, const Float4& value) const
	{
		*static_cast<Float4*>(m_materialValueList.at(index)) = value;
	}

	void Material::SetFloatByName(const std::string_view& name, const FLOAT& value) const
	{
		*static_cast<FLOAT*>(m_materialValueMap.at(name.data())) = value;
	}

	void Material::SetFloat2ByName(const std::string_view& name, const Float2& value) const
	{
		*static_cast<Float2*>(m_materialValueMap.at(name.data())) = value;
	}

	void Material::SetFloat3ByName(const std::string_view& name, const Float3& value) const
	{
		*static_cast<Float3*>(m_materialValueMap.at(name.data())) = value;
	}

	void Material::SetFloat4ByName(const std::string_view& name, const Float4& value) const
	{
		*static_cast<Float4*>(m_materialValueMap.at(name.data())) = value;
	}

	void Material::SetMatrix2ByIndex(UINT index, const Matrix2x2& value) const
	{
		*static_cast<Matrix2x2*>(m_materialValueList.at(index)) = value;
	}

	void Material::SetMatrix3ByIndex(UINT index, const Matrix3x3& value) const
	{
		*static_cast<Matrix3x3*>(m_materialValueList.at(index)) = value;
	}

	void Material::SetMatrix4ByIndex(UINT index, const Matrix4x4& value) const
	{
		*static_cast<Matrix4x4*>(m_materialValueList.at(index)) = value;
	}

	void Material::SetMatrix2ByName(const std::string_view& name, const Matrix2x2& value) const
	{
		*static_cast<Matrix2x2*>(m_materialValueMap.at(name.data())) = value;
	}

	void Material::SetMatrix3ByName(const std::string_view& name, const Matrix3x3& value) const
	{
		*static_cast<Matrix3x3*>(m_materialValueMap.at(name.data())) = value;
	}

	void Material::SetMatrix4ByName(const std::string_view& name, const Matrix4x4& value) const
	{
		*static_cast<Matrix4x4*>(m_materialValueMap.at(name.data())) = value;
	}

	void Material::SetTextureByIndex(UINT index, Texture* value)
	{
		auto& property = m_bindShader->GetPropertyByIndex(index);

		m_materialValueList.at(index) = value;
		m_materialValueMap.at(property.name) = value;
	}

	void Material::SetTextureByName(const std::string_view& name, Texture* value)
	{
		auto& property = m_bindShader->GetPropertyByName(name);

		m_materialValueList.at(property.index) = value;
		m_materialValueMap.at(name.data()) = value;
	}
}
