#pragma once

#include <type_traits>
#include <unordered_map>

#include "Common/WindowDefine.h"
#include "Window.h"

#pragma warning(disable : 4251)

namespace XusoryEngine
{
	using WindowClass = WNDCLASS;
	using WindowClassEx = WNDCLASSEX;

	DLL_STATIC_CLASS(WindowFactory)
	{
		friend LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		friend void ThrowIfSMWindowClassNull();

	public:
		static void Del();
		static void StartNewWindowClass();
		static void SetWindowCursor(INT sysCursor);
		static void SetWindowCursor(const std::wstring_view& imagePath);
		static void SetWindowIcon(INT sysIcon);
		static void SetWindowIcon(const std::wstring_view& imagePath);
		static void RegisterWindowClass(HINSTANCE hInstance, const std::wstring_view & className);

		template <typename WindowT>
		static Window* CreateWindowInstance(const std::wstring_view& className, const std::wstring_view& windowTitle, INT sizeX = DEFAULT_WIN_SIZE, INT sizeY = DEFAULT_WIN_SIZE,
			BOOL isClientSize = false, INT posX = DEFAULT_WIN_POS, INT posY = DEFAULT_WIN_POS);
		static void CloseWindowInstance(Window*& window);
		static void DestroyWindowInstance(Window*& window);

	private:
		static void DeleteWindowInstance(Window*& window);

		static WindowClassEx* sm_windowClass;
		static std::unordered_map<HWND, Window*> sm_winInstanceMap;
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
