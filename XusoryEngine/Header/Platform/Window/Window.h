#pragma once

#include "WindowCom.h"
#include "WindowEvent.h"

namespace XusoryEngine::Platform
{
	DLL_CLASS(Window)
	{
		friend class WindowFactory;

	public:
		Window() = default;
		DEFAULT_COPY_OPERATOR(Window);
		MOVE_OPERATOR(Window);
		virtual ~Window() = default;

		WinID GetWinId() const;
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

		virtual void OnCreate() = 0;
		virtual void OnClose() = 0;
		virtual void OnDestroy() = 0;

		virtual void OnShow() = 0;
		virtual void OnHide() = 0;
		
		virtual void OnMaximize() = 0;
		virtual void OnMinimize() = 0;
		virtual void OnRestore() = 0;

		virtual void OnFocusIn(const FocusEvent& event) = 0;
		virtual void OnFocusOut() = 0;

		virtual void OnMove(const MoveEvent& event) = 0;
		virtual void OnResize(const ResizeEvent& event) = 0;

		virtual void OnMouseMove(const MouseMoveEvent& event) = 0;
		virtual void OnMousePress(const MouseClickEvent& event) = 0;
		virtual void OnMouseRelease(const MouseClickEvent& event) = 0;
		virtual void OnMouseDoublePress(const MouseClickEvent & event) = 0;
		virtual void OnMouseWheel(const MouseWheelEvent& event) = 0;

		virtual void OnKeyPress(const KeyEvent& event) = 0;
		virtual void OnKeyRelease(const KeyEvent& event) = 0;

	private:
		void Create(const std::wstring_view& wndClassName, const std::wstring_view& windowTitle, INT posX, INT posY, INT sizeX, INT sizeY);
		void Close() const;
		void Destroy() const;

		WinID m_winId = nullptr;
	};
}
