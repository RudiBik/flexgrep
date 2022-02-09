#pragma once

#include <filesystem>

#include <PathFilter/IMetaFilter.hpp>

namespace lg {

class AlwaysMatchingFilter : public IMetaFilter
{
  public:
    AlwaysMatchingFilter() {}

  public:
    virtual bool check(const File::Meta& metaData) const { return true; }
};

} // namespace lg
