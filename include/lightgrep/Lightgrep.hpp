#pragma once

#include <PathFilter/IMetaFilter.hpp>
#include <PathFilter/IContentFilter.hpp>
#include <ContentProcessors/IContentProcessor.hpp>
#include <Utilities/Options.hpp>

#include <memory>
#include <optional>


namespace lg {


class Lightgrep {
public:
	template <typename OutputIterator>
	Lightgrep(std::shared_ptr<const Options> options, OutputIterator oiter);

	void searchAndOutput();

private:
	bool passesMetaFilters(const File::Meta& metaData) const;

	void processDirectory(const std::filesystem::path &p);
	void processSymlink(const std::filesystem::path &p);
	void processRegular(const std::filesystem::path &p);

private:
	typedef std::unique_ptr<IMetaFilter> IMetaFilterPtr;

private:
	std::shared_ptr<const Options> mOptions;

	std::vector<IMetaFilterPtr> mMetaFilters;
	std::unique_ptr<IContentProcessor> mContentFilter;

	// used to prevent following recursive symlinks
	std::optional<std::filesystem::path> mCurrentSymlink;
};



template <typename OutputIterator>
Lightgrep::Lightgrep(std::shared_ptr<const Options> options, OutputIterator oiter) : mOptions{options}, mCurrentSymlink{} {
	mMetaFilters = IMetaFilter::createMetaFilters(options.get());

	mContentFilter = IContentProcessor::create(oiter, mOptions);
	if(!mContentFilter) {
		// TODO: Throw exception
	}
}


} // namespace lg
