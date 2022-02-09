#pragma once

#include <ICheckAndOutput.hpp>
#include <PathFilter/IPathFilter.hpp>

#include <memory>


namespace lg {


template <typename OutputIterator>
class SequentialCheckAndOutput : public ICheckAndOutput {
public:
	SequentialCheckAndOutput(OutputIterator oiter, std::unique_ptr<IPathFilter> secondLvlFilter); 
	virtual ~SequentialCheckAndOutput();

public:
	virtual void process(const std::filesystem::path &path);
	virtual void join();

private:
	OutputIterator mOutputIter;
	std::unique_ptr<IPathFilter> mSecondLvlFilter;
};



template <typename OutputIterator>
SequentialCheckAndOutput<OutputIterator>::SequentialCheckAndOutput(OutputIterator oiter, std::unique_ptr<IPathFilter> secondLvlFilter)
    : mOutputIter{oiter}, mSecondLvlFilter{std::move(secondLvlFilter)} {

	// TODO: Check for validity of arguments
}


template <typename OutputIterator>
SequentialCheckAndOutput<OutputIterator>::~SequentialCheckAndOutput() {
}


template <typename OutputIterator>
void SequentialCheckAndOutput<OutputIterator>::process(const std::filesystem::path &path) {
	if(mSecondLvlFilter->check(path)) {

		// Output
		(*mOutputIter) = path.string() + std::string("\n");
		mOutputIter++;
	}
}


template <typename OutputIterator>
void SequentialCheckAndOutput<OutputIterator>::join() {
}


} // namespace lg
