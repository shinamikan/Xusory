#pragma once

#include <type_traits>
#include <unordered_map>

#include "../Common/PlatformDefine.h"

#include "Common/WindowDefine.h"
#include "Window.h"

#pragma warning(disable : 4251)

namespace XusoryEngine
{
	using WindowClass = WNDCLASS;
	using WindowClassEx = WNDCLASSEX;

	enum MessageBoxStyle
	{
		MSG_BOX_OK = MB_OK,
		MSG_BOX_OK_CANCEL = MB_OKCANCEL,
		MSG_BOX_YES_NO = MB_YESNO,
		MSG_BOX_YES_NO_CANCEL = MB_YESNOCANCEL,
		MSG_BOX_RETRY_CANCEL = MB_RETRYCANCEL,
		MSG_BOX_ABORT_RETRY_IGNORE = MB_ABORTRETRYIGNORE,
		MSG_BOX_CANCEL_TRY_CONTINUE = MB_CANCELTRYCONTINUE,
	};

	enum MessageBoxIcon
	{
		MSG_ICON_STOP = MB_ICONSTOP,
		MSG_ICON_WARNING = MB_ICONWARNING,
		MSG_ICON_QUESTION = MB_ICONQUESTION,
		MSG_ICON_INFORMATION = MB_ICONINFORMATION
	};

	enum MessageBoxCode
	{
		MSG_CODE_NO = IDNO,
		MSG_CODE_OK = IDOK,
		MSG_CODE_YES = IDYES,
		MSG_CODE_ABORT = IDABORT,
		MSG_CODE_RETRY = IDRETRY,
		MSG_CODE_CANCEL = IDCANCEL,
		MSG_CODE_IGNORE = IDIGNORE,
		MSG_CODE_CONTINUE = IDCONTINUE,
		MSG_CODE_TRY_AGAIN = IDTRYAGAIN,
	};

	DLL_STATIC_CLASS(WindowFactory)
	{
		friend LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		friend void ThrowIfSMWindowClassNull();

	public:
		static void StartNewWindowClass();
		static void SetWindowCursor(INT sysCursor);
		static void SetWindowCursor(const std::wstring_view& imagePath);
		static void SetWindowIcon(INT sysIcon);
		static void SetWindowIcon(const std::wstring_view& imagePath);
		static void RegisterWindowClass(HINSTANCE hInstance, const std::wstring_view& className);

		template <typename WindowT>
		static Window* CreateWindowInstance(const std::wstring_view& className, const std::wstring_view& windowTitle,
			INT sizeX = DEFAULT_WIN_SIZE, INT sizeY = DEFAULT_WIN_SIZE, BOOL isClientSize = false, INT posX = DEFAULT_WIN_POS, INT posY = DEFAULT_WIN_POS);
		static void CloseWindowInstance(Window*& window);
		static void CloseAllWindowInstance();
		static void DestroyWindowInstance(Window*& window);
		static void DestroyAllWindowInstance();

		static MessageBoxCode MessageWindow(WinId winId, const std::wstring_view& caption, const std::wstring_view& text,
			MessageBoxStyle style = MSG_BOX_OK_CANCEL, MessageBoxIcon icon = MSG_ICON_INFORMATION);

	private:
		static void DeleteWindowInstance(Window*& window);

		static WindowClassEx* sm_windowClass;
		static std::unordered_map<WinId, Window*> sm_winInstanceMap;
	};

	template<typename WindowT>
	Window* WindowFactory::CreateWindowInstance(const std::wstring_view& className, const std::wstring_view& windowTitle, INT sizeX, INT sizeY,
		BOOL isClientSize, INT posX, INT posY)
	{
		static_assert(std::is_base_of_v<Window, WindowT>);

		if (isClientSize)
		{
			Rect rect = { 0, 0, sizeX, sizeY };
			AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
			sizeX = rect.right - rect.left;
			sizeY = rect.bottom - rect.top;
		}

		WindowT* window = new WindowT();
		window->Create(className, windowTitle, posX, posY, sizeX, sizeY);
		sm_winInstanceMap.insert(std::make_pair(window->m_winId, window));
		SendMessage(window->m_winId, WM_CREATE, NULL, NULL);

		return window;
	}
}
