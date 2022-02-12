// Copyright (c) 2022, Rudi Bikschentajew
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#pragma once

#include <filesystem>

namespace lg {

bool
pathContainsFile(const std::filesystem::path& rootPath,
                 const std::filesystem::path& file);

//!================================================
//! \brief Uses a heuristic to determmine on the first <8192bytes if a file is a
//!        binary file or not or if the size is very big
//!------------------------------------------------
bool
isBinaryFile(const char* pBuffer, int size, size_t filesize);

} // lg
