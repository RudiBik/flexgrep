#include <PathFilter/FilenameFilter.hpp>

namespace lg {

FilenameFilter::FilenameFilter(const Wildcard &wildcard) : wc(wildcard) {}


bool FilenameFilter::check(const File::Meta& metaData) const {
	return wc.match(metaData.filePath.filename().string());
}

} // namespace lg
