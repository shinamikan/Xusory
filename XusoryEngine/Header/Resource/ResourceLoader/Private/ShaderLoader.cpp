#include "../ShaderLoader.h"

namespace XusoryEngine
{
	void DxShaderLoader::LoadShader(Shader* shader, const std::wstring_view& path)
	{
		DxShaderCompiler shaderCompiler;
		shaderCompiler.CompileShader(path, shader->GetShaderEntryPoint(), nullptr);

		UINT propertyIndexTemp = 0;
		for (const auto& cBuffer : shaderCompiler.m_constantBufferDescMap)
		{
			const auto& cBufferDesc = cBuffer.first;
			ShaderCBufferProperty cBufferProperty;
			cBufferProperty.name = cBufferDesc.bufferName;
			cBufferProperty.size = cBufferDesc.Size;
			cBufferProperty.variableNum = cBufferDesc.Variables;
			cBufferProperty.slot = cBufferDesc.bindPoint;
			cBufferProperty.space = cBufferDesc.space;
			shader->m_shaderCBufferPropertyList.push_back(std::move(cBufferProperty));

			for (const auto& variableDesc : cBuffer.second)
			{
				ShaderProperty property;
				property.name = variableDesc.variableName;
				property.index = propertyIndexTemp;
				property.offset = variableDesc.StartOffset;
				property.slot = cBuffer.first.bindPoint;
				property.space = cBuffer.first.space;
				if (variableDesc.typeName == "int") property.propertyType = ShaderPropertyType::INT;
				else if (variableDesc.typeName == "float") property.propertyType = ShaderPropertyType::FLOAT;
				else if (variableDesc.typeName == "float2") property.propertyType = ShaderPropertyType::FLOAT2;
				else if (variableDesc.typeName == "float3") property.propertyType = ShaderPropertyType::FLOAT3;
				else if (variableDesc.typeName == "float4") property.propertyType = ShaderPropertyType::FLOAT4;
				else if (variableDesc.typeName == "float2x2") property.propertyType = ShaderPropertyType::MATRIX2;
				else if (variableDesc.typeName == "float3x3") property.propertyType = ShaderPropertyType::MATRIX3;
				else if (variableDesc.typeName == "float4x4") property.propertyType = ShaderPropertyType::MATRIX4;
				else
				{
					ThrowWithErrName(RuntimeError, "Unrecognized property type");
				}
				property.dimension = TextureDimension::UNKNOWN;

				propertyIndexTemp++;
				shader->m_shaderPropertyList.push_back(std::move(property));
				shader->m_shaderPropertyMap.emplace(variableDesc.variableName, *(shader->m_shaderPropertyList.end() - 1));
			}
		}
		for (const auto& resourceDesc : shaderCompiler.m_shaderResourceDescList)
		{
			ShaderProperty property;
			property.name = resourceDesc.resourceName;
			property.index = propertyIndexTemp;
			property.offset = 0;
			property.slot = resourceDesc.BindPoint;
			property.space = resourceDesc.Space;
			property.propertyType = ShaderPropertyType::TEXTURE;
			property.dimension = static_cast<TextureDimension>(resourceDesc.Dimension);

			propertyIndexTemp++;
			shader->m_shaderPropertyList.push_back(std::move(property));
			shader->m_shaderPropertyMap.emplace(resourceDesc.resourceName, *(shader->m_shaderPropertyList.end() - 1));
		}

		for (UINT i = 0; i < 5; i++)
		{
			auto* shaderBlob = shaderCompiler.GetShaderByteCode(i);

			ShaderByte shaderByte;
			if (shaderBlob != nullptr)
			{
				shaderByte.byteCode = std::vector<BYTE>(shaderBlob->GetBufferSize());
				shaderByte.byteSize = shaderBlob->GetBufferSize();

				memcpy(shaderByte.byteCode.data(), shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize());
			}
			else
			{
				shaderByte.byteSize = NULL;
			}

			shader->m_shaderByteList.at(i) = std::move(shaderByte);
		}
	}
}
