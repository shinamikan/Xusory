#include "../Window.h"

namespace XusoryEngine
{
	BOOL Window::IsCreated() const
	{
		return m_winId != nullptr;
	}

	WinId Window::GetWinId() const
	{
		return m_winId;
	}

	Point Window::GetWindowPos() const
	{
		ThrowIfObjectNotCreated(m_winId, "window");

		Rect rect;
		GetWindowRect(m_winId, &rect);

		return { rect.left, rect.top };
	}

	Point Window::GetWindowSize(BOOL isClientSize) const
	{
		ThrowIfObjectNotCreated(m_winId, "window");

		Rect rect;
		if (isClientSize)
		{
			GetClientRect(m_winId, &rect);
		}
		else
		{
			GetWindowRect(m_winId, &rect);
		}

		return { rect.right - rect.left, rect.bottom - rect.top };
	}

	std::wstring Window::GetWindowTitle() const
	{
		ThrowIfObjectNotCreated(m_winId, "window");

		std::wstring title(UINT8_MAX, 0);
		GetWindowText(m_winId, title.data(), UINT8_MAX);

		return title;
	}

	void Window::SetWindowTitle(const std::wstring_view& title) const
	{
		ThrowIfObjectNotCreated(m_winId, "window");
		ThrowIfWinFuncFailed(SetWindowText(m_winId, title.data()), "set window title");
	}

	void Window::Show() const
	{
		ThrowIfObjectNotCreated(m_winId, "window");
		ShowWindow(m_winId, SW_SHOW);
	}

	void Window::Hide() const
	{
		ThrowIfObjectNotCreated(m_winId, "window");
		ShowWindow(m_winId, SW_HIDE);
	}

	void Window::Maximize() const
	{
		ThrowIfObjectNotCreated(m_winId, "window");
		SendMessage(m_winId, WM_SYSCOMMAND, SC_MAXIMIZE, NULL);
	}

	void Window::Minimize() const
	{
		ThrowIfObjectNotCreated(m_winId, "window");
		SendMessage(m_winId, WM_SYSCOMMAND, SC_MINIMIZE, NULL);
	}

	void Window::Restore() const
	{
		ThrowIfObjectNotCreated(m_winId, "window");
		SendMessage(m_winId, WM_SYSCOMMAND, SC_RESTORE, NULL);
	}

	void Window::Active() const
	{
		ThrowIfObjectNotCreated(m_winId, "window");
		SetActiveWindow(m_winId);
	}

	void Window::Move(const Point& pos) const
	{
		ThrowIfObjectNotCreated(m_winId, "window");

		const auto sizeTemp = GetWindowSize();
		ThrowIfWinFuncFailed(MoveWindow(m_winId, pos.x, pos.y, sizeTemp.x, sizeTemp.y, true), "move window");
	}

	void Window::Move(INT posX, INT posY) const
	{
		ThrowIfObjectNotCreated(m_winId, "window");

		const auto sizeTemp = GetWindowSize();
		ThrowIfWinFuncFailed(MoveWindow(m_winId, posX, posY, sizeTemp.x, sizeTemp.y, true), "move window");
	}

	void Window::Resize(const Point& size, BOOL isClientSize) const
	{
		ThrowIfObjectNotCreated(m_winId, "window");
		Resize(size.x, size.y, isClientSize);
	}

	void Window::Resize(INT sizeX, INT sizeY, BOOL isClientSize) const
	{
		ThrowIfObjectNotCreated(m_winId, "window");

		if (isClientSize)
		{
			Rect rect = { 0, 0, sizeX, sizeY };
			AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
			sizeX = rect.right - rect.left;
			sizeY = rect.bottom - rect.top;
		}

		const auto posTemp = GetWindowPos();
		ThrowIfWinFuncFailed(MoveWindow(m_winId, posTemp.x, posTemp.y, sizeX, sizeY, true), "resize window");
	}

	void Window::MessageLoop()
	{
		MSG msg = { };

		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, nullptr, NULL, NULL, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				OnLoop();
			}
		}
	}

	void Window::Create(const std::wstring_view& wndClassName, const std::wstring_view& windowTitle, INT posX, INT posY, INT sizeX, INT sizeY)
	{
		m_winId = CreateWindowEx(WS_EX_CLIENTEDGE, wndClassName.data(), windowTitle.data(), WS_OVERLAPPEDWINDOW,
			posX, posY, sizeX, sizeY, nullptr, nullptr, nullptr, nullptr);
	}

	void Window::Close() const
	{
		ThrowIfObjectNotCreated(m_winId, "window");
		SendMessage(m_winId, WM_CLOSE, NULL, NULL);
	}

	void Window::Destroy() const
	{
		ThrowIfObjectNotCreated(m_winId, "window");
		DestroyWindow(m_winId);
	}

	void Window::OnCreate() { }
	void Window::OnClose() { }
	void Window::OnDestroy() { }
	void Window::OnShow() { }
	void Window::OnHide() { }
	void Window::OnMaximize() { }
	void Window::OnMinimize() { }
	void Window::OnRestore() { }
	void Window::OnFocusIn(const FocusEvent& event) { }
	void Window::OnFocusOut() { }
	void Window::OnMove(const MoveEvent& event) { }
	void Window::OnResize(const ResizeEvent& event) { }
	void Window::OnMouseMove(const MouseMoveEvent& event) { }
	void Window::OnMousePress(const MouseClickEvent& event) { }
	void Window::OnMouseRelease(const MouseClickEvent& event) { }
	void Window::OnMouseDoublePress(const MouseClickEvent& event) { }
	void Window::OnMouseWheel(const MouseWheelEvent& event) { }
	void Window::OnKeyPress(const KeyEvent& event) { }
	void Window::OnKeyRelease(const KeyEvent& event) { }
	void Window::OnLoop() { }
}
