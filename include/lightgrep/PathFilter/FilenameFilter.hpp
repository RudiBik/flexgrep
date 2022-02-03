#pragma once

#include <Wildcard.hpp>
#include <PathFilter/IMetaFilter.hpp>

#include <filesystem>


namespace lg {


//!================================================
//! \brief Very basic Filter that checks only the following parameter:
//! Filename: The filenames of all incoming paths have to match the filename wildcard from the given Options.
//!------------------------------------------------
class FilenameFilter : public IMetaFilter {
public:
	FilenameFilter(const Wildcard &wildcard);

	virtual ~FilenameFilter() {}

	FilenameFilter(const FilenameFilter &rhs) = default;
	FilenameFilter& operator=(const FilenameFilter &rhs) = default;

public:
    //!================================================
	//! Returns true if the filename of the path matches the wildcard
    //!------------------------------------------------
	bool check(const File::Meta& metaData) const override;

private:
	Wildcard wc;
};


} // namespace lg
