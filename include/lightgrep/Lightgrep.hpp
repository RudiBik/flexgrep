#pragma once

#include <PathFilter/IMetaFilter.hpp>
#include <PathFilter/IContentFilter.hpp>
#include <ICheckAndOutput.hpp>
#include <Options.hpp>

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
	std::unique_ptr<ICheckAndOutput> mCheckAndOutput;

	// used to prevent recursive symlinks
	std::optional<std::filesystem::path> mCurrentSymlink;
};



template <typename OutputIterator>
Lightgrep::Lightgrep(std::shared_ptr<const Options> options, OutputIterator oiter) : mOptions{options}, mCurrentSymlink{} {
	mMetaFilters = IMetaFilter::createMetaFilters(options.get());

	// given to ICheckAndOutput::create after successful creation -> don't use it here
	// TODO: instead of passing true, extract skipBinaries from Options
	auto contentFilter = IContentFilter::createContentFilter(options->mRegexContent);
	if(!contentFilter) {
		// TODO: Throw exception
	}

	mCheckAndOutput = ICheckAndOutput::create(oiter, std::move(contentFilter), false);
	if(!mCheckAndOutput) {
		// TODO: Throw exception
	}
}


} // namespace lg
