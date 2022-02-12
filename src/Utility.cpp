// Copyright (c) 2022, Rudi Bikschentajew
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <Utilities/Utilities.hpp>
#include <algorithm>
#include <string>
#include <vector>

namespace lg {

using namespace std::filesystem;
using namespace std;

bool
pathContainsFile(const path& rootPath, const path& file)
{
    string fileString = file.string();
    string pathFilenameString = rootPath.filename().string();

    std::vector<size_t> positions;
    size_t pos = fileString.find(pathFilenameString, 0);
    while (pos != string::npos) {
        positions.push_back(pos);
        pos = fileString.find(pathFilenameString, pos + 1);
    }

    for (const auto pos : positions) {
        path subPath(fileString.begin(),
                     fileString.begin() + pos + pathFilenameString.size());

        if (exists(subPath) && equivalent(rootPath, subPath))
            return true;
    }

    return false;
}

bool
isBinaryFile(const char* pBuffer, int bufferSize, size_t fileSize)
{
    static constexpr size_t MAX_SIZE = 100000000; // 1 GB
    if (fileSize > MAX_SIZE) {
        return true;
    }

    if (bufferSize > 8192)
        bufferSize = 8192;

    unsigned char numberOfUnprintableCharacters = 0;
    for (int i = 0; i < bufferSize; ++i) {
        // On windows iscntrl is throwing an exception on chars < -1
#ifdef _WIN32
        if (pBuffer[i] == '\0') {
            ++numberOfUnprintableCharacters;
        }
#else
        if ((!isprint(pBuffer[i]) && !iscntrl(pBuffer[i])) ||
            (pBuffer[i] == '\0')) {
            ++numberOfUnprintableCharacters;
        }
#endif
    }

    return (numberOfUnprintableCharacters > 1);
}

} // namespace lg
