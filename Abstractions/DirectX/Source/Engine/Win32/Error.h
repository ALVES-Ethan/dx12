#pragma once

#include "Win32.h"
#include "../Common/Types.h"

namespace Engine::Win32 {
    enum class Level : byte {
        Success,        // OK
        Recoverable,    // Can retry / continue
        Fatal           // Must terminate
    };

    enum class Type : HRESULT {
        OperationSuccessful     = S_OK,
        OperationAborted        = E_ABORT,
        AccessDenied            = E_ACCESSDENIED,
        UnspecifiedFailure      = E_FAIL,
        InvalidHandle           = E_HANDLE,
        InvalidArguments        = E_INVALIDARG,
        NoSuchInterface         = E_NOINTERFACE,
        NotImplemented          = E_NOTIMPL,
        OutOfMemory             = E_OUTOFMEMORY,
        InvalidPointer          = E_POINTER,
        UnexpectedFailure       = E_UNEXPECTED
    };

    struct Result {
        Level level;
        Type type;
        const bool Succeeded() const;
    };

    constexpr Result Success() { return Result{ Level::Success, Type::OperationSuccessful }; }
    constexpr Result Recoverable(Type _type = Type::UnexpectedFailure) { return Result{ Level::Recoverable, _type }; }
    constexpr Result Fatal(Type _type = Type::UnexpectedFailure) { return Result{ Level::Fatal, _type }; }
}