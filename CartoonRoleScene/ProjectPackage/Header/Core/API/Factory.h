#pragma once

#include <unordered_map>	
#include "../../Platform/Platform.h"

namespace XusoryEngine
{
	template <typename FactoryInterface>
	class FactoryBase
	{
		typedef FactoryInterface* (*FactoryCreateFunc)();

	public:
		FactoryBase() = delete;

		static void RegisterFactory(const std::string_view& name, FactoryCreateFunc func)
		{
			GetStrFactoryMap().emplace(name, func);
		}

		static void RegisterFactory(const std::wstring_view& name, FactoryCreateFunc func)
		{
			GetWStrFactoryMap().emplace(name, func);
		}

		static auto GetFactory(const std::string_view& name)
		{
			CaptureNoReturnFunc(return GetStrFactoryMap().at(name.data())());
		}

		static auto GetFactory(const std::wstring_view& name)
		{
			CaptureNoReturnFunc(return GetWStrFactoryMap().at(name.data())());
		}

	private:
		static std::unordered_map<std::string, FactoryCreateFunc>& GetStrFactoryMap()
		{
			static std::unordered_map<std::string, FactoryCreateFunc> strFactoryStrMap;
			return strFactoryStrMap;
		}

		static std::unordered_map<std::wstring, FactoryCreateFunc>& GetWStrFactoryMap()
		{
			static std::unordered_map<std::wstring, FactoryCreateFunc> wStrFactoryStrMap;
			return wStrFactoryStrMap;
		}
	};
}

#define CREATE_FACTORY(factoryInterface, factoryType)	\
	static factoryInterface* Create()					\
	{													\
		return new factoryType;							\
	}													\
private:												\
	static BOOL sm_registered;


#define REGISTER_FACTORY(factoryBaseType, factoryType, format)	\
BOOL factoryType::sm_registered = []							\
{																\
    factoryBaseType::RegisterFactory(format, Create);			\
    return true;												\
}()
