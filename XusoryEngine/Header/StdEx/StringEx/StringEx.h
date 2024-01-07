#pragma once

#include <cstdio>
#include <iostream>
#include <vector>
#include <Windows.h>

#include "../../CppEx/CppEx.h"

STATIC_CLASS(StringEx)
{
public:
	static INT GetStringWideSize(const std::string_view& str);
	static INT GetWStringByteSize(const std::wstring_view& wStr);

	static std::wstring StringToWString(const std::string_view& strSrc);
	static std::string	WStringToString(const std::wstring_view& wStrSrc);

	template <typename StringT>
	static BOOL BeginWith(const std::basic_string_view<typename StringT::value_type>&dstStr, typename StringT::value_type dstChar);

	template <typename StringT>
	static BOOL EndWith(const std::basic_string_view<typename StringT::value_type>& dstStr, typename StringT::value_type dstChar);

	template <typename StringT, typename... Args>
	static StringT Format(const std::basic_string_view<typename StringT::value_type>& formatStr, Args... args);

	template <typename StringT>
	static std::vector<StringT> Split(const std::basic_string_view<typename StringT::value_type>& strDst,
		const std::basic_string_view<typename StringT::value_type>& separator);
};

template<typename StringT>
BOOL StringEx::BeginWith(const std::basic_string_view<typename StringT::value_type>& dstStr, typename StringT::value_type dstChar)
{
	if (*dstStr.begin() == dstChar)
	{
		return true;
	}
	return false;
}

template<typename StringT>
BOOL StringEx::EndWith(const std::basic_string_view<typename StringT::value_type>& dstStr, typename StringT::value_type dstChar)
{
	if (*(dstStr.end() - 1) == dstChar)
	{
		return true;
	}
	return false;
}

template<typename StringT, typename ...Args>
StringT StringEx::Format(const std::basic_string_view<typename StringT::value_type>& formatStr, Args... args)
{
	if constexpr (std::is_same_v<StringT, std::string>)
	{
		CaptureNoReturnFunc(const int size = std::snprintf(nullptr, 0, formatStr.data(), args...));
		StringT buf(size, 0);
		std::snprintf(buf.data(), size + 1, formatStr.data(), args...);
		return buf;
	}
	else
	{
		CaptureNoReturnFunc(const int size = std::swprintf(nullptr, 0, formatStr.data(), args...));
		StringT buf(size, 0);
		std::swprintf(buf.data(), size + 1, formatStr.data(), args...);
		return buf;
	}
}

template<typename StringT>
std::vector<StringT> StringEx::Split(const std::basic_string_view<typename StringT::value_type>& strDst,
	const std::basic_string_view<typename StringT::value_type>& separator)
{
	static_assert(std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>);
	using StrSizeT = typename StringT::size_type;

	const auto size = strDst.size();

	std::vector<StringT> splitResult;
	StrSizeT pos = 0;

	for (StrSizeT i = 0; i < size; )
	{
		pos = strDst.find(separator, i);
		if (pos == UINT64_MAX)
		{
			pos = i;
			break;
		}

		if (pos < size)
		{
			auto str = StringT(strDst.substr(i, pos - i));
			splitResult.emplace_back(str);
			i = pos + separator.size();
		}
	}

	auto endStr = StringT(strDst.substr(pos, strDst.size() - pos));
	splitResult.emplace_back(endStr);

	return splitResult;
}
