#include "Error.h"

namespace Engine::Win32 {
	const bool Result::Succeeded() const {
		return SUCCEEDED(HRESULT(type));
	}
}