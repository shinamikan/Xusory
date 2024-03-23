#include <windowsx.h>

#include "../WindowFactory.h"
#include "../Common/WindowEvent.h"
#include "../../File/File.h"

namespace XusoryEngine
{
	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		Window* window;

		const auto it = WindowFactory::sm_winInstanceMap.find(hWnd);
		if (it != WindowFactory::sm_winInstanceMap.end())
		{
			window = it->second;
		}
		else
		{
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}

		switch (msg)
		{
		case WM_CREATE:
			window->OnCreate();
			break;

		case WM_CLOSE:
			window->OnClose();
			break;

		case WM_DESTROY:
			window->OnDestroy();
			break;

		case WM_SHOWWINDOW:
			if (wParam == TRUE)
			{
				window->OnShow();
			}
			else
			{
				window->OnHide();
			}

			break;

		case WM_SYSCOMMAND:
			switch (wParam)
			{
			case SC_MAXIMIZE:
				window->OnMaximize();
				break;

			case SC_MINIMIZE:
				window->OnMinimize();
				break;

			case SC_RESTORE:
				window->OnRestore();
				break;

			default:
				break;
			}

			break;

		case WM_ACTIVATE:
		{
			switch (auto active = GET_X_LPARAM(wParam))
			{
			case WA_ACTIVE:
			case WA_CLICKACTIVE:
				FocusEvent event;
				event.focusReason = static_cast<FocusReason>(active);
				window->OnFocusIn(event);
				break;

			case WA_INACTIVE:
				window->OnFocusOut();
				break;

			default:
				break;
			}
		}

		case WM_MOVE:
		{
			MoveEvent event;
			event.movePosX = GET_X_LPARAM(lParam);
			event.movePosY = GET_Y_LPARAM(lParam);
			window->OnMove(event);
			break;
		}

		case WM_SIZE:
		{
			ResizeEvent event;
			event.sizeX = GET_X_LPARAM(lParam);
			event.sizeY = GET_Y_LPARAM(lParam);
			window->OnResize(event);
			break;
		}

		case WM_MOUSEMOVE:
		{
			MouseMoveEvent event;
			event.mouseClickKeyCode = static_cast<MouseKeyCode>(wParam);
			event.mouseMovePosX = GET_X_LPARAM(lParam);
			event.mouseMovePosY = GET_Y_LPARAM(lParam);
			window->OnMouseMove(event);
			break;
		}

		case WM_LBUTTONDBLCLK:
		case WM_RBUTTONDBLCLK:
		case WM_MBUTTONDBLCLK:
		case WM_XBUTTONDBLCLK:
		{
			MouseClickEvent event;
			event.mouseKeyCode = static_cast<MouseKeyCode>(wParam);
			event.clickPosX = GET_X_LPARAM(lParam);
			event.clickPosY = GET_Y_LPARAM(lParam);
			window->OnMouseDoublePress(event);
			break;
		}

		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_XBUTTONDOWN:
		{
			MouseClickEvent event;
			event.mouseKeyCode = static_cast<MouseKeyCode>(wParam);
			event.clickPosX = GET_X_LPARAM(lParam);
			event.clickPosY = GET_Y_LPARAM(lParam);
			window->OnMousePress(event);
			break;
		}

		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
		case WM_XBUTTONUP:
		{
			MouseClickEvent event;
			event.mouseKeyCode = static_cast<MouseKeyCode>(wParam);
			event.clickPosX = GET_X_LPARAM(lParam);
			event.clickPosY = GET_Y_LPARAM(lParam);
			window->OnMouseRelease(event);
			break;
		}

		case WM_MOUSEWHEEL:
		{
			MouseWheelEvent event;
			event.mouseWheelDis = GET_Y_LPARAM(wParam);
			window->OnMouseWheel(event);
			break;
		}

		case WM_KEYDOWN:
		{
			KeyEvent event;
			event.keyCode = static_cast<KeyCode>(wParam);
			if ((lParam & 0x40000000) == 0)
			{
				event.isRepeating = false;
			}
			else
			{
				event.isRepeating = true;
			}

			window->OnKeyPress(event);
			break;
		}

		case WM_KEYUP:
		{
			KeyEvent event;
			event.keyCode = static_cast<KeyCode>(wParam);
			window->OnKeyRelease(event);
			break;
		}
		default:
			break;
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	WindowClassEx* WindowFactory::sm_windowClass = nullptr;
	std::unordered_map<WinId, Window*> WindowFactory::sm_winInstanceMap = std::unordered_map<WinId, Window*>();

	void WindowFactory::StartNewWindowClass()
	{
		sm_windowClass = new WindowClassEx();
	}

	void WindowFactory::SetWindowCursor(SysCursor sysCursor)
	{
		ThrowIfWindowClassNull();
		sm_windowClass->hCursor = LoadCursor(nullptr, MAKEINTRESOURCE(sysCursor));
	}

	void WindowFactory::SetWindowCursor(const std::wstring_view& imagePath)
	{
		ThrowIfWindowClassNull();

		File::TryToFindFile(imagePath);
		sm_windowClass->hCursor = static_cast<HCURSOR>(LoadImage(nullptr, imagePath.data(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE));
	}

	void WindowFactory::SetWindowIcon(SysIcon sysIcon)
	{
		ThrowIfWindowClassNull();
		sm_windowClass->hIcon = LoadIcon(nullptr, MAKEINTRESOURCE(sysIcon));
	}

	void WindowFactory::SetWindowIcon(const std::wstring_view& imagePath)
	{
		ThrowIfWindowClassNull();

		File::TryToFindFile(imagePath);
		sm_windowClass->hIcon = static_cast<HICON>(LoadImage(nullptr, imagePath.data(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE));
	}

	void WindowFactory::RegisterWindowClass(HINSTANCE hInstance, const std::wstring_view& className, BOOL allowDoubleClick)
	{
		ThrowIfWindowClassNull();

		sm_windowClass->cbSize = sizeof(WNDCLASSEX);
		sm_windowClass->hbrBackground = static_cast<HBRUSH>(GetStockObject(COLOR_WINDOW + 1));
		sm_windowClass->hInstance = hInstance;
		sm_windowClass->lpfnWndProc = WndProc;
		sm_windowClass->lpszClassName = className.data();
		sm_windowClass->style = allowDoubleClick ? CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS : CS_HREDRAW | CS_VREDRAW;

		if (!RegisterClassEx(sm_windowClass))
		{
			ThrowWithErrName(RuntimeError, WinFailedInfo("register window"));
		}

		delete sm_windowClass;
		sm_windowClass = nullptr;
	}

	void WindowFactory::CloseWindowInstance(Window*& window)
	{
		window->Close();
		DeleteWindowInstance(window);
	}

	void WindowFactory::CloseAllWindowInstance()
	{
		for (auto& [winId, windowInstance] : sm_winInstanceMap)
		{
			CloseWindowInstance(windowInstance);
		}
	}

	void WindowFactory::DestroyWindowInstance(Window*& window)
	{
		window->Destroy();
		DeleteWindowInstance(window);
	}

	void WindowFactory::DestroyAllWindowInstance()
	{
		for (auto& [winId, windowInstance] : sm_winInstanceMap)
		{
			DestroyWindowInstance(windowInstance);
		}
	}

	MessageBoxCode WindowFactory::MessageWindow(WinId winId, const std::wstring_view& caption, const std::wstring_view& text, MessageBoxStyle style, MessageBoxIcon icon)
	{
		return static_cast<MessageBoxCode>(MessageBox(winId, text.data(), caption.data(), static_cast<INT>(style) | static_cast<INT>(icon) | MB_DEFBUTTON1));
	}

	void WindowFactory::DeleteWindowInstance(Window*& window)
	{
		delete window;
		window = nullptr;
	}

	void WindowFactory::ThrowIfWindowClassNull()
	{
		if (sm_windowClass == nullptr)
		{
			ThrowWithErrName(LogicError, "Not yet started creating a new window class");
		}
	}
}
