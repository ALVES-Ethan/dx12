#include "Win.h"

namespace Engine::Win32{
	Result RegisterWindowClass(WNDCLASS* _class, HMODULE _inst, wcstr _name, WNDPROC _proc) {
		if (_class == nullptr)
			return Fatal(Type::InvalidPointer);

		if (_name == nullptr)
			return Fatal(Type::InvalidArguments);

		_class->lpfnWndProc = _proc;
		_class->hInstance = _inst;
		_class->lpszClassName = _name;

		if (!RegisterClass(_class))
			return Fatal(Type::UnexpectedFailure);

		return Success();
	}

	Result CreateWindowFromClass(HWND* _handle, const WNDCLASS* _class, HMODULE _inst, WindowDescriptor _desc, LPVOID _appdata) {
		if(_handle == nullptr)
			return Fatal(Type::InvalidPointer);

		if (_class == nullptr)
			return Fatal(Type::InvalidPointer);
		
		*_handle = CreateWindowEx(
			0,                      // Optional window styles.
			_class->lpszClassName,  // Window class
			_desc.title,			// Window text
			WS_OVERLAPPEDWINDOW,    // Window style

			// Position and size
			_desc.x, _desc.y, _desc.width, _desc.height,

			NULL,		// Parent window    
			NULL,		// Menu
			_inst,		// Instance handle
			_appdata	// Additional application data
		);

		if (*_handle == NULL)
			return Fatal(Type::UnexpectedFailure);

		return Success();
	}
}