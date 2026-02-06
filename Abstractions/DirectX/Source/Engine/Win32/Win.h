#pragma once

#include "Win32.h"
#include "Error.h"

#include "../Common/Types.h"

namespace Engine::Win32 {
	constexpr wcstr DEFAULT_WIN_TITLE	= L"Window";
	constexpr int DEFAULT_WIN_POS_X		= CW_USEDEFAULT;
	constexpr int DEFAULT_WIN_POS_Y		= CW_USEDEFAULT;
	constexpr int DEFAULT_WIN_WIDTH		= CW_USEDEFAULT;
	constexpr int DEFAULT_WIN_HEIGHT	= CW_USEDEFAULT;

	constexpr WNDPROC DEFAULT_WIN_PROC	= DefWindowProc;

	struct WindowDescriptor {
		wcstr title		= DEFAULT_WIN_TITLE;
		int x			= DEFAULT_WIN_POS_X;
		int y			= DEFAULT_WIN_POS_Y;
		int width		= DEFAULT_WIN_WIDTH;
		int height		= DEFAULT_WIN_HEIGHT;
	};

	Result RegisterWindowClass(
		WNDCLASS* _class,
		HMODULE _inst,
		wcstr _name,
		WNDPROC _proc = DEFAULT_WIN_PROC
	);

	Result CreateWindowFromClass(
		HWND* _handle,
		const WNDCLASS* _class,
		HMODULE _inst,
		WindowDescriptor _desc = WindowDescriptor(),
		LPVOID _appdata = nullptr
	);
}