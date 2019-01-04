#include "base/base_time.h"
#include "gtest/include/gtest/gtest.h"

namespace {
  const int64 now = 1546529592; // 2019/1/3 23:33:12
  TEST(BaseTimeTest, Time) {
    base::Time t1;
    EXPECT_TRUE(t1.is_null());
    EXPECT_TRUE(!t1.is_max());

    {
      auto t2 = base::Time::UnixEpoch();
      EXPECT_TRUE(!t2.is_null());

      base::Time::Exploded el;
      t2.LocalExplode(&el);
      EXPECT_EQ(el.year, 1970);
      EXPECT_TRUE(el.HasValidValues());
    }

    {
      auto t3 = base::Time::Now();
      EXPECT_TRUE(!t3.is_null());

      base::Time::Exploded el;
      t3.UTCExplode(&el);
      EXPECT_EQ(el.year, 2019);
    }
  }
}
