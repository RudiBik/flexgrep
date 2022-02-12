// Copyright (c) 2022, Rudi Bikschentajew
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#pragma once

#include <Utilities/Wildcard.hpp>

#include <filesystem>
#include <regex>
#include <string>

namespace lg {

//!===============================================
//! \brief Responsible for checking the semantics of the input for the Flexgrep
//! class
//!-----------------------------------------------
class Configuration
{
  public:
    Configuration(const std::string& rootPath,
                  const std::string& filenameWildcard,
                  const std::string& regexContent,
                  bool bskipBinaries,
                  bool bParallelFiltering);

    // Enabling / Disabling optional features
    // ...

    std::filesystem::path mRootPath;

    std::unique_ptr<Wildcard> mFilenameWildcard;
    std::regex mRegexContent;

    bool mSkipBinaries;
    bool mParallelContentFiltering{ false };
};

} // namespace lg
