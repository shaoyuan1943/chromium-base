#include "base/base_time.h"
#include "gtest/include/gtest/gtest.h"

namespace {
  const int64 now = 1546529592; // 2019/1/3 23:33:12
  TEST(BaseTimeTest, TimeDelta) {
    auto td1 = base::TimeDelta::FromSeconds(now);
    EXPECT_EQ(td1.ToInternalValue(), now);

    auto td2 = base::TimeDelta::FromInternalValue(td1.ToInternalValue());
    EXPECT_EQ(td1, td2);
  }

  TEST(BaseTimeTest, Time) {
    base::Time t1;
    EXPECT_TRUE(t1.is_null());
    EXPECT_TRUE(!t1.is_max());

    auto t2 = base::Time::UnixEpoch();
    EXPECT_TRUE(!t2.is_null());

    {
      base::Time::Exploded el;
      t2.LocalExplode(&el);
      EXPECT_EQ(el.year, 2019);
      EXPECT_EQ(el.month, 1);
    }

    {
      auto t3 = base::Time::Now();
      EXPECT_TRUE(!t3.is_null());

      base::Time::Exploded el;
      t3.UTCExplode(&el);
      EXPECT_EQ(el.year, 2019);
      EXPECT_EQ(el.month, 1);
      }
  }
}
