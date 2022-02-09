#pragma once

#include <PathFilter/IContentFilter.hpp>
#include <Utilities/Configuration.hpp>

#include <iostream>
#include <memory>

namespace lg {

//!================================================
//! \brief Interface for filtering and outputting files to an output_iterator
//!------------------------------------------------
class IContentProcessor
{
  public:
    virtual ~IContentProcessor() {}

  public:
    virtual void process(const FileSPtr filePtr) = 0;
    virtual void join() = 0;

  public:
    template<typename OutputIterator>
    static std::unique_ptr<IContentProcessor> create(
      OutputIterator oiter,
      std::shared_ptr<const Configuration> opt);
};

} // namespace lg
