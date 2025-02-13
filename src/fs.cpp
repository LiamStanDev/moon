#include <moon/fs.h>
#include <unistd.h>

namespace moon {

void Read(FileHandle fd, Span<char> buf) {
  ::read(fd.handle, buf.data, buf.size);
}

std::optional<FileHandle> Open(fs::path& path, OpenFlag flag) {
  int fd = ::open(path.c_str(), static_cast<int>(flag));
  if (fd == -1) {
    return std::nullopt;
  }
  return FileHandle{fd};
}

void Close(FileHandle fd) { ::close(fd.handle); }

}  // namespace moon
