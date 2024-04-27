#pragma once

#include <iostream>
#include <Windows.h>

#if defined(_MSC_VER)
#define PRETTY_FUNCTION __FUNCSIG__
#endif

template<typename EnumT, EnumT ValueT>
constexpr std::string_view GetEnumValueName()
{
	std::string_view name(PRETTY_FUNCTION);
	const std::string_view enumTName(typeid(EnumT).name());

	std::string_view::size_type strIndex = name.find(enumTName,0) + enumTName.size() + 1;

	std::string_view::size_type indexTemp = 0;
	while ((indexTemp = name.find("::", strIndex)) != UINT64_MAX)
	{
		strIndex = indexTemp;
		strIndex += 2;
	}
	indexTemp = name.find('>', strIndex);

	name = name.substr(strIndex, indexTemp - strIndex);

	if (name.find(')') == UINT64_MAX)
	{
		return name;
	}

	return { };
}

template<typename EnumT, EnumT ValueT>
constexpr BOOL IsEnumValueValid()
{
	return GetEnumValueName<EnumT, ValueT>().size() != 0;
}

//TODO:注册枚举，可以通过字符串获取
