#include "../Dx12RootSignature.h"
#include "../Dx12Device.h"

namespace XusoryEngine
{
	void Dx12RootSignature::Create(const Dx12Device* device)
	{
		const CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(
			static_cast<UINT>(m_parameterList.size()), m_parameterList.data(),
			static_cast<UINT>(m_staticSamplerList.size()), m_staticSamplerList.data(),
			D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

		Microsoft::WRL::ComPtr<ID3DBlob> serializedRootSig = nullptr;
		Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;
		ThrowIfDxFailed(D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1,
			serializedRootSig.GetAddressOf(), errorBlob.GetAddressOf()));
		if (errorBlob != nullptr)
		{
			::OutputDebugStringA(static_cast<char*>(errorBlob->GetBufferPointer()));
		}

		ThrowIfDxFailed((*device)->CreateRootSignature(0, serializedRootSig->GetBufferPointer(), serializedRootSig->GetBufferSize(),
			IID_PPV_ARGS(GetDxObjectAddressOf())));

		m_rangeTempList.clear();
	}

	void Dx12RootSignature::ReSet()
	{
		DxObject::ReSet();
		m_rangeTempList.clear();
		m_parameterList.clear();
		m_staticSamplerList.clear();
	}

	BOOL Dx12RootSignature::IsRangeTempListNull() const
	{
		return m_rangeTempList.empty();
	}

	UINT Dx12RootSignature::GetParameterNum() const
	{
		return static_cast<UINT>(m_parameterList.size());
	}

	D3D12_ROOT_PARAMETER_TYPE Dx12RootSignature::GetParameterType(UINT parameterIndex) const
	{
		if (parameterIndex >= m_parameterList.size())
		{
			ThrowWithErrName(DxRuntimeError, "Index out of parameter list range");
		}
		return m_parameterList.at(parameterIndex).ParameterType;
	}

	void Dx12RootSignature::AddConstants(UINT constantValueNum, UINT shaderRegister, UINT registerSpace)
	{
		AddSize(ROOT_PARA_CONSTANTS_SIZE);

		CD3DX12_ROOT_PARAMETER rootParameter;
		rootParameter.InitAsConstants(constantValueNum, shaderRegister, registerSpace, D3D12_SHADER_VISIBILITY_ALL);
		m_parameterList.push_back(std::move(rootParameter));
	}

	void Dx12RootSignature::AddConstantBufferView(UINT shaderRegister, UINT registerSpace)
	{
		AddSize(ROOT_PARA_VIEW_SIZE);

		CD3DX12_ROOT_PARAMETER rootParameter;
		rootParameter.InitAsConstantBufferView(shaderRegister, registerSpace, D3D12_SHADER_VISIBILITY_ALL);
		m_parameterList.push_back(std::move(rootParameter));
	}

	void Dx12RootSignature::AddShaderResourceView(UINT shaderRegister, UINT registerSpace)
	{
		AddSize(ROOT_PARA_VIEW_SIZE);

		CD3DX12_ROOT_PARAMETER rootParameter;
		rootParameter.InitAsShaderResourceView(shaderRegister, registerSpace, D3D12_SHADER_VISIBILITY_ALL);
		m_parameterList.push_back(std::move(rootParameter));
	}

	void Dx12RootSignature::AddUnorderedAccessView(UINT shaderRegister, UINT registerSpace)
	{
		AddSize(ROOT_PARA_VIEW_SIZE);

		CD3DX12_ROOT_PARAMETER rootParameter;
		rootParameter.InitAsUnorderedAccessView(shaderRegister, registerSpace, D3D12_SHADER_VISIBILITY_ALL);
		m_parameterList.push_back(std::move(rootParameter));
	}

	void Dx12RootSignature::AddDescriptorRange(D3D12_DESCRIPTOR_RANGE_TYPE rangeType, UINT descriptorNum, UINT shaderRegister, UINT registerSpace)
	{
		if (m_rangeTempList.empty())
		{
			m_rangeTempList.emplace_back();
		}

		CD3DX12_DESCRIPTOR_RANGE range;
		range.Init(rangeType, descriptorNum, shaderRegister, registerSpace);
		(m_rangeTempList.end() - 1)->push_back(std::move(range));
	}

	void Dx12RootSignature::AddDescriptorTable()
	{
		AddSize(ROOT_PARA_DESC_TABLE_SIZE);

		const auto rangeList = m_rangeTempList.end() - 1;
		CD3DX12_ROOT_PARAMETER rootParameter;
		rootParameter.InitAsDescriptorTable(static_cast<UINT>(rangeList->size()), rangeList->data(), D3D12_SHADER_VISIBILITY_ALL);
		m_parameterList.push_back(std::move(rootParameter));

		m_rangeTempList.emplace_back();
	}

	void Dx12RootSignature::AddStaticSampler(UINT shaderRegister, D3D12_FILTER filter, D3D12_TEXTURE_ADDRESS_MODE addressMode)
	{
		CD3DX12_STATIC_SAMPLER_DESC sampler(shaderRegister, filter,
			addressMode,
			addressMode,
			addressMode);
		m_staticSamplerList.push_back(std::move(sampler));
	}

	void Dx12RootSignature::AddStaticSampler(UINT shaderRegister, D3D12_FILTER filter, D3D12_TEXTURE_ADDRESS_MODE addressModeX, D3D12_TEXTURE_ADDRESS_MODE addressModeY, D3D12_TEXTURE_ADDRESS_MODE addressModeZ)
	{
		CD3DX12_STATIC_SAMPLER_DESC sampler(shaderRegister, filter,
			addressModeX,
			addressModeY,
			addressModeZ);
		m_staticSamplerList.push_back(std::move(sampler));
	}

	void Dx12RootSignature::AddSize(UINT8 size)
	{
		if (m_rootSignatureSize + size > 64)
		{
			ThrowWithErrName(DxLogicError, "Root signature size exceeds the range");
		}
		else
		{
			m_rootSignatureSize += size;
		}
	}
}
