#pragma once

#include <PathFilter/IContentFilter.hpp>
#include <Options.hpp>

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
	virtual void process(const FileSPtr filePtr)=0;
	virtual void join()=0;

public:
	template <typename OutputIterator>
	static std::unique_ptr<ICheckAndOutput> create(OutputIterator oiter, std::shared_ptr<const Options> opt);
};


} // namespace lg
