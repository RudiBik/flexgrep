#pragma once

#include <filesystem>
#include <fstream>
#include <vector>

namespace lg {

class File
{
public:
	//!===============================================
	//! \brief ...
    //! 
    //! \throws ...
	//!----------------------------------------------- 
    File(const std::filesystem::path& p);

	File(const File &rhs) = delete;
	File& operator=(const File &rhs) = delete;

public:
    std::filesystem::path mPath;
    std::vector<char> mData;
};


} // namespace lg
