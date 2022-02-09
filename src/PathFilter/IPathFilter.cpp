#include <PathFilter/IPathFilter.hpp>

#include <PathFilter/FilenameFilter.hpp>
#include <PathFilter/AlwaysMatchingFilter.hpp>
#include <PathFilter/SecondLvlRegexFilter.hpp>

namespace lg {


std::vector<IPathFilter::IPathFilterPtr> IPathFilter::createFirstLevelFilter(const Options *options) {
	std::vector<IPathFilter::IPathFilterPtr> result{};

	if(options->mFilenameWildcard) {
		auto filter = std::make_unique<FilenameFilter>(*(options->mFilenameWildcard));
		result.push_back(std::move(filter));
	}


	return result;
}


std::unique_ptr<IPathFilter> IPathFilter::createSecondLevelFilter(const std::regex &contentRegex, bool skipBinaries) {
	return std::make_unique<SecondLvlRegexFilter>(contentRegex, skipBinaries);
}


} // namespace lg
