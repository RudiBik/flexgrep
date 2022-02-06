#pragma once

#include <ContentProcessors/IContentProcessor.hpp>

#include <memory>


namespace lg {


template <typename OutputIterator>
class SequentialContentProcessor : public IContentProcessor {
public:
	SequentialContentProcessor(OutputIterator oiter, std::shared_ptr<IContentFilter> contentFilter); 
	virtual ~SequentialContentProcessor();

public:
	virtual void process(const FileSPtr filePtr);
	virtual void join();

private:
	OutputIterator mOutputIter;
	std::shared_ptr<IContentFilter> mContentFilter;
};



template <typename OutputIterator>
SequentialContentProcessor<OutputIterator>::SequentialContentProcessor(OutputIterator oiter, std::shared_ptr<IContentFilter> contentFilter)
    : mOutputIter{oiter}, mContentFilter{contentFilter} {

	// TODO: Check for validity of arguments
}


template <typename OutputIterator>
SequentialContentProcessor<OutputIterator>::~SequentialContentProcessor() {
}


template <typename OutputIterator>
void SequentialContentProcessor<OutputIterator>::process(const FileSPtr filePtr) {
	if(mContentFilter->check(filePtr)) {

		// Output
		(*mOutputIter) = filePtr->mMetaData.filePath.string() + std::string("\n");
		mOutputIter++;
	}
}


template <typename OutputIterator>
void SequentialContentProcessor<OutputIterator>::join() {
}


} // namespace lg
