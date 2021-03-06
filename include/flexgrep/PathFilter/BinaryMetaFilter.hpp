// Copyright (c) 2022, Rudi Bikschentajew
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#pragma once

#include <PathFilter/IMetaFilter.hpp>
#include <iostream>

namespace lg {

class BinaryMetaFilter : public IMetaFilter
{
  public:
    BinaryMetaFilter() {}

    virtual ~BinaryMetaFilter() {}

    BinaryMetaFilter(const BinaryMetaFilter& rhs) = default;
    BinaryMetaFilter& operator=(const BinaryMetaFilter& rhs) = default;

  public:
    //!================================================
    //! Returns true if the file is not a binary file
    //!------------------------------------------------
    bool check(const File::Meta& metaData) const override
    {
        return (metaData.binary == false);
    }
};

} // namespace lg
