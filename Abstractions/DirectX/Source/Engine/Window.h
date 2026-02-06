#pragma once

#include "Win32/Win32.h"

#include <string>

namespace Engine {
	class Window {
	public:
		Window(const std::wstring& _title, int _width, int _height);

		const bool ShouldClose() const;

		void PollEvents();

	protected:
		const std::wstring& m_title;
		int m_width; int m_height;
		bool m_opened;

	private:
		LRESULT WindowProc(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
		static LRESULT CALLBACK ProcedureInitializer(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

		MSG m_msg;
		HWND m_handle;
		HMODULE m_hInst;
		WNDCLASS m_winCls;
	};
}