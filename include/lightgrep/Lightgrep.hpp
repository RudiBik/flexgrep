#pragma once

#include <PathFilter/IPathFilter.hpp>
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
	bool passedFirstLvlFilter(const std::filesystem::path &p) const;

	void processDirectory(const std::filesystem::path &p);
	void processSymlink(const std::filesystem::path &p);
	void processRegular(const std::filesystem::path &p);

private:
	typedef std::unique_ptr<IPathFilter> IPathFilterPtr;

private:
	std::shared_ptr<const Options> mOptions;

	std::vector<IPathFilterPtr> mFirstLvlFilters;
	std::unique_ptr<ICheckAndOutput> mCheckAndOutput;

	// used to prevent recursive symlinks
	std::optional<std::filesystem::path> mCurrentSymlink;
};



template <typename OutputIterator>
Lightgrep::Lightgrep(std::shared_ptr<const Options> options, OutputIterator oiter) : mOptions{options}, mCurrentSymlink{} {
	mFirstLvlFilters = IPathFilter::createFirstLevelFilter(options.get());

	// given to ICheckAndOutput::create after successful creation -> don't use it here
	// TODO: instead of passing true, extract skipBinaries from Options
	auto secondLvlFilter = IPathFilter::createSecondLevelFilter(options->mRegexContent, true);
	if(!secondLvlFilter) {
		// TODO: Throw exception
	}

	mCheckAndOutput = ICheckAndOutput::create(oiter, std::move(secondLvlFilter), false);
	if(!mCheckAndOutput) {
		// TODO: Throw exception
	}
}


} // namespace lg
