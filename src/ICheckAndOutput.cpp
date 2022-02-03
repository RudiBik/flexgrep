#include <ICheckAndOutput.hpp>

#include <SequentialCheckAndOutput.hpp>


namespace lg {


template <typename OutputIterator>
std::unique_ptr<ICheckAndOutput> ICheckAndOutput::create(OutputIterator oiter, std::unique_ptr<IContentFilter> secondLvlFilter, bool bParallel) {

	return std::make_unique<SequentialCheckAndOutput<OutputIterator>>(oiter, std::move(secondLvlFilter));
}


} // namespace lg
