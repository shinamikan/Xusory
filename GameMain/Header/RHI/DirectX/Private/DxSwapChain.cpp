#include "../DxSwapChain.h"
#include "../DxFactory.h"

namespace XusoryEngine
{
	void DxSwapChain::Create(const DxFactory* factory, IUnknown* deviceOrDx12CommandQueue,
		const WinId& winId, UINT width, UINT height, DXGI_FORMAT format, UINT bufferCount,
		DXGI_USAGE usage, DXGI_SCALING scaling, DXGI_SWAP_EFFECT swapEffect, DXGI_ALPHA_MODE alphaMode, UINT flags)
	{
		m_swapChainDesc = {};
		m_swapChainDesc.Width = width;
		m_swapChainDesc.Height = height;
		m_swapChainDesc.Format = format;
		m_swapChainDesc.Stereo = false;
		m_swapChainDesc.SampleDesc.Count = 1;
		m_swapChainDesc.SampleDesc.Quality = 0;
		m_swapChainDesc.BufferUsage = usage;
		m_swapChainDesc.BufferCount = bufferCount;
		m_swapChainDesc.Scaling = scaling;
		m_swapChainDesc.SwapEffect = swapEffect;
		m_swapChainDesc.AlphaMode = alphaMode;
		m_swapChainDesc.Flags = flags;

		DxObject<IDXGISwapChain1> swapChainTemp;
		ThrowIfDxFailed((*factory)->CreateSwapChainForHwnd(deviceOrDx12CommandQueue, winId, &m_swapChainDesc,
			nullptr, nullptr, swapChainTemp.GetDxObjectAddressOf()));
		swapChainTemp->QueryInterface(IID_PPV_ARGS(GetDxObjectAddressOf()));
	}

	DXGI_FORMAT DxSwapChain::GetFormat() const
	{
		return m_swapChainDesc.Format;
	}

	UINT DxSwapChain::GetWidth() const
	{
		return m_swapChainDesc.Width;
	}

	UINT DxSwapChain::GetHeight() const
	{
		return m_swapChainDesc.Height;
	}

	UINT DxSwapChain::GetBackBufferCount() const
	{
		return m_swapChainDesc.BufferCount;
	}

	UINT DxSwapChain::GetCurrentBackBufferIndex() const
	{
		return (*this)->GetCurrentBackBufferIndex();
	}

	void DxSwapChain::ResizeBuffer(UINT width, UINT height) const
	{
		ThrowIfDxFailed((*this)->ResizeBuffers(GetBackBufferCount(), width, height,
			GetFormat(), DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH));
	}

	void DxSwapChain::Present(UINT SyncState) const
	{
		ThrowIfDxFailed((*this)->Present(SyncState, 0));
	}
}
