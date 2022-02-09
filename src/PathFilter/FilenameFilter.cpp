#include <PathFilter/FilenameFilter.hpp>

namespace lg {

FilenameFilter::FilenameFilter(const Wildcard &wildcard) : wc(wildcard) {}


bool FilenameFilter::check(const std::filesystem::path &path) const {
	return wc.match(path.filename().string());
}

} // namespace lg
