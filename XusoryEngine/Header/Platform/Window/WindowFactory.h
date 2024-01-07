#pragma once

#include <type_traits>
#include <unordered_map>

#include "Window.h"
#include "WindowCom.h"
#include "WindowEvent.h"

namespace XusoryEngine::Platform
{
	DLL_STATIC_CLASS(WindowFactory)
	{
		friend LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		friend void ThrowIfSMWindowClassNull();

	public:
		static void Del();
		static void RegisterWindowClass(HINSTANCE hInstance, const std::wstring_view& className);
		static void SetWindowCursor(INT sysCursor);
		static void SetWindowCursor(const std::wstring_view& imagePath);
		static void SetWindowIcon(INT sysIcon);
		static void SetWindowIcon(const std::wstring_view& imagePath);
		static void StartNewWindowClass();

		template <typename WindowT>
		static WindowT* CreateWindowInstance(const std::wstring_view& className, const std::wstring_view& windowTitle, INT posX = DEFAULT_WIN_POS, INT posY = DEFAULT_WIN_POS,
			INT sizeX = DEFAULT_WIN_SIZE, INT sizeY = DEFAULT_WIN_SIZE, BOOL isClientSize = false);
		static void CloseWindowInstance(Window*& window);
		static void DestroyWindowInstance(Window*& window);

	private:
		static void DeleteWindowInstance(Window*& window);

		static WindowClassEx* sm_windowClass;
		static std::unordered_map<HWND, Window*> sm_winInstanceMap;
	};

	template<typename WindowT>
	WindowT* WindowFactory::CreateWindowInstance(const std::wstring_view& className, const std::wstring_view& windowTitle, INT posX, INT posY,
		INT sizeX, INT sizeY, BOOL isClientSize)
	{
		static_assert(std::is_base_of_v<WindowT, Window>);

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

		return window;
	}
}
