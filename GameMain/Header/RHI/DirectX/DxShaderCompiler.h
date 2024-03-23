#pragma once

#include <unordered_map>
#include <vector>
#include "Common/DxDefine.h"

namespace XusoryEngine
{
	enum class ShaderType
	{
		VERTEX_SHADER = 0,
		PIXEL_SHADER,
		DOMAIN_SHADER,
		HULL_SHADER,
		GEOMETRY_SHADER
	};

	struct D3D12_SHADER_CONSTANT_BUFFER_DESC : D3D12_SHADER_BUFFER_DESC
	{
		std::string bufferName;
		UINT bindPoint;
		UINT bindCount;
		UINT space;
	};

	struct ShaderBufferDescHash
	{
		std::size_t operator()(const D3D12_SHADER_CONSTANT_BUFFER_DESC& desc) const
		{
			return std::hash<std::string>{}(desc.bufferName);
		}
	};

	struct ShaderBufferDescEqual
	{
		std::size_t operator()(const D3D12_SHADER_CONSTANT_BUFFER_DESC& lhs, const D3D12_SHADER_CONSTANT_BUFFER_DESC& rhs) const
		{
			return lhs.bufferName == rhs.bufferName;
		}
	};

	struct D3D12_SHADER_VARIABLE_TYPE_DESC :
		D3D12_SHADER_VARIABLE_DESC, D3D12_SHADER_TYPE_DESC
	{
		D3D12_SHADER_VARIABLE_TYPE_DESC(const D3D12_SHADER_VARIABLE_DESC& varDesc, const D3D12_SHADER_TYPE_DESC& typeDesc)
			: D3D12_SHADER_VARIABLE_DESC(varDesc), D3D12_SHADER_TYPE_DESC(typeDesc) {}

		BOOL operator==(const D3D12_SHADER_VARIABLE_TYPE_DESC& rhs) const
		{
			return variableName == rhs.variableName && typeName == rhs.typeName;
		}

		std::string variableName;
		std::string typeName;
	};

	typedef struct D3D12_SHADER_RESOURCE_DESC : D3D12_SHADER_INPUT_BIND_DESC
	{
		BOOL operator==(const D3D12_SHADER_RESOURCE_DESC& rhs) const
		{
			return resourceName == rhs.resourceName;
		}

		std::string resourceName;
	} D3D12_UNORDERED_ACCESS_DESC;

	class DxShaderCompiler
	{
	public:
		ID3DBlob* GetVertexShader() const;
		ID3DBlob* GetPixelShader() const;
		ID3DBlob* GetDomainShader() const;
		ID3DBlob* GetHullShader() const;
		ID3DBlob* GetGeometryShader() const;
		ID3DBlob* GetShaderByteCode(UINT index) const;

		void CompileShader(const std::wstring_view& shaderFilePath, const std::array<std::string, 5>& shaderEntryPointList, const D3D_SHADER_MACRO* defines);

		std::unordered_map<D3D12_SHADER_CONSTANT_BUFFER_DESC, std::vector<D3D12_SHADER_VARIABLE_TYPE_DESC>, ShaderBufferDescHash, ShaderBufferDescEqual> m_constantBufferDescMap;
		std::vector<D3D12_SHADER_RESOURCE_DESC> m_shaderResourceDescList;

	private:
		std::array<Microsoft::WRL::ComPtr<ID3DBlob>, 5> m_shaderBytesArray;
	};
}
