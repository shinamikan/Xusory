#include "../StringEx.h"

namespace XusoryEngine
{
    INT StringEx::GetStringWideSize(const std::string_view& str)
    {
        return MultiByteToWideChar(CP_ACP, 0, str.data(), -1, nullptr, NULL);
    }

    INT StringEx::GetWStringByteSize(const std::wstring_view& str)
    {
        return WideCharToMultiByte(CP_ACP, 0, str.data(), -1, nullptr, 0,
            nullptr, nullptr);
    }

    std::wstring StringEx::StringToWString(const std::string_view& str)
    {
        const INT wideSize = GetStringWideSize(str) - 1;

        if (wideSize <= 0)
        {
            return { TEXT("") };
        }

        std::wstring wStrTemp(wideSize, 0);
        MultiByteToWideChar(CP_ACP, 0, str.data(), -1, wStrTemp.data(), wideSize);

        return wStrTemp;
    }

    std::string StringEx::WStringToString(const std::wstring_view& str)
    {
        const INT byteSize = GetWStringByteSize(str) - 1;

        if (byteSize <= 0)
        {
            return { "" };
        }

        std::string strTemp(byteSize, 0);
        WideCharToMultiByte(CP_ACP, 0, str.data(), -1, strTemp.data(), byteSize,
            nullptr, nullptr);

        return strTemp;
    }
}
