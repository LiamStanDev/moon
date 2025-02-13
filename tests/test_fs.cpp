#include <gtest/gtest.h>
#include <moon/fs.h>

#include <clocale>

TEST(FsTest, Read) {
  namespace fs = std::filesystem;
  moon::FileHandle fd{0};
  char buf[30];
  moon::Read(fd, moon::Span<char>{buf});
}
