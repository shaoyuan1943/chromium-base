// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

//
// Deal with the differences between Microsoft and GNU implemenations
// of hash_map. Allows all platforms to use |base::hash_map| and
// |base::hash_set|.
//  eg:
//   base::hash_map<int> my_map;
//   base::hash_set<int> my_set;
//
// NOTE: It is an explicit non-goal of this class to provide a generic hash
// function for pointers.  If you want to hash a pointers to a particular class,
// please define the template specialization elsewhere (for example, in its
// header file) and keep it specific to just pointers to that class.  This is
// because identity hashes are not desirable for all types that might show up
// in containers as pointers.

#ifndef BASE_HASH_TABLES_H_
#define BASE_HASH_TABLES_H_

#include "build/build_config.h"
#include "base/string16.h"
#include "base/file_path.h"

#include <functional>
#include <unordered_map>
#include <unordered_set>

namespace std {

  template <>
  struct hash <FilePath> {
    size_t operator()(const FilePath& f) const {
      return hash<FilePath::StringType>()(f.value());
    }
  };

  template <>
  struct hash<base::StringPiece> {
    size_t operator()(const base::StringPiece& sp) const {
      size_t result = 0;
      for (base::StringPiece::const_iterator i = sp.begin(); i != sp.end(); ++i) {
        result = (result * 131) + *i;
      }

      return result;
    }
  };

  template <>
  struct hash<base::StringPiece16> {
    size_t operator()(const base::StringPiece16& sp) const {
      size_t result = 0;
      for (base::StringPiece16::const_iterator i = sp.begin(); i != sp.end(); ++i) {
        result = (result * 131) + *i;
      }

      return result;
    }
  };

}

#endif  // BASE_HASH_TABLES_H_
