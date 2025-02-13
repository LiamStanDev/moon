#include <gtest/gtest.h>
#include <moon/span.h>

#include <array>
#include <vector>

using namespace moon;

TEST(SpanTest, Construct) {
  char buf[30];
  auto s = Span<char>{buf};

  EXPECT_EQ(s.size, sizeof(buf));
  EXPECT_EQ(s.data, buf);
  EXPECT_NE(s.data, nullptr);

  auto s2 = Span<char>{buf};
  EXPECT_EQ(s2.size, sizeof(buf));
  EXPECT_EQ(s2.data, buf);

  std::array<char, 30> buf2;
  Span<char> s3 = buf2;
  EXPECT_EQ(s3.size, buf2.size());
  EXPECT_EQ(s3.data, buf2.data());

  std::vector<int> buf3(30);
  Span<int> s4 = buf3;

  EXPECT_EQ(s4.size, buf3.size());
  EXPECT_EQ(s4.data, buf3.data());
}
