// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/base64.h"

#include "gtest/include/gtest/gtest.h"

namespace {

TEST(Base64Test, Basic) {
  const std::string kText = "hello world";
  const std::string kBase64Text = "aGVsbG8gd29ybGQ=";

  char* encode = new char[base::Base64EncodeLength(kText)];
  char* decode = nullptr;
  bool ok = false;;
  size_t encodeLength = 0, decodeLength = 0;

   ok = base::Base64Encode(kText, encode, &encodeLength);
   EXPECT_TRUE(ok);
   EXPECT_EQ(kBase64Text, std::string(encode, encodeLength));

   decode = new char[base::Base64DecodeLength(std::string(encode, encodeLength))];
   ok = base::Base64Decode(std::string(encode, encodeLength), decode, &decodeLength);
   EXPECT_TRUE(ok);
   EXPECT_EQ(kText, std::string(decode, decodeLength));
}

}  // namespace base
