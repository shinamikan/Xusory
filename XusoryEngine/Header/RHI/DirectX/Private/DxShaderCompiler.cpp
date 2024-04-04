#include "../DxShaderCompiler.h"

namespace XusoryEngine
{
	ID3DBlob* DxShaderCompiler::GetVertexShader() const
	{
		return m_shaderBytesArray.at(0).Get();
	}

	ID3DBlob* DxShaderCompiler::GetPixelShader() const
	{
		return m_shaderBytesArray.at(1).Get();
	}

	ID3DBlob* DxShaderCompiler::GetDomainShader() const
	{
		return m_shaderBytesArray.at(2).Get();
	}

	ID3DBlob* DxShaderCompiler::GetHullShader() const
	{
		return m_shaderBytesArray.at(3).Get();
	}

	ID3DBlob* DxShaderCompiler::GetGeometryShader() const
	{
		return m_shaderBytesArray.at(4).Get();
	}

	ID3DBlob* DxShaderCompiler::GetShaderByteCode(UINT index) const
	{
		CaptureNoReturnFunc(return m_shaderBytesArray.at(index).Get());
	}

	void DxShaderCompiler::CompileShader(const std::wstring_view& shaderFilePath, const std::array<std::string, 5>& shaderEntryPointList, const D3D_SHADER_MACRO* defines)
	{
		File::TryToFindFile(shaderFilePath);

		std::string shaderTarget[5] = { "vs_5_1", "ps_5_1", "ds_5_1", "hs_5_1", "gs_5_1" };
		for (UINT i = 0; i < 5; i++)
		{
			if (shaderEntryPointList[i].empty())
			{
				continue;
			}

			Microsoft::WRL::ComPtr<ID3DBlob> errors;
			ThrowIfDxFailed(D3DCompileFromFile(shaderFilePath.data(), defines, D3D_COMPILE_STANDARD_FILE_INCLUDE,
				shaderEntryPointList[i].data(), shaderTarget[i].data(),
				D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, NULL, m_shaderBytesArray[i].GetAddressOf(), errors.GetAddressOf()));

			Microsoft::WRL::ComPtr<ID3D12ShaderReflection> shaderReflection;
			ThrowIfDxFailed(D3DReflect(m_shaderBytesArray[i]->GetBufferPointer(),
				m_shaderBytesArray[i]->GetBufferSize(), IID_PPV_ARGS(shaderReflection.GetAddressOf())));

			D3D12_SHADER_DESC shaderDesc;
			ThrowIfDxFailed(shaderReflection.Get()->GetDesc(&shaderDesc));

			for (UINT j = 0; j < shaderDesc.ConstantBuffers; j++)
			{
				ID3D12ShaderReflectionConstantBuffer* shaderReflectionCBuffer = shaderReflection.Get()->GetConstantBufferByIndex(j);

				D3D12_SHADER_CONSTANT_BUFFER_DESC constantBufferDesc;
				ThrowIfDxFailed(shaderReflectionCBuffer->GetDesc(&constantBufferDesc));
				constantBufferDesc.bufferName = constantBufferDesc.Name;
				for (UINT k = 0; k < shaderDesc.BoundResources; k++)
				{
					D3D12_SHADER_RESOURCE_DESC resourceDesc;
					ThrowIfDxFailed(shaderReflection->GetResourceBindingDesc(k, &resourceDesc));
					resourceDesc.resourceName = resourceDesc.Name;

					if (resourceDesc.Type == D3D_SIT_CBUFFER && constantBufferDesc.bufferName == resourceDesc.resourceName)
					{
						constantBufferDesc.bindPoint = resourceDesc.BindPoint;
						constantBufferDesc.bindCount = resourceDesc.BindCount;
						constantBufferDesc.space = resourceDesc.Space;
						break;
					}
				}

				if (m_constantBufferDescMap.find(constantBufferDesc) == m_constantBufferDescMap.end())
				{
					m_constantBufferDescMap[constantBufferDesc] = std::vector<D3D12_SHADER_VARIABLE_TYPE_DESC>();
				}
				else
				{
					continue;
				}

				for (UINT k = 0; k < constantBufferDesc.Variables; k++)
				{
					ID3D12ShaderReflectionVariable* cBufferVariable = shaderReflectionCBuffer->GetVariableByIndex(k);

					D3D12_SHADER_VARIABLE_DESC cBufferVariableDesc;
					ThrowIfDxFailed(cBufferVariable->GetDesc(&cBufferVariableDesc));

					ID3D12ShaderReflectionType* cBufferType = cBufferVariable->GetType();
					D3D12_SHADER_TYPE_DESC cBufferTypeDesc;
					ThrowIfDxFailed(cBufferType->GetDesc(&cBufferTypeDesc));

					D3D12_SHADER_VARIABLE_TYPE_DESC propertyDesc(cBufferVariableDesc, cBufferTypeDesc);
					propertyDesc.variableName = propertyDesc.D3D12_SHADER_VARIABLE_DESC::Name;
					propertyDesc.typeName = propertyDesc.D3D12_SHADER_TYPE_DESC::Name;

					auto& variableList = m_constantBufferDescMap[constantBufferDesc];
					if (std::find(variableList.begin(), variableList.end(), propertyDesc) == variableList.end())
					{
						variableList.push_back(std::move(propertyDesc));
					}
				}
			}

			for (UINT j = 0; j < shaderDesc.BoundResources; j++)
			{
				D3D12_SHADER_RESOURCE_DESC resourceDesc;
				ThrowIfDxFailed(shaderReflection->GetResourceBindingDesc(j, &resourceDesc));
				resourceDesc.resourceName = resourceDesc.Name;

				if (resourceDesc.Type == D3D_SIT_TEXTURE)
				{
					if (std::find(m_shaderResourceDescList.begin(), m_shaderResourceDescList.end(), resourceDesc) == m_shaderResourceDescList.end())
					{
						m_shaderResourceDescList.push_back(std::move(resourceDesc));
					}
				}
			}
		}
	}
}
