#pragma once

#include <cstdio>
#include <iostream>
#include <vector>
#include <Windows.h>

#include "../../CppEx/CppEx.h"

#ifdef min
#undef min
#endif

namespace XusoryEngine
{
	DLL_STATIC_CLASS(StringEx)
	{
	public:
		static INT GetStringWideSize(const std::string_view& str);
		static INT GetWStringByteSize(const std::wstring_view& str);

		static std::wstring StringToWString(const std::string_view& str);
		static std::string	WStringToString(const std::wstring_view& str);

		template <typename StringT>
		static BOOL BeginWith(const std::basic_string_view<typename StringT::value_type>& str, typename StringT::value_type beginChar);
		template <typename StringT>
		static BOOL BeginWith(const std::basic_string_view<typename StringT::value_type>& str, const std::basic_string_view<typename StringT::value_type>& beginStr);

		template <typename StringT>
		static BOOL EndWith(const std::basic_string_view<typename StringT::value_type>& str, typename StringT::value_type endChar);
		template <typename StringT>
		static BOOL EndWith(const std::basic_string_view<typename StringT::value_type>& str, const std::basic_string_view<typename StringT::value_type>& endStr);

		template <typename StringT, typename... Args>
		static StringT Format(const std::basic_string_view<typename StringT::value_type>& formatStr, Args... args);

		template <typename StringT>
		static std::vector<StringT> Split(const std::basic_string_view<typename StringT::value_type>& str,
			const std::basic_string_view<typename StringT::value_type>& separator);
	};

	template<typename StringT>
	BOOL StringEx::BeginWith(const std::basic_string_view<typename StringT::value_type>& str, typename StringT::value_type beginChar)
	{
		static_assert(std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>);

		if (*str.begin() != beginChar)
		{
			return false;
		}
		return true;
	}

	template<typename StringT>
	BOOL StringEx::BeginWith(const std::basic_string_view<typename StringT::value_type>& str, const std::basic_string_view<typename StringT::value_type>& beginStr)
	{
		static_assert(std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>);

		for (UINT i = 0; i < std::min(str.size(), beginStr.size()) ; i++)
		{
			if (str.at(i) != beginStr.at(i))
			{
				return false;
			}
		}
		return true;
	}

	template<typename StringT>
	BOOL StringEx::EndWith(const std::basic_string_view<typename StringT::value_type>& str, typename StringT::value_type endChar)
	{
		static_assert(std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>);

		if (*(str.end() - 1) != endChar)
		{
			return false;
		}
		return true;
	}

	template<typename StringT>
	BOOL StringEx::EndWith(const std::basic_string_view<typename StringT::value_type>& str, const std::basic_string_view<typename StringT::value_type>& endStr)
	{
		for (UINT i = std::min(str.size(), endStr.size()) - 1; i > -1; --i)
		{
			if (str.at(i) != endStr.at(i))
			{
				return false;
			}
		}
		return true;
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
	std::vector<StringT> StringEx::Split(const std::basic_string_view<typename StringT::value_type>& str,
		const std::basic_string_view<typename StringT::value_type>& separator)
	{
		static_assert(std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>);
		using StrSizeT = typename StringT::size_type;

		const auto size = str.size();

		std::vector<StringT> splitResult;
		StrSizeT pos = 0;

		for (StrSizeT i = 0; i < size; )
		{
			pos = str.find(separator, i);
			if (pos == UINT64_MAX)
			{
				pos = i;
				break;
			}

			if (pos < size)
			{
				auto subStr = StringT(str.substr(i, pos - i));
				splitResult.emplace_back(subStr);
				i = pos + separator.size();
			}
		}

		auto endStr = StringT(str.substr(pos, str.size() - pos));
		splitResult.emplace_back(endStr);

		return splitResult;
	}
}
