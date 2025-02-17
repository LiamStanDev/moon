#include <nix/core.h>

namespace nix {

Expected<ssize_t> PoxisErrorToExpected(ssize_t ret) noexcept {
  if (ret == -1) {
    return std::unexpected{std::error_code(errno, std::system_category())};
  }
  return ret;
}
}  // namespace nix
