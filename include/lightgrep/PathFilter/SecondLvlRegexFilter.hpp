#pragma once

#include <PathFilter/IPathFilter.hpp>

#include <filesystem>
#include <regex>


namespace lg {


//!================================================
//! \brief Used for filtering files based on the content of the files and a given regex
//!------------------------------------------------
class SecondLvlRegexFilter : public IPathFilter {
public:
    //!================================================
	//! \param contentRegex
	//! \param skipBinaries A heuristic is used to determine if a file is a binary file. If this flag is set to true, all binary files won't pass the check
    //!------------------------------------------------
	SecondLvlRegexFilter(const std::regex &contentRegex, bool skipBinaries);

	virtual ~SecondLvlRegexFilter() {}
    
	SecondLvlRegexFilter(const SecondLvlRegexFilter &rhs) = default;
	SecondLvlRegexFilter& operator=(const SecondLvlRegexFilter &rhs) = default;

public:
    //!================================================
	//! \brief A file passes this check if it contains at least one line which passes the content regex
    //!	
	//! \note Paths which point to nonexistent files or non-regular files will return false
    //!------------------------------------------------
	bool check(const std::filesystem::path &path) const override;

private:
    //!================================================
	//! \brief Uses a heuristic to determmine on the first <256bytes if a file is a binary file or not
    //!------------------------------------------------
	bool isBinaryFile(const char* pBuffer, int size) const;

	//! \brief Prints prefix, suffix and matches to standard output
    //!	
    //! \param match contains the search results; Product of regex_search etc.
    //!------------------------------------------------
    void printSearchResult(const std::smatch &match) const;

private:
	std::regex mContentRegex;
	bool mSkipBinaries;
};


} // namespace lg
