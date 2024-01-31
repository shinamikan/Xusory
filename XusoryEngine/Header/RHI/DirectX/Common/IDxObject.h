#pragma once

#include <type_traits>
#include "DxInclude.h"

namespace XusoryEngine
{
	template <typename DxObjT>
	class IDxObject
	{
		static_assert(std::is_base_of_v<IUnknown, DxObjT>);
		using DxObjectCom = Microsoft::WRL::ComPtr<DxObjT>;

	public:
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
		IDxObject<UpgradeObjT> UpgradeObject()
		{
			IDxObject<UpgradeObjT> dxObjTemp;
			m_dxObject->QueryInterface(IID_PPV_ARGS(dxObjTemp.GetDxObjectAddressOf()));
			return dxObjTemp;
		}

		void ReSet()
		{
			m_dxObject.Reset();
		}

	protected:
		DxObjectCom m_dxObject;
	};
}
