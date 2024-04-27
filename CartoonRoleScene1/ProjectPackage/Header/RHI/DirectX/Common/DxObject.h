#pragma once

#include <type_traits>
#include "DxDefine.h"

namespace XusoryEngine
{
	template <typename DxObjT>
	class DxObject
	{
		static_assert(std::is_base_of_v<IUnknown, DxObjT>);
		using DxObjectCom = Microsoft::WRL::ComPtr<DxObjT>;

	public:
		DxObject() = default;
		DEFAULT_COPY_OPERATOR(DxObject);
		DEFAULT_MOVE_OPERATOR(DxObject);
		virtual ~DxObject() = default;

		DxObjT* operator->() const
		{
			return m_dxObject.Get();
		}

		BOOL isCreated() const
		{
			return m_dxObject.Get() != nullptr;
		}

		DxObjT* GetDxObjectPtr() const
		{
			return m_dxObject.Get();
		}

		DxObjT* const* GetConstDxObjectAddressOf() const
		{
			return m_dxObject.GetAddressOf();
		}

		DxObjT** GetDxObjectAddressOf()
		{
			return m_dxObject.GetAddressOf();
		}

		DxObjectCom& GetDxObjectComRef()
		{
			return m_dxObject;
		}

		template <typename UpgradeObjT>
		DxObject<UpgradeObjT> UpgradeObject()
		{
			DxObject<UpgradeObjT> dxObjTemp;
			m_dxObject->QueryInterface(IID_PPV_ARGS(dxObjTemp.GetDxObjectAddressOf()));
			return dxObjTemp;
		}

		virtual void ReSet()
		{
			m_dxObject.Reset();
		}

	protected:
		DxObjectCom m_dxObject;
	};
}
