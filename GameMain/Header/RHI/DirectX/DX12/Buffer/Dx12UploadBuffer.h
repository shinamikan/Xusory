#pragma once

#include "Dx12Buffer.h"

namespace XusoryEngine
{
	class Dx12Device;
	class Dx12UploadBuffer : public Dx12Buffer
	{
	public:
		explicit Dx12UploadBuffer(BOOL isConstantBuffer);
		DELETE_COPY_OPERATOR(Dx12UploadBuffer);
		DELETE_MOVE_OPERATOR(Dx12UploadBuffer);
		~Dx12UploadBuffer() override;

		void CreateUploadBuffer(const Dx12Device* device, UINT64 size);
		void CopyDataToBuffer(const void* srcData) const;

	private:
		BOOL m_isConstantBuffer = false;
		UINT64 m_bufferSize = 0;
		UINT64 m_originalBufferSize = 0;

		void* m_mappedData = nullptr;
	};
}
