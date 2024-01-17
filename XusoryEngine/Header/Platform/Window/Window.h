#pragma once

#include "../Common/PlatformDefine.h"

#include "Common/WindowDefine.h"
#include "Common/WindowEvent.h"

namespace XusoryEngine
{
	using WinId = HWND;

	DLL_CLASS(Window)
	{
		friend class WindowFactory;

	public:
		Window() = default;
		DEFAULT_COPY_OPERATOR(Window);
		MOVE_OPERATOR(Window);
		virtual ~Window() = default;

		BOOL IsCreated() const;
		WinId GetWinId() const;
		Point GetWindowPos() const;
		Point GetWindowSize(BOOL isClientSize = false) const;
		std::wstring GetWindowTitle() const;

		void SetWindowTitle(const std::wstring_view& title) const;

		void Show() const;
		void Hide() const;
		
		void Maximize() const;
		void Minimize() const;
		void Restore() const;

		void Active() const;

		void Move(const Point& pos) const;
		void Move(INT posX, INT	posY) const;

		void Resize(const Point& size, BOOL isClientSize = false) const;
		void Resize(INT sizeX, INT sizeY, BOOL isClientSize = false) const;

		void MessageLoop();

		virtual void OnCreate();
		virtual void OnClose();
		virtual void OnDestroy();

		virtual void OnShow();
		virtual void OnHide();
		
		virtual void OnMaximize();
		virtual void OnMinimize();
		virtual void OnRestore();

		virtual void OnFocusIn(const FocusEvent& event);
		virtual void OnFocusOut();

		virtual void OnMove(const MoveEvent& event);
		virtual void OnResize(const ResizeEvent& event);

		virtual void OnMouseMove(const MouseMoveEvent& event);
		virtual void OnMouseDoublePress(const MouseClickEvent& event);
		virtual void OnMousePress(const MouseClickEvent& event);
		virtual void OnMouseRelease(const MouseClickEvent& event);
		virtual void OnMouseWheel(const MouseWheelEvent& event);

		virtual void OnKeyPress(const KeyEvent& event);
		virtual void OnKeyRelease(const KeyEvent& event);

		virtual void OnLoop();

	private:
		void Create(const std::wstring_view& wndClassName, const std::wstring_view& windowTitle, INT posX, INT posY, INT sizeX, INT sizeY);
		void Close() const;
		void Destroy() const;

		WinId m_winId = nullptr;
	};
}
