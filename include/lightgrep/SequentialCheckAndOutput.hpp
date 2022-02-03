#pragma once

#include <ICheckAndOutput.hpp>

#include <memory>


namespace lg {


template <typename OutputIterator>
class SequentialCheckAndOutput : public ICheckAndOutput {
public:
	SequentialCheckAndOutput(OutputIterator oiter, std::unique_ptr<IContentFilter> contentFilter); 
	virtual ~SequentialCheckAndOutput();

public:
	virtual void process(const std::shared_ptr<File> filePtr);
	virtual void join();

private:
	OutputIterator mOutputIter;
	std::unique_ptr<IContentFilter> mContentFilter;
};



template <typename OutputIterator>
SequentialCheckAndOutput<OutputIterator>::SequentialCheckAndOutput(OutputIterator oiter, std::unique_ptr<IContentFilter> contentFilter)
    : mOutputIter{oiter}, mContentFilter{std::move(contentFilter)} {

	// TODO: Check for validity of arguments
}


template <typename OutputIterator>
SequentialCheckAndOutput<OutputIterator>::~SequentialCheckAndOutput() {
}


template <typename OutputIterator>
void SequentialCheckAndOutput<OutputIterator>::process(const std::shared_ptr<File> filePtr) {
	if(mContentFilter->check(filePtr)) {

		// Output
		(*mOutputIter) = filePtr->mPath.string() + std::string("\n");
		mOutputIter++;
	}
}


template <typename OutputIterator>
void SequentialCheckAndOutput<OutputIterator>::join() {
}


} // namespace lg
