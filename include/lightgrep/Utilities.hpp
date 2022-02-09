#pragma once

#include <filesystem>


namespace lg {


bool pathContainsFile(const std::filesystem::path &rootPath, const std::filesystem::path &file);


} // lg
