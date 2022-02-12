// Copyright (c) 2022, Rudi Bikschentajew
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#pragma once

#include <filesystem>
#include <fstream>
#include <vector>

namespace lg {

class File
{
  public:
    struct Meta
    {
        std::filesystem::path filePath;
        size_t fileSize;
        bool binary;
        // Other metadata like permissions, ...
    };

  public:
    //!===============================================
    //! \brief ...
    //!
    //! \throws ...
    //!-----------------------------------------------
    File(const std::filesystem::path& p);

    bool loadContent();
    void unloadContent();

    File(const File& rhs) = delete;
    File& operator=(const File& rhs) = delete;

  public:
    Meta mMetaData;
    std::vector<char> mData;
};

using FileSPtr = std::shared_ptr<File>;

} // namespace lg
