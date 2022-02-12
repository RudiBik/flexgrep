// Copyright (c) 2022, Rudi Bikschentajew
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <PathFilter/FilenameMetaFilter.hpp>

namespace lg {

FilenameMetaFilter::FilenameMetaFilter(const Wildcard& wildcard)
  : wc(wildcard)
{}

bool
FilenameMetaFilter::check(const File::Meta& metaData) const
{
    return wc.match(metaData.filePath.filename().string());
}

} // namespace lg
