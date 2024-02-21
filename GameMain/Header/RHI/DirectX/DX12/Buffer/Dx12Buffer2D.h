#pragma once

#include "Dx12Buffer.h"
#include "../Dx12DescriptorHeap.h"

namespace XusoryEngine
{
	class Dx12Device;
	class Dx12Buffer2D : public Dx12Buffer
	{
	public:
		Dx12Buffer2D();

		void CreateTex2DBuffer(const Dx12Device* device,
			D3D12_RESOURCE_STATES initState, D3D12_RESOURCE_FLAGS flag, const D3D12_CLEAR_VALUE* clearValue,
			UINT width, UINT height, UINT16 arraySize = 1, UINT16 mipLevels = 0,
			UINT sampleCount = 1, UINT sampleQuality = 0, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);
		void CreateTex2DCubeBuffer(const Dx12Device* device,
			D3D12_RESOURCE_STATES initState, D3D12_RESOURCE_FLAGS flag, const D3D12_CLEAR_VALUE* clearValue,
			UINT width, UINT height, UINT16 mipLevels = 0,
			UINT sampleCount = 1, UINT sampleQuality = 0, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);

		DXGI_FORMAT GetFormat() const;
		UINT64 GetWidth() const;
		UINT GetHeight() const;
		UINT16 GetArraySize() const;
		UINT16 GetMipLevels() const;
		UINT GetSampleCount() const;
		UINT GetSampleQuality() const;
	};
}
