#pragma once

#include <PathFilter/IPathFilter.hpp>

#include <filesystem>
#include <memory>


namespace lg {


//!================================================
//! Interface for filtering and outputiting path objects to an output_iterator
//!------------------------------------------------
class ICheckAndOutput {
public:
	virtual ~ICheckAndOutput() {}

public:
	virtual void process(const std::filesystem::path &path)=0;
	virtual void join()=0;

public:
	template <typename OutputIterator>
	static std::unique_ptr<ICheckAndOutput> create(OutputIterator oiter, std::unique_ptr<IPathFilter> secondLvlFilter, bool bParallel);
};


} // namespace lg
