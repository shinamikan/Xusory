#include "../Window.h"

namespace XusoryEngine::Platform
{
	void ThrowIfWinIdIsNull(const WinID& winId)
	{
		ThrowWithErrName(NullHandleError, "Window has not been created yet");
	}

	WinID Window::GetWinId() const
	{
		return m_winId;
	}

	Point Window::GetWindowPos() const
	{
		ThrowIfWinIdIsNull(m_winId);

		Rect rect;
		GetWindowRect(m_winId, &rect);

		return { rect.left, rect.top };
	}

	Point Window::GetWindowSize(BOOL isClientSize) const
	{
		ThrowIfWinIdIsNull(m_winId);

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
		ThrowIfWinIdIsNull(m_winId);

		std::wstring title(UINT8_MAX, 0);
		GetWindowText(m_winId, title.data(), UINT8_MAX);

		return title;
	}

	void Window::SetWindowTitle(const std::wstring_view& title) const
	{
		ThrowIfWinIdIsNull(m_winId);

		if (!SetWindowText(m_winId, title.data()))
		{
			ThrowWithErrName(RuntimeError, WinFailedInfo("set window title"));
		}
	}

	void Window::Show() const
	{
		ThrowIfWinIdIsNull(m_winId);
		ShowWindow(m_winId, SW_SHOW);
	}

	void Window::Hide() const
	{
		ThrowIfWinIdIsNull(m_winId);
		ShowWindow(m_winId, SW_HIDE);
	}

	void Window::Maximize() const
	{
		ThrowIfWinIdIsNull(m_winId);
		SendMessage(m_winId, WM_SYSCOMMAND, SC_MAXIMIZE, NULL);
	}

	void Window::Minimize() const
	{
		ThrowIfWinIdIsNull(m_winId);
		SendMessage(m_winId, WM_SYSCOMMAND, SC_MINIMIZE, NULL);
	}

	void Window::Restore() const
	{
		ThrowIfWinIdIsNull(m_winId);
		SendMessage(m_winId, WM_SYSCOMMAND, SC_RESTORE, NULL);
	}

	void Window::Active() const
	{
		SetActiveWindow(m_winId);
	}

	void Window::Move(const Point& pos) const
	{
		ThrowIfWinIdIsNull(m_winId);

		const auto sizeTemp = GetWindowSize();
		if (!MoveWindow(m_winId, pos.x, pos.y, sizeTemp.x, sizeTemp.y, true))
		{
			ThrowWithErrName(RuntimeError, WinFailedInfo("move window"));
		}
	}

	void Window::Move(INT posX, INT posY) const
	{
		ThrowIfWinIdIsNull(m_winId);

		const auto sizeTemp = GetWindowSize();
		if (!MoveWindow(m_winId, posX, posY, sizeTemp.x, sizeTemp.y, true))
		{
			ThrowWithErrName(RuntimeError, WinFailedInfo("move window"));
		}
	}

	void Window::Resize(const Point& size, BOOL isClientSize) const
	{
		ThrowIfWinIdIsNull(m_winId);
		Resize(size.x, size.y, isClientSize);
	}

	void Window::Resize(INT sizeX, INT sizeY, BOOL isClientSize) const
	{
		ThrowIfWinIdIsNull(m_winId);

		if (isClientSize)
		{
			Rect rect = { 0, 0, sizeX, sizeY };
			AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
			sizeX = rect.right - rect.left;
			sizeY = rect.bottom - rect.top;
		}

		const auto posTemp = GetWindowPos();
		if (!MoveWindow(m_winId, posTemp.x, posTemp.y, sizeX, sizeY, true))
		{
			ThrowWithErrName(RuntimeError, WinFailedInfo("resize window"));
		}
	}

	void Window::Create(const std::wstring_view& wndClassName, const std::wstring_view& windowTitle, INT posX, INT posY, INT sizeX, INT sizeY)
	{
		m_winId = CreateWindowEx(WS_EX_CLIENTEDGE, wndClassName.data(), windowTitle.data(), WS_OVERLAPPEDWINDOW,
			posX, posY, sizeX, sizeY, nullptr, nullptr, nullptr, nullptr);
	}

	void Window::Close() const
	{
		ThrowIfWinIdIsNull(m_winId);
		SendMessage(m_winId, WM_CLOSE, NULL, NULL);
	}

	void Window::Destroy() const
	{
		ThrowIfWinIdIsNull(m_winId);
		DestroyWindow(m_winId);
	}
}
