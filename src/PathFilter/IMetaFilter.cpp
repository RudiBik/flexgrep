#include <PathFilter/IMetaFilter.hpp>

#include <PathFilter/FilenameFilter.hpp>
#include <PathFilter/BinaryMetaFilter.hpp>
#include <PathFilter/AlwaysMatchingFilter.hpp>


namespace lg {


std::vector<IMetaFilter::IMetaFilterPtr> IMetaFilter::createMetaFilters(const Options *options) {
	std::vector<IMetaFilter::IMetaFilterPtr> result{};

    if(options->mSkipBinaries)
    {
        auto filter = std::make_unique<BinaryMetaFilter>();
        result.push_back(std::move(filter));
    }

	if(options->mFilenameWildcard) {
		auto filter = std::make_unique<FilenameFilter>(*(options->mFilenameWildcard));
		result.push_back(std::move(filter));
	}

	return result;
}


} // namespace lg
