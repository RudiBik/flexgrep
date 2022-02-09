#include <PathFilter/FilenameMetaFilter.hpp>

namespace lg {

FilenameMetaFilter::FilenameMetaFilter(const Wildcard& wildcard)
  : wc(wildcard)
{}

bool
FilenameMetaFilter::check(const File::Meta& metaData) const
{
    return wc.match(metaData.filePath.filename().string());
}

} // namespace lg
