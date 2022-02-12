// Copyright (c) 2022, Rudi Bikschentajew
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include "Utilities/Configuration.hpp"

namespace lg {

using namespace std::filesystem;

Configuration::Configuration(const std::string& rootPath,
                             const std::string& filenameWildcard,
                             const std::string& regexContent,
                             bool bskipBinaries,
                             bool bParallelContentFiltering)
{
    if (!exists(rootPath) || !is_directory(rootPath)) {
        // TOTO Output error message and quit
    }
    mRootPath = rootPath;

    // TOTO: check if filenameWildcard is valid
    if (!filenameWildcard.empty())
        mFilenameWildcard = std::make_unique<Wildcard>(filenameWildcard);
    else
        mFilenameWildcard = nullptr;

    // TODO: check if regexContent is valid
    mRegexContent = std::regex(regexContent);

    mSkipBinaries = bskipBinaries;
    mParallelContentFiltering = bParallelContentFiltering;
}

} // namespace lg
