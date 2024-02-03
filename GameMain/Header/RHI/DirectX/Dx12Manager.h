#pragma once

#include "../IGraphicsManager.h"

#include "DX12/Dx12Device.h"
#include "DX12/Dx12RootSignature.h"
#include "DxFactory.h"

namespace XusoryEngine
{
	class Dx12Manager : public IGraphicsManager
	{
	public:
		Dx12Manager();
		DELETE_COPY_OPERATOR(Dx12Manager);
		DELETE_MOVE_OPERATOR(Dx12Manager);
		~Dx12Manager() override;

		void InitGraphicsObject(const void* renderWindow) override;
		void Resize(UINT width, UINT height) override;
		void Render() override;

	private:
		void CreateFactoryDevice();
		void CreateCommonRootSignature();

		DxFactory* m_factory = nullptr;
		Dx12Device* m_device = nullptr;

		Dx12RootSignature* m_commonRootSignature = nullptr;
	};
}
