#include <PathFilter/IMetaFilter.hpp>

#include <PathFilter/FilenameFilter.hpp>
#include <PathFilter/AlwaysMatchingFilter.hpp>

#include <PathFilter/ContentRegexFilter.hpp>


namespace lg {


std::vector<IMetaFilter::IMetaFilterPtr> IMetaFilter::createMetaFilters(const Options *options) {
	std::vector<IMetaFilter::IMetaFilterPtr> result{};

	if(options->mFilenameWildcard) {
		auto filter = std::make_unique<FilenameFilter>(*(options->mFilenameWildcard));
		result.push_back(std::move(filter));
	}


	return result;
}


std::unique_ptr<IContentFilter> IContentFilter::createContentFilter(const std::regex &contentRegex) {
	return std::make_unique<ContentRegexFilter>(contentRegex);
}



} // namespace lg
