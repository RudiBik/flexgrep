// Copyright (c) 2022, Rudi Bikschentajew
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#pragma once

#include <ContentProcessors/IContentProcessor.hpp>

#include <memory>

namespace lg {

template<typename OutputIterator>
class SequentialContentProcessor : public IContentProcessor
{
  public:
    SequentialContentProcessor(OutputIterator oiter,
                               std::shared_ptr<IContentFilter> contentFilter);
    virtual ~SequentialContentProcessor();

  public:
    virtual void process(const FileSPtr filePtr);
    virtual void join();

  private:
    OutputIterator mOutputIter;
    std::shared_ptr<IContentFilter> mContentFilter;
};

template<typename OutputIterator>
SequentialContentProcessor<OutputIterator>::SequentialContentProcessor(
  OutputIterator oiter,
  std::shared_ptr<IContentFilter> contentFilter)
  : mOutputIter{ oiter }
  , mContentFilter{ contentFilter }
{}

template<typename OutputIterator>
SequentialContentProcessor<OutputIterator>::~SequentialContentProcessor()
{}

template<typename OutputIterator>
void
SequentialContentProcessor<OutputIterator>::process(const FileSPtr filePtr)
{
    if (mContentFilter->check(filePtr)) {
        (*mOutputIter) =
          filePtr->mMetaData.filePath.string() + std::string("\n");
        mOutputIter++;
    }
}

template<typename OutputIterator>
void
SequentialContentProcessor<OutputIterator>::join()
{}

} // namespace lg
