#pragma once

#include <filesystem>


namespace lg {


bool pathContainsFile(const std::filesystem::path &rootPath, const std::filesystem::path &file);


//!================================================
//! \brief Uses a heuristic to determmine on the first <256bytes if a file is a binary file or not
//!------------------------------------------------
bool isBinaryFile(const char* pBuffer, int size);

} // lg
