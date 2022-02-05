#include <ICheckAndOutput.hpp>

// filters
#include <PathFilter/ContentRegexFilter.hpp>

// processors
#include <SequentialCheckAndOutput.hpp>
#include <ParallelCheckAndOutput/ParallelCheckAndOutput.hpp>


namespace lg {


template <typename OutputIterator>
std::unique_ptr<ICheckAndOutput> ICheckAndOutput::create(OutputIterator oiter, std::shared_ptr<const Options> opt) {

    // Create the content filter

    // if regex filter
	auto contentFilter = std::make_shared<ContentRegexFilter>(opt->mRegexContent);
	if(!contentFilter) {
		// TODO: Throw exception
	}

    // Create the processor (single- or multi-threaded)

	return std::make_unique<ParallelCheckAndOutput<OutputIterator>>(oiter, contentFilter);
}


} // namespace lg
