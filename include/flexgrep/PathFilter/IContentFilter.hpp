#pragma once

#include <File.hpp>

#include <memory>
#include <regex>

namespace lg {

class File;

class IContentFilter
{
  public:
    virtual ~IContentFilter() {}

  public:
    virtual bool check(const FileSPtr pFile) const = 0;
};

} // namespace lg
