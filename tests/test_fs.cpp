#include <gtest/gtest.h>
#include <nix/fs.h>

#include <clocale>
#include <fstream>
#include <system_error>

namespace fs = std::filesystem;
TEST(FsTest, OpenFileWithNonExit) {
  auto path = fs::path("/aa/bb.txt");
  nix::Expected<nix::FileHandle> ret = nix::Open(path, nix::OpenFlag::Read);
  EXPECT_EQ(ret.error(), std::errc::no_such_file_or_directory);
}

TEST(FsTest, OpenAndCloseFile) {
  auto path = fs::temp_directory_path() / "testfile.txt";
  {
    auto ofs = std::ofstream{path};
    ofs << "test";
  }

  auto ret = nix::Open(path, nix::OpenFlag::Read);
  ASSERT_TRUE(ret.has_value());
  auto fd = ret.value();

  auto close_ret = nix::Close(fd);
  EXPECT_TRUE(close_ret.has_value());

  std::filesystem::remove(path);
}

TEST(FsTest, ReadFile) {
  auto path = fs::temp_directory_path() / "testfile.txt";
  {
    std::ofstream ofs{path};
    ofs << "test";
  }

  auto ret = nix::Open(path, nix::OpenFlag::Read);
  ASSERT_TRUE(ret.has_value());
  auto fd = ret.value();

  std::vector<char> buffer(4);
  auto read_ret = nix::Read(fd, buffer);
  ASSERT_TRUE(read_ret.has_value());
  EXPECT_EQ(read_ret.value(), 4);
  EXPECT_EQ(std::string(buffer.data(), buffer.size()), "test");

  auto close_ret = nix::Close(fd);
  std::filesystem::remove(path);
}

TEST(FsTest, WriteFile) {
  auto path = fs::temp_directory_path() / "testfile.txt";

  auto ret = nix::Open(path, nix::OpenFlag::Write | nix::OpenFlag::Create);
  ASSERT_TRUE(ret.has_value());
  auto fd = ret.value();

  const std::string data = "test";
  auto write_ret =
      nix::Write(fd, std::span<const char>(data.data(), data.size()));
  ASSERT_TRUE(write_ret.has_value());
  EXPECT_EQ(write_ret.value(), 4);

  auto close_ret = nix::Close(fd);

  std::ifstream ifs(path);
  std::string content((std::istreambuf_iterator<char>{ifs}),
                      (std::istreambuf_iterator<char>{}));
  EXPECT_EQ(content, "test");

  std::filesystem::remove(path);
}

TEST(FsTest, LseekFile) {
  auto path = fs::temp_directory_path() / "testfile.txt";
  {
    std::ofstream ofs(path);
    ofs << "test";
  }

  auto ret = nix::Open(path, nix::OpenFlag::Read);
  ASSERT_TRUE(ret.has_value());
  auto fd = ret.value();

  auto lseek_ret = nix::Seek(fd, 2, nix::WhenceFlag::Start);
  ASSERT_TRUE(lseek_ret.has_value());
  EXPECT_EQ(lseek_ret.value(), 2);

  std::vector<char> buffer(2);
  auto read_ret = nix::Read(fd, buffer);
  ASSERT_TRUE(read_ret.has_value());
  EXPECT_EQ(read_ret.value(), 2);
  EXPECT_EQ(std::string(buffer.data(), buffer.size()), "st");

  auto close_ret = nix::Close(fd);
  std::filesystem::remove(path);
}

TEST(FsTest, FsyncFile) {
  auto path = fs::temp_directory_path() / "testfile.txt";

  auto ret = nix::Open(path, nix::OpenFlag::Write | nix::OpenFlag::Create);
  ASSERT_TRUE(ret.has_value());
  auto fd = ret.value();

  std::string data = "test";
  auto write_ret =
      nix::Write(fd, std::span<const char>(data.data(), data.size()));
  ASSERT_TRUE(write_ret.has_value());
  EXPECT_EQ(write_ret.value(), 4);

  auto fsync_ret = nix::Sync(fd);
  EXPECT_TRUE(fsync_ret.has_value());

  auto close_ret = nix::Close(fd);
  std::filesystem::remove(path);
}
