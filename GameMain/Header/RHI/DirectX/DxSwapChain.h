#pragma once

#include "Common/DxObject.h"

namespace XusoryEngine
{
	class DxFactory;
	class DxSwapChain : public DxObject<IDXGISwapChain3>
	{
	public:
		DxSwapChain() = default;

		void Create(const DxFactory* factory, IUnknown* deviceOrDx12CommandQueue, 
			WinId winId, UINT width, UINT height, DXGI_FORMAT format, UINT bufferCount,
			DXGI_USAGE usage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
			DXGI_SCALING scaling = DXGI_SCALING_STRETCH, DXGI_SWAP_EFFECT swapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD,
			DXGI_ALPHA_MODE alphaMode = DXGI_ALPHA_MODE_UNSPECIFIED, UINT flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);

		DXGI_FORMAT GetFormat() const;
		UINT GetWidth() const;
		UINT GetHeight() const;
		UINT GetBackBufferCount() const;
		UINT GetCurrentBackBufferIndex() const;

		void ResizeBuffer(UINT width, UINT height) const;
		void Present(UINT SyncState) const;

	private:
		DXGI_SWAP_CHAIN_DESC1 m_swapChainDesc;
		BOOL m_isFullScreen = false;
	};
}
