#pragma once

#include "../Common/DxObject.h"

namespace XusoryEngine
{
	constexpr UINT8 ROOT_PARA_CONSTANTS_SIZE = 1;
	constexpr UINT8 ROOT_PARA_VIEW_SIZE = 2;
	constexpr UINT8 ROOT_PARA_DESC_TABLE_SIZE = 1;

	class Dx12Device;
	class Dx12RootSignature : public DxObject<ID3D12RootSignature>
	{
	public:
		Dx12RootSignature() = default;

		void Create(const Dx12Device* device);
		void ReSet() override;

		D3D12_ROOT_PARAMETER_TYPE GetParameterType(UINT parameterIndex) const;

		void AddConstants(UINT constantValueNum, UINT shaderRegister, UINT registerSpace = 0);
		void AddConstantBufferView(UINT shaderRegister, UINT registerSpace = 0);
		void AddShaderResourceView(UINT shaderRegister, UINT registerSpace = 0);
		void AddUnorderedAccessView(UINT shaderRegister, UINT registerSpace = 0);
		void AddDescriptorRange(D3D12_DESCRIPTOR_RANGE_TYPE rangeType, UINT descriptorNum, UINT shaderRegister, UINT registerSpace = 0);
		void AddDescriptorTable(D3D12_DESCRIPTOR_RANGE_TYPE rangeType, UINT descriptorNum, UINT shaderRegister, UINT registerSpace = 0);
		void AddStaticSampler(UINT shaderRegister, D3D12_FILTER filter, D3D12_TEXTURE_ADDRESS_MODE addressMode);
		void AddStaticSampler(UINT shaderRegister, D3D12_FILTER filter,
			D3D12_TEXTURE_ADDRESS_MODE addressModeX,
			D3D12_TEXTURE_ADDRESS_MODE addressModeY,
			D3D12_TEXTURE_ADDRESS_MODE addressModeZ);

	private:
		void AddSize(UINT8 size);

		UINT8 m_rootSignatureSize = 0;

		std::vector<std::vector<D3D12_DESCRIPTOR_RANGE>> m_rangeTempList;
		std::vector<D3D12_ROOT_PARAMETER> m_parameterList;
		std::vector<D3D12_STATIC_SAMPLER_DESC> m_staticSamplerList;
	};
}
