#include <fcntl.h>
#include <moon/span.h>

#include <filesystem>
#include <optional>

namespace moon {
namespace fs = std::filesystem;

struct FileHandle {
  int handle;
  FileHandle(int handle) : handle(handle) {}
};

enum class OpenFlag {
  Red = O_RDONLY,
  Write = O_WRONLY,
  ReadWrite = O_RDWR,
  Create = O_CREAT,
  Truncate = O_TRUNC,
  Append = O_APPEND,
};

void Read(FileHandle fd, Span<char> buf);

std::optional<FileHandle> Open(fs::path& path, OpenFlag flag);

void Close(FileHandle fd);

}  // namespace moon
