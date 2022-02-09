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
class Options
{
  public:
    Options(const std::string& rootPath,
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
