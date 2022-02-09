#pragma once

#include <PathFilter/IMetaFilter.hpp>
#include <Utilities/Wildcard.hpp>

#include <filesystem>

namespace lg {

//!================================================
//! \brief Very basic Filter that checks only the following parameter:
//!        Filename: The filenames of all incoming paths have to match the
//!        provided filename wildcard
//!------------------------------------------------
class FilenameMetaFilter : public IMetaFilter
{
  public:
    FilenameMetaFilter(const Wildcard& wildcard);

    virtual ~FilenameMetaFilter() {}

    FilenameMetaFilter(const FilenameMetaFilter& rhs) = default;
    FilenameMetaFilter& operator=(const FilenameMetaFilter& rhs) = default;

  public:
    //!================================================
    //! Returns true if the filename of the path matches the wildcard
    //!------------------------------------------------
    bool check(const File::Meta& metaData) const override;

  private:
    Wildcard wc;
};

} // namespace lg
