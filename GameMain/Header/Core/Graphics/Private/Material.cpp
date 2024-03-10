#include "../Material.h"
#include "../Texture.h"

namespace XusoryEngine
{
	Material::Material(const Shader* shader) : m_bindShader(shader) { }

	BOOL Material::existProperty(const std::string_view& name)
	{
		return m_materialValueMap.find(name.data()) == m_materialValueMap.end();
	}

	const std::wstring& Material::GetMaterialFilePath() const
	{
		return m_materialFilePath;
	}

	const Shader* Material::GetShader() const
	{
		return m_bindShader;
	}

	UINT Material::GetPropertyNum() const
	{
		return static_cast<UINT>(m_constantBufferList.size());
	}

	UINT Material::GetConstantPropertyNum() const
	{
		return m_constantPropertyNum;
	}

	UINT Material::GetTexturePropertyNum() const
	{
		return m_texturePropertyNum;
	}

	FLOAT Material::GetFloatByIndex(UINT index) const
	{
		ThrowIfOutOfValueRange(index);
		return *static_cast<FLOAT*>(m_materialValueList.at(index));
	}

	const Float2& Material::GetFloat2ByIndex(UINT index) const
	{
		ThrowIfOutOfValueRange(index);
		return *static_cast<Float2*>(m_materialValueList.at(index));
	}

	const Float3& Material::GetFloat3ByIndex(UINT index) const
	{
		ThrowIfOutOfValueRange(index);
		return *static_cast<Float3*>(m_materialValueList.at(index));
	}

	const Float4& Material::GetFloat4ByIndex(UINT index) const
	{
		ThrowIfOutOfValueRange(index);
		return *static_cast<Float4*>(m_materialValueList.at(index));
	}

	FLOAT Material::GetFloatByName(const std::string_view& name) const
	{
		CaptureNoReturnFunc(return *static_cast<FLOAT*>(m_materialValueMap.at(name.data())));
	}

	const Float2& Material::GetFloat2ByName(const std::string_view& name) const
	{
		CaptureNoReturnFunc(return *static_cast<Float2*>(m_materialValueMap.at(name.data())));
	}

	const Float3& Material::GetFloat3ByName(const std::string_view& name) const
	{
		CaptureNoReturnFunc(return *static_cast<Float3*>(m_materialValueMap.at(name.data())));
	}

	const Float4& Material::GetFloat4ByName(const std::string_view& name) const
	{
		CaptureNoReturnFunc(return *static_cast<Float4*>(m_materialValueMap.at(name.data())));
	}

	const Matrix2x2& Material::GetMatrix2ByIndex(UINT index) const
	{
		ThrowIfOutOfValueRange(index);
		return *static_cast<Matrix2x2*>(m_materialValueList.at(index));
	}

	const Matrix3x3& Material::GetMatrix3ByIndex(UINT index) const
	{
		ThrowIfOutOfValueRange(index);
		return *static_cast<Matrix3x3*>(m_materialValueList.at(index));
	}

	const Matrix4x4& Material::GetMatrix4ByIndex(UINT index) const
	{
		ThrowIfOutOfValueRange(index);
		return *static_cast<Matrix4x4*>(m_materialValueList.at(index));
	}

	const Matrix2x2& Material::GetMatrix2ByName(const std::string_view& name) const
	{
		CaptureNoReturnFunc(return *static_cast<Matrix2x2*>(m_materialValueMap.at(name.data())));
	}

	const Matrix3x3& Material::GetMatrix3ByName(const std::string_view& name) const
	{
		CaptureNoReturnFunc(return *static_cast<Matrix3x3*>(m_materialValueMap.at(name.data())));
	}

	const Matrix4x4& Material::GetMatrix4ByName(const std::string_view& name) const
	{
		CaptureNoReturnFunc(return *static_cast<Matrix4x4*>(m_materialValueMap.at(name.data())));
	}

	const Texture* Material::GetTextureByIndex(UINT index) const
	{
		ThrowIfOutOfValueRange(index);
		return static_cast<Texture*>(m_materialValueList.at(index));
	}

	const Texture* Material::GetTextureByName(const std::string_view& name) const
	{
		CaptureNoReturnFunc(return static_cast<Texture*>(m_materialValueMap.at(name.data())));
	}

	void Material::SetFloatByIndex(UINT index, FLOAT value) const
	{
		ThrowIfOutOfValueRange(index);
		*static_cast<FLOAT*>(m_materialValueList.at(index)) = value;
	}

