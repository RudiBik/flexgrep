#pragma once

#include <PathFilter/IContentFilter.hpp>

#include <memory>
#include <iostream>


namespace lg {


//!================================================
//! Interface for filtering and outputiting path objects to an output_iterator
//!------------------------------------------------
class ICheckAndOutput {
public:
	virtual ~ICheckAndOutput() {}

public:
	virtual void process(const std::shared_ptr<File> filePtr)=0;
	virtual void join()=0;

public:
	template <typename OutputIterator>
	static std::unique_ptr<ICheckAndOutput> create(OutputIterator oiter, std::unique_ptr<IContentFilter> contentFilter, bool bParallel);
};


} // namespace lg
