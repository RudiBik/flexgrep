#pragma once

#include <File.hpp>
#include <Utilities/Configuration.hpp>

#include <filesystem>
#include <memory>
#include <regex>
#include <vector>

namespace lg {

class IMetaFilter
{
  public:
    virtual ~IMetaFilter() {}

  public:
    virtual bool check(const File::Meta& metaData) const = 0;
};

typedef std::unique_ptr<IMetaFilter> IMetaFilterUPtr;

} // namespace lg
