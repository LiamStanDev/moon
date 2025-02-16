#pragma once
#include <fcntl.h>
#include <nix/core.h>

#include <expected>
#include <filesystem>
#include <span>
#include <type_traits>

namespace nix {

namespace fs = std::filesystem;

struct FileHandle {
  int handle;
  FileHandle(int handle) : handle(handle) {}
};

enum class OpenFlag {
  Read = O_RDONLY,
  Write = O_WRONLY,
  ReadWrite = O_RDWR,
  Create = O_CREAT,
  Truncate = O_TRUNC,
  Append = O_APPEND,
};

inline OpenFlag operator|(OpenFlag lhs, OpenFlag rhs) {
  using T = std::underlying_type_t<OpenFlag>;
  return static_cast<OpenFlag>(static_cast<T>(lhs) | static_cast<T>(rhs));
}

enum class WhenceFlag {
  Start = SEEK_SET,
  Current = SEEK_CUR,
  End = SEEK_END,
};

Expected<FileHandle> Open(fs::path& path, OpenFlag flag) noexcept;

Expected<void> Close(FileHandle fd) noexcept;

Expected<int> Write(FileHandle fd, std::span<const char>) noexcept;

Expected<int> Read(FileHandle fd, std::span<char>) noexcept;

Expected<void> Sync(FileHandle fd) noexcept;

Expected<off_t> Seek(FileHandle fd, off_t offset, WhenceFlag flag) noexcept;

}  // namespace nix
