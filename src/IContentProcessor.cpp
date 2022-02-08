#include <ContentProcessors/IContentProcessor.hpp>

// filters
#include <PathFilter/ContentRegexFilter.hpp>

// processors
#include <ContentProcessors/SequentialContentProcessor.hpp>
#include <ContentProcessors/ParallelContentProcessor/ParallelContentProcessor.hpp>


namespace lg {


template <typename OutputIterator>
std::unique_ptr<IContentProcessor> IContentProcessor::create(OutputIterator oiter, std::shared_ptr<const Options> opt) {

    // Create the content filter

    // if regex filter
	auto contentFilter = std::make_shared<ContentRegexFilter>(opt->mRegexContent);
	if(!contentFilter) {
		// TODO: Throw exception
	}

    // Create the processor (single- or multi-threaded)
    if(opt->mParallelContentFiltering)
    {
        return std::make_unique<ParallelContentProcessor<OutputIterator>>(oiter, contentFilter);
    }
    else
    {
        return std::make_unique<SequentialContentProcessor<OutputIterator>>(oiter, contentFilter);
    }
}


} // namespace lg
