#pragma once

#include <unordered_map>	
#include "../../Platform/Platform.h"

namespace XusoryEngine
{
	template <typename IFactoryType>
	class FactoryBase
	{
		typedef IFactoryType* (*FactoryCreateFunc)();

	public:
		FactoryBase() = delete;

		static void RegisterFactory(const std::string_view& name, FactoryCreateFunc func)
		{
			sm_factoryMap.emplace(name, func);
		}

		static IFactoryType* GetFactory(const std::string_view& name)
		{
			return sm_factoryMap.at(name.data());
		}

	private:
		static auto& GetFactoryMap()
		{
			return sm_factoryMap;
		}

		static std::unordered_map<std::string, FactoryCreateFunc> sm_factoryMap;
	};
}

#define CREATE_LOADER(IFactoryType, FactoryType)	\
public:												\
	static IFactoryType* Create()					\
	{												\
		return new FactoryType();					\
	}												\
private:											\
	static bool registered;

#define REGISTER_LOADER(Ty_Factory, Ty_Loader, format)	\
bool Ty_Loader::registered = []							\
{														\
    Ty_Factory::RegisterLoader(format, Create);			\
    return true;										\
}()
