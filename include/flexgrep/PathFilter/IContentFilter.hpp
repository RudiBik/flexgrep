// Copyright (c) 2022, Rudi Bikschentajew
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#pragma once

#include <File.hpp>

#include <memory>
#include <regex>

namespace lg {

class File;

class IContentFilter
{
  public:
    virtual ~IContentFilter() {}

  public:
    virtual bool check(const FileSPtr pFile) const = 0;
};

} // namespace lg
