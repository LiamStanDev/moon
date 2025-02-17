#include <error.h>
#include <nix/core.h>
#include <nix/fs.h>
#include <unistd.h>

namespace nix {

Expected<FileHandle> Open(fs::path& path, OpenFlag flag) noexcept {
  auto ret = PoxisErrorToExpected(::open(path.c_str(), static_cast<int>(flag)));
  if (!ret) {
    return ret;
  }

  return ret.transform([](int fd) { return FileHandle{fd}; });
}

Expected<void> Close(FileHandle fd) noexcept {
  auto ret = PoxisErrorToExpected(::close(fd.handle));
  if (!ret) {
    return std::unexpected{ret.error()};
  }
  return {};
}

Expected<int> Write(FileHandle fd, std::span<const char> buffer) noexcept {
  return PoxisErrorToExpected(::write(fd.handle, buffer.data(), buffer.size()));
}

Expected<int> Read(FileHandle fd, std::span<char> buffer) noexcept {
  return PoxisErrorToExpected(::read(fd.handle, buffer.data(), buffer.size()));
}

Expected<void> Sync(FileHandle fd) noexcept {
  auto ret = PoxisErrorToExpected(::fsync(fd.handle));
  if (!ret) {
    return std::unexpected{ret.error()};
  }
  return {};
}

Expected<off_t> Seek(FileHandle fd, off_t offset, WhenceFlag flag) noexcept {
  return PoxisErrorToExpected(
      ::lseek(fd.handle, offset, static_cast<int>(flag)));
}

}  // namespace nix
