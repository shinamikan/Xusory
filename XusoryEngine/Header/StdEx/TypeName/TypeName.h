#pragma once

#include <vector>
#include "../../CppEx/CppEx.h"
#include "../StringEx/StringEx.h"

namespace XusoryEngine
{
	template <typename T>
	std::string GetTypeName()
	{
		if (const auto typeNameList = StringEx::Split<std::string>(GetTypeId<T>(), " "); typeNameList.size() == 1)
		{
			return typeNameList.at(0);
		}
		else
		{
			return *(StringEx::Split<std::string>(typeNameList.at(1), "::").end() - 1);
		}
	}
}
