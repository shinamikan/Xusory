#pragma once

#include "Dx12Buffer.h"

namespace XusoryEngine
{
	class Dx12Device;
	class Dx12Buffer1D : public Dx12Buffer
	{
	public:
		Dx12Buffer1D();

		void CreateFixedBuffer(const Dx12Device* device, D3D12_RESOURCE_STATES initState, D3D12_RESOURCE_FLAGS flag, UINT64 size);
		void CreateTex1DBuffer(const Dx12Device* device, D3D12_RESOURCE_STATES initState, D3D12_RESOURCE_FLAGS flag, UINT64 size,
			UINT16 arraySize = 1, UINT16 mipLevels = 0, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);

		UINT64 GetSize() const;
		UINT16 GetArraySize() const;
		UINT16 GetMipLevels() const;
	};
}
