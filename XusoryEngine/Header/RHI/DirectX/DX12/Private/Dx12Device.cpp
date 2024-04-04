#include "../Dx12Device.h"
#include "../../DxFactory.h"

namespace XusoryEngine
{
	void Dx12Device::Create(const DxFactory* factory)
	{
		const HRESULT hardwareResult = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(GetDxObjectAddressOf()));
		if (FAILED(hardwareResult))
		{
			Microsoft::WRL::ComPtr<IDXGIAdapter> warpAdapter;

			ThrowIfDxFailed((*factory)->EnumWarpAdapter(IID_PPV_ARGS(warpAdapter.GetAddressOf())));
			ThrowIfDxFailed(D3D12CreateDevice(warpAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(GetDxObjectAddressOf())));
		}
	}
}
