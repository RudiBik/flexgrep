// Copyright (c) 2022, Rudi Bikschentajew
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include "PathFilter/ContentRegexFilter.hpp"

#include <ContentProcessors/IContentProcessor.hpp>
#include <Utilities/Utilities.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace lg {

ContentRegexFilter::ContentRegexFilter(const std::regex& contentRegex)
  : mContentRegex(contentRegex)
{
    // TODO: Log a warning on suspicious regex
}

bool
ContentRegexFilter::check(const FileSPtr pFile) const
{
    std::stringstream reader(
      std::string(pFile->mData.begin(), pFile->mData.end()));

    std::smatch match;
    std::string line;
    while (std::getline(reader, line)) {
        if (std::regex_search(line, match, mContentRegex)) {
            printSearchResult(match);
            return true;
        }
    }

    return false;
}

void
ContentRegexFilter::printSearchResult(const std::smatch& match) const
{
    std::cout << "\n";
    std::cout << "\033[90m" << match.prefix() << "\033[0m";
    for (size_t i = 0; i < match.size(); ++i) {
        std::cout << "\033[1;31m" << match[i] << "\033[0m";
    }
    std::cout << "\033[90m" << match.suffix() << "\033[0m\n";
}

} // namespace lg
