#include <Flexgrep.hpp>
#include <Utilities/Utilities.hpp>
#include <filesystem>
#include <iostream>

#include <PathFilter/AlwaysMatchingFilter.hpp>
#include <PathFilter/BinaryMetaFilter.hpp>
#include <PathFilter/FilenameMetaFilter.hpp>
#include <PathFilter/IMetaFilter.hpp>

namespace lg {

using namespace std;
using namespace std::filesystem;

void
Flexgrep::searchAndOutput()
{
    processDirectory(mOptions->mRootPath);

    mContentFilter->join();
}

void
Flexgrep::processDirectory(const path& p)
{
    // TODO: check if it is excluded

    for (const auto& p : directory_iterator(p)) {
        if (p.is_symlink()) {
            processSymlink(p);

        } else if (p.is_directory()) {
            // when following a symlink, don't enter the root directory
            // reccursively
            if (mCurrentSymlink && equivalent(p, mOptions->mRootPath))
                continue;

            processDirectory(p);

        } else if (p.is_regular_file()) {
            processRegular(p);

        } else {
            // TODO: Throw an error
        }
    }
}

void
Flexgrep::processRegular(const path& p)
{
    FileSPtr pFile;
    try {
        // Constructor loads the meta data
        pFile = std::make_shared<File>(p);
    } catch (...) {
        // TODO: Some error or warning, file could not be opened
        return;
    }

    if (passesMetaFilters(pFile->mMetaData)) {
        if (!pFile->loadContent()) {
            // TODO:: error or warning
            return;
        }

        mContentFilter->process(pFile);
    }
}

void
Flexgrep::processSymlink(const path& p)
{
    path linkedFile = read_symlink(p);

    if (exists(linkedFile)) {
        // dont't follow symlinks that point to a file under the root search
        // directory
        if (pathContainsFile(mOptions->mRootPath, linkedFile)) {
            // TODO: Log that this file is skipped
            return;
        }

        if (is_regular_file(linkedFile)) {
            processRegular(linkedFile);

        } else if (is_directory(linkedFile)) {
            // follow symbolic links only once
            if (mCurrentSymlink)
                return;

            mCurrentSymlink = p;
            processDirectory(linkedFile);
            mCurrentSymlink = std::nullopt;
        }
    }
}

bool
Flexgrep::passesMetaFilters(const File::Meta& metaData) const
{
    for (const auto& filter : mMetaFilters) {
        if (!filter->check(metaData))
            return false;
    }

    return true;
}

std::vector<IMetaFilterUPtr>
Flexgrep::createMetaFilters(const Options* options)
{
    std::vector<IMetaFilterUPtr> result{};

    if (options->mSkipBinaries) {
        auto filter = std::make_unique<BinaryMetaFilter>();
        result.push_back(std::move(filter));
    }

    if (options->mFilenameWildcard) {
        auto filter =
          std::make_unique<FilenameMetaFilter>(*(options->mFilenameWildcard));
        result.push_back(std::move(filter));
    }

    return result;
}

} // namespace lg
