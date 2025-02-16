#pragma once
#include <sys/types.h>

#include <expected>
#include <system_error>

namespace nix {

template <class T>
using Expected = std::expected<T, std::error_code>;

Expected<ssize_t> ExpectedStdError(ssize_t ret) noexcept;
}  // namespace nix