	void Material::SetFloat2ByIndex(UINT index, const Float2& value) const
	{
		ThrowIfOutOfValueRange(index);
		*static_cast<Float2*>(m_materialValueList.at(index)) = value;
	}

	void Material::SetFloat3ByIndex(UINT index, const Float3& value) const
	{
		ThrowIfOutOfValueRange(index);
		*static_cast<Float3*>(m_materialValueList.at(index)) = value;
	}

	void Material::SetFloat4ByIndex(UINT index, const Float4& value) const
	{
		ThrowIfOutOfValueRange(index);
		*static_cast<Float4*>(m_materialValueList.at(index)) = value;
	}

	void Material::SetFloatByName(const std::string_view& name, const FLOAT& value) const
	{
		CaptureNoReturnFunc(*static_cast<FLOAT*>(m_materialValueMap.at(name.data())) = value);
	}

	void Material::SetFloat2ByName(const std::string_view& name, const Float2& value) const
	{
		CaptureNoReturnFunc(*static_cast<Float2*>(m_materialValueMap.at(name.data())) = value);
	}

	void Material::SetFloat3ByName(const std::string_view& name, const Float3& value) const
	{
		CaptureNoReturnFunc(*static_cast<Float3*>(m_materialValueMap.at(name.data())) = value);
	}

	void Material::SetFloat4ByName(const std::string_view& name, const Float4& value) const
	{
		CaptureNoReturnFunc(*static_cast<Float4*>(m_materialValueMap.at(name.data())) = value);
	}

	void Material::SetMatrix2ByIndex(UINT index, const Matrix2x2& value) const
	{
		ThrowIfOutOfValueRange(index);
		*static_cast<Matrix2x2*>(m_materialValueList.at(index)) = value;
	}

	void Material::SetMatrix3ByIndex(UINT index, const Matrix3x3& value) const
	{
		ThrowIfOutOfValueRange(index);
		*static_cast<Matrix3x3*>(m_materialValueList.at(index)) = value;
	}

	void Material::SetMatrix4ByIndex(UINT index, const Matrix4x4& value) const
	{
		ThrowIfOutOfValueRange(index);
		*static_cast<Matrix4x4*>(m_materialValueList.at(index)) = value;
	}

	void Material::SetMatrix2ByName(const std::string_view& name, const Matrix2x2& value) const
	{
		CaptureNoReturnFunc(*static_cast<Matrix2x2*>(m_materialValueMap.at(name.data())) = value);
	}

	void Material::SetMatrix3ByName(const std::string_view& name, const Matrix3x3& value) const
	{
		CaptureNoReturnFunc(*static_cast<Matrix3x3*>(m_materialValueMap.at(name.data())) = value);
	}

	void Material::SetMatrix4ByName(const std::string_view& name, const Matrix4x4& value) const
	{
		CaptureNoReturnFunc(*static_cast<Matrix4x4*>(m_materialValueMap.at(name.data())) = value);
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

	void Material::BindShader()
	{
		UINT propertyIndexTemp = 0;
		for (UINT i = 0; i < m_bindShader->GetCBufferCount(); i++)
		{
			auto& cBufferProperty = m_bindShader->GetCBufferProperty(i);
			auto* cBuffer = new BYTE[cBufferProperty.size];

			for (UINT j = 0; j < cBufferProperty.variableNum; j++)
			{
				auto& property = m_bindShader->GetPropertyByIndex(propertyIndexTemp);
				m_materialValueList.push_back(cBuffer + property.offset);
				m_materialValueMap.emplace(property.name, cBuffer + property.offset);

				propertyIndexTemp++;
			}

			m_constantBufferList.emplace_back(cBuffer);
		}

		m_constantPropertyNum = propertyIndexTemp;
		m_texturePropertyNum = m_bindShader->GetPropertyCount() - propertyIndexTemp;

		for (UINT i = 0; i < m_texturePropertyNum; i++)
		{
			auto& property = m_bindShader->GetPropertyByIndex(propertyIndexTemp);
			m_materialValueList.push_back(nullptr);
			m_materialValueMap.emplace(property.name, nullptr);

			propertyIndexTemp++;
		}
	}

	void Material::ThrowIfOutOfValueRange(UINT index) const
	{
		if (index >= m_materialValueList.size())
		{
			ThrowWithErrName(RuntimeError, "Index out of material value list range");
		}
	}
}
