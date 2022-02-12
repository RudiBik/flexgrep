// Copyright (c) 2022, Rudi Bikschentajew
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#pragma once

#include <ContentProcessors/IContentProcessor.hpp>
#include <ContentProcessors/ParallelContentProcessor/SharedDataViews.hpp>
#include <chrono>
#include <memory>
#include <thread>

namespace lg {

template<typename OutputIterator>
void
threadWorker(OutputIterator oiter,
             std::shared_ptr<IContentFilter> contentFilter,
             std::unique_ptr<ReaderView> readerView)
{
    OutputIterator outputIterator = oiter;
    while (readerView->isWorkAvailable()) {
        while (auto pFile = readerView->getNext()) {
            if (contentFilter->check(pFile)) {
                (*outputIterator) =
                  pFile->mMetaData.filePath.string() + std::string("\n");
                ++outputIterator;
            }

            pFile->unloadContent();
        }
    }
}

//!===============================================
//! \brief Files matching the meta filter criterions are forwarded to this class
//!        and pushed to the shared data container via the WriterView on the
//!        main thread. On construction multiple side threads are spawned using
//!        the ReaderView to process the data
//!-----------------------------------------------
template<typename OutputIterator>
class ParallelContentProcessor : public IContentProcessor
{
  public:
    ParallelContentProcessor(OutputIterator oiter,
                             std::shared_ptr<IContentFilter> contentFilter);
    virtual ~ParallelContentProcessor();

  public:
    virtual void process(const FileSPtr filePtr);
    virtual void join();

  private:
    std::unique_ptr<WriterView> mSharedDataWriter;

    std::vector<std::unique_ptr<std::thread>> mThreads;
};

template<typename OutputIterator>
ParallelContentProcessor<OutputIterator>::ParallelContentProcessor(
  OutputIterator oiter,
  std::shared_ptr<IContentFilter> contentFilter)
{
    SharedDataSPtr sharedDataPtr = std::make_shared<SharedData>();
    mSharedDataWriter = std::make_unique<WriterView>(sharedDataPtr);

    const int numThreads =
      std::max(1U, std::thread::hardware_concurrency() - 1);
    for (int i = 0; i < numThreads; ++i) {
        mThreads.push_back(std::make_unique<std::thread>(
          &threadWorker<OutputIterator>,
          oiter,
          contentFilter,
          std::make_unique<ReaderView>(sharedDataPtr, numThreads, i)));
    }
}

template<typename OutputIterator>
ParallelContentProcessor<OutputIterator>::~ParallelContentProcessor()
{}

template<typename OutputIterator>
void
ParallelContentProcessor<OutputIterator>::process(const FileSPtr filePtr)
{
    mSharedDataWriter->push_back(filePtr);
}

template<typename OutputIterator>
void
ParallelContentProcessor<OutputIterator>::join()
{
    mSharedDataWriter->setFinished();
    for (const auto& t : mThreads) {
        t->join();
    }
}

} // namespace lg
