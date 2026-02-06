#include "Window.h"

#include "Win32/Win.h"

#include <iostream>

namespace Engine {
	Window::Window(const std::wstring& _title, int _width, int _height)
		: m_title(_title), m_width(_width), m_height(_height) {

		m_hInst = GetModuleHandle(NULL);

		Win32::Result result;

		result = Win32::RegisterWindowClass(
			&m_winCls,
			m_hInst,
			_title.c_str(),
			ProcedureInitializer
		);

		if (!result.Succeeded()) {} // TO DO : Add propper error handling

		Win32::WindowDescriptor desc;
		desc.title = m_title.c_str();
		desc.width = m_width;
		desc.height = m_height;

		result = Win32::CreateWindowFromClass(
			&m_handle,
			&m_winCls,
			m_hInst,
			desc,
			this
		);

		if (!result.Succeeded()) {} // TO DO : Add propper error handling

		// Ignore potential args, just show the window
		ShowWindow(m_handle, SW_SHOW);
		m_msg = {};
		m_opened = true;
	}

	LRESULT Window::WindowProc(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam) {
		switch (_message) {
		case WM_CLOSE:
			m_opened = false;
			break;
		default:
			break;
		}
		return DefWindowProc(_hwnd, _message, _wParam, _lParam);
	}

	const bool Window::ShouldClose() const {
		return !m_opened;
	}

	void Window::PollEvents() {
		GetMessage(&m_msg, NULL, 0, 0);
		TranslateMessage(&m_msg);
		DispatchMessage(&m_msg);
	}

	// TO DO : Cleanup
	LRESULT Window::ProcedureInitializer(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam) {
		Window* window;
		if (_message == WM_NCCREATE) {
			CREATESTRUCT* cs = (CREATESTRUCT*)_lParam;
			window = (Window*)cs->lpCreateParams;
			SetLastError(0);
			if (SetWindowLongPtr(_hwnd, GWL_USERDATA, (LONG_PTR)window) == 0) {
				if (GetLastError() != 0) return FALSE;
			}
		}
		else { window = (Window*)GetWindowLongPtr(_hwnd, GWL_USERDATA); }
		if (window) {
			return window->WindowProc(_hwnd, _message, _wParam, _lParam);
		}
		return DefWindowProc(_hwnd, _message, _wParam, _lParam);
	}
}