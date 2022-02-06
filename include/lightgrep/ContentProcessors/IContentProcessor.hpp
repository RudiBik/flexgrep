#pragma once

#include <PathFilter/IContentFilter.hpp>
#include <Utilities/Options.hpp>

#include <memory>
#include <iostream>


namespace lg {


//!================================================
//! Interface for filtering and outputiting files to an output_iterator
//!------------------------------------------------
class IContentProcessor {
public:
	virtual ~IContentProcessor() {}

public:
	virtual void process(const FileSPtr filePtr)=0;
	virtual void join()=0;

public:
	template <typename OutputIterator>
	static std::unique_ptr<IContentProcessor> create(OutputIterator oiter, std::shared_ptr<const Options> opt);
};


} // namespace lg
