// Copyright (c) 2022, Rudi Bikschentajew
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#pragma once

#include <filesystem>

#include <PathFilter/IMetaFilter.hpp>

namespace lg {

class AlwaysMatchingFilter : public IMetaFilter
{
  public:
    AlwaysMatchingFilter() {}

  public:
    virtual bool check(const File::Meta& metaData) const { return true; }
};

} // namespace lg
