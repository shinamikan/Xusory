#pragma once

#include "../../RHI/RHI.h"
#include "../Math/Math.h"

namespace XusoryEngine
{
	class Shader;
	class Texture;
	class Material
	{
	public:
		explicit Material(const Shader* shader);

		const std::wstring& GetMaterialFilePath() const;
		BOOL existProperty(const std::string_view& name);

		const Shader* GetShader() const;
		FLOAT GetFloatByIndex(UINT index) const;
		const Float2& GetFloat2ByIndex(UINT index) const;
		const Float3& GetFloat3ByIndex(UINT index) const;
		const Float4& GetFloat4ByIndex(UINT index) const;
		FLOAT GetFloatByName(const std::string_view& name) const;
		const Float2& GetFloat2ByName(const std::string_view& name) const;
		const Float3& GetFloat3ByName(const std::string_view& name) const;
		const Float4& GetFloat4ByName(const std::string_view& name) const;

		const Matrix2x2& GetMatrix2ByIndex(UINT index) const;
		const Matrix3x3& GetMatrix3ByIndex(UINT index) const;
		const Matrix4x4& GetMatrix4ByIndex(UINT index) const;
		const Matrix2x2& GetMatrix2ByName(const std::string_view& name) const;
		const Matrix3x3& GetMatrix3ByName(const std::string_view& name) const;
		const Matrix4x4& GetMatrix4ByName(const std::string_view& name) const;

		const Texture* GetTextureByIndex(UINT index) const;
		const Texture* GetTextureByName(const std::string_view& name) const;

		void SetFloatByIndex(UINT index, FLOAT value) const;
		void SetFloat2ByIndex(UINT index, const Float2& value) const;
		void SetFloat3ByIndex(UINT index, const Float3& value) const;
		void SetFloat4ByIndex(UINT index, const Float4& value) const;
		void SetFloatByName(const std::string_view& name, const FLOAT& value) const;
		void SetFloat2ByName(const std::string_view& name, const Float2& value) const;
		void SetFloat3ByName(const std::string_view& name, const Float3& value) const;
		void SetFloat4ByName(const std::string_view& name, const Float4& value) const;

		void SetMatrix2ByIndex(UINT index, const Matrix2x2& value) const;
		void SetMatrix3ByIndex(UINT index, const Matrix3x3& value) const;
		void SetMatrix4ByIndex(UINT index, const Matrix4x4& value) const;
		void SetMatrix2ByName(const std::string_view& name, const Matrix2x2& value) const;
		void SetMatrix3ByName(const std::string_view& name, const Matrix3x3& value) const;
		void SetMatrix4ByName(const std::string_view& name, const Matrix4x4& value) const;

		void SetTextureByIndex(UINT index, Texture* value);
		void SetTextureByName(const std::string_view& name, Texture* value);

	private:
		std::wstring m_materialFilePath;

		const Shader* m_bindShader;
		std::vector<std::unique_ptr<BYTE>> m_constantBufferList;

		std::vector<void*> m_materialValueList;
		std::unordered_map<std::string, void*> m_materialValueMap;
	};
}
