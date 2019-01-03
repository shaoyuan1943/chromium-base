// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/base64.h"
#include "base/logging.h"
#include "third_party/modp_b64/modp_b64.h"

namespace base {

bool Base64Encode(const StringPiece& input, char* output, size_t* encodeLength) {
  DCHECK(output != nullptr);
  std::string temp;
  temp.resize(modp_b64_encode_len(input.size()));  // makes room for null byte

  // null terminates result since result is base64 text!
  int input_size = static_cast<int>(input.size());

  // modp_b64_encode_len() returns at least 1, so temp[0] is safe to use.
  int output_size = modp_b64_encode(&(temp[0]), input.data(), input_size);
  if (output_size < 0)
    return false;

  temp.resize(output_size);  // strips off null byte

  memcpy(output, temp.data(), temp.size());
  *encodeLength = temp.size();
  return true;
}

bool Base64Decode(const StringPiece& input, char* output, size_t* decodeLength) {
  DCHECK(output != nullptr);
  std::string temp;
  temp.resize(modp_b64_decode_len(input.size()));

  // does not null terminate result since result is binary data!
  int input_size = static_cast<int>(input.size());
  int output_size = modp_b64_decode(&(temp[0]), input.data(), input_size);
  if (output_size < 0)
    return false;

  temp.resize(output_size);

  memcpy(output, temp.data(), temp.size());
  *decodeLength = temp.size();
  return true;
}

size_t Base64EncodeLength(const StringPiece& input) {
  return modp_b64_encode_len(input.size()) + 10;
}

size_t Base64DecodeLength(const StringPiece& input) {
  return modp_b64_decode_len(input.size() + 10);
}

}  // namespace base
