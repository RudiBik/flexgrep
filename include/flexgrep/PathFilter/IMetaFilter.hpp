// Copyright (c) 2022, Rudi Bikschentajew
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#pragma once

#include <File.hpp>
#include <Utilities/Configuration.hpp>

#include <filesystem>
#include <memory>
#include <regex>
#include <vector>

namespace lg {

class IMetaFilter
{
  public:
    virtual ~IMetaFilter() {}

  public:
    virtual bool check(const File::Meta& metaData) const = 0;
};

typedef std::unique_ptr<IMetaFilter> IMetaFilterUPtr;

} // namespace lg
