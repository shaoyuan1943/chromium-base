// Copyright (c) 2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file contains the unit tests for the bit utilities.

#include <io.h>
#include <iostream>

#include "base/bits.h"
#include "gtest/include/gtest/gtest.h"

using namespace testing;

TEST(BitsTest, Log2Floor) {
  EXPECT_EQ(-1, base::bits::Log2Floor(0));
  EXPECT_EQ(0, base::bits::Log2Floor(1));
  EXPECT_EQ(1, base::bits::Log2Floor(2));
  EXPECT_EQ(1, base::bits::Log2Floor(3));
  EXPECT_EQ(2, base::bits::Log2Floor(4));
  for (int i = 3; i < 31; ++i) {
    unsigned int value = 1U << i;
    EXPECT_EQ(i, base::bits::Log2Floor(value));
    EXPECT_EQ(i, base::bits::Log2Floor(value + 1));
    EXPECT_EQ(i, base::bits::Log2Floor(value + 2));
    EXPECT_EQ(i - 1, base::bits::Log2Floor(value - 1));
    EXPECT_EQ(i - 1, base::bits::Log2Floor(value - 2));
  }
  EXPECT_EQ(31, base::bits::Log2Floor(0xffffffffU));
}

TEST(BitsTest, Log2Ceiling) {
  EXPECT_EQ(-1, base::bits::Log2Ceiling(0));
  EXPECT_EQ(0, base::bits::Log2Ceiling(1));
  EXPECT_EQ(1, base::bits::Log2Ceiling(2));
  EXPECT_EQ(2, base::bits::Log2Ceiling(3));
  EXPECT_EQ(2, base::bits::Log2Ceiling(4));
  for (int i = 3; i < 31; ++i) {
    unsigned int value = 1U << i;
    EXPECT_EQ(i, base::bits::Log2Ceiling(value));
    EXPECT_EQ(i + 1, base::bits::Log2Ceiling(value + 1));
    EXPECT_EQ(i + 1, base::bits::Log2Ceiling(value + 2));
    EXPECT_EQ(i, base::bits::Log2Ceiling(value - 1));
    EXPECT_EQ(i, base::bits::Log2Ceiling(value - 2));
  }
  EXPECT_EQ(32, base::bits::Log2Ceiling(0xffffffffU));
}
