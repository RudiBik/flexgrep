#pragma once

#include <PathFilter/IContentFilter.hpp>

#include <filesystem>
#include <regex>


namespace lg {


//!================================================
//! \brief Used for filtering files based on the content of the files and a given regex
//!------------------------------------------------
class ContentRegexFilter : public IContentFilter {
public:
    //!================================================
	//! \param contentRegex
	//! \param skipBinaries A heuristic is used to determine if a file is a binary file. If this flag is set to true, all binary files won't pass the check
    //!------------------------------------------------
	ContentRegexFilter(const std::regex &contentRegex);

	virtual ~ContentRegexFilter() {}
    
	ContentRegexFilter(const ContentRegexFilter &rhs) = default;
	ContentRegexFilter& operator=(const ContentRegexFilter &rhs) = default;

public:
    //!================================================
	//! \brief A file passes this check if it contains at least one line which passes the content regex
    //!	
	//! \note Paths which point to nonexistent files or non-regular files will return false
    //!------------------------------------------------
	bool check(const FileSPtr pFile) const override;

private:

	//! \brief Prints prefix, suffix and matches to standard output
    //!	
    //! \param match contains the search results; Product of regex_search etc.
    //!------------------------------------------------
    void printSearchResult(const std::smatch &match) const;

private:
	std::regex mContentRegex;
};


} // namespace lg
