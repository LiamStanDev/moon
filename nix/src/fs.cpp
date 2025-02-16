#include <error.h>
#include <nix/core.h>
#include <nix/fs.h>
#include <unistd.h>

namespace nix {

Expected<FileHandle> Open(fs::path& path, OpenFlag flag) noexcept {
  auto ret = ExpectedStdError(::open(path.c_str(), static_cast<int>(flag)));
  if (!ret) {
    return ret;
  }

  return ret.transform([](int fd) { return FileHandle{fd}; });
}

Expected<void> Close(FileHandle fd) noexcept {
  auto ret = ExpectedStdError(::close(fd.handle));
  if (!ret) {
    return std::unexpected{ret.error()};
  }
  return {};
}

Expected<int> Write(FileHandle fd, std::span<const char> buffer) noexcept {
  return ExpectedStdError(::write(fd.handle, buffer.data(), buffer.size()));
}

Expected<int> Read(FileHandle fd, std::span<char> buffer) noexcept {
  return ExpectedStdError(::read(fd.handle, buffer.data(), buffer.size()));
}

Expected<void> Sync(FileHandle fd) noexcept {
  auto ret = ExpectedStdError(::fsync(fd.handle) == -1);
  if (!ret) {
    return std::unexpected{ret.error()};
  }
  return {};
}

Expected<off_t> Seek(FileHandle fd, off_t offset, WhenceFlag flag) noexcept {
  return ExpectedStdError(::lseek(fd.handle, offset, static_cast<int>(flag)));
}

}  // namespace nix
