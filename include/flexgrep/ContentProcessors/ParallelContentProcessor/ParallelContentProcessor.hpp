#pragma once

#include <ContentProcessors/IContentProcessor.hpp>

#include <ContentProcessors/ParallelContentProcessor/SharedDataViews.hpp>

#include <memory>
#include <chrono>
#include <thread>

namespace lg {



template <typename OutputIterator>
void threadWorker(OutputIterator oiter, std::shared_ptr<IContentFilter> contentFilter, std::unique_ptr<BinaryReaderView> readerView)
{
    OutputIterator outputIterator = oiter;
    while(readerView->isWorkAvailable())
    {
        while(auto pFile = readerView->getNext())
        {
            if(contentFilter->check(pFile))
            {
                (*outputIterator) = pFile->mMetaData.filePath.string() + std::string("\n");
                ++outputIterator;
            }

            pFile->unloadContent();
        }
    }
}



template <typename OutputIterator>
class ParallelContentProcessor : public IContentProcessor {
public:
	ParallelContentProcessor(OutputIterator oiter, std::shared_ptr<IContentFilter> contentFilter); 
	virtual ~ParallelContentProcessor();

public:
	virtual void process(const FileSPtr filePtr);
	virtual void join();

private:
    std::unique_ptr<WriterView> mSharedDataWriter;

    std::vector<std::unique_ptr<std::thread>> mThreads;
};


template <typename OutputIterator>
ParallelContentProcessor<OutputIterator>::ParallelContentProcessor(OutputIterator oiter, std::shared_ptr<IContentFilter> contentFilter)
{
    SharedDataSPtr sharedDataPtr = std::make_shared<SharedData>();
    mSharedDataWriter = std::make_unique<WriterView>(sharedDataPtr);

    const int numThreads = std::max(1U, std::thread::hardware_concurrency() - 1);
    for(int i = 0; i < numThreads; ++i)
    {
        mThreads.push_back(std::make_unique<std::thread>(&threadWorker<OutputIterator>, oiter, contentFilter, std::make_unique<BinaryReaderView>(sharedDataPtr, numThreads, i)));
    }
}


template <typename OutputIterator>
ParallelContentProcessor<OutputIterator>::~ParallelContentProcessor() {
}


template <typename OutputIterator>
void ParallelContentProcessor<OutputIterator>::process(const FileSPtr filePtr) {
    mSharedDataWriter->push_back(filePtr);
}


template <typename OutputIterator>
void ParallelContentProcessor<OutputIterator>::join() {
    mSharedDataWriter->setFinished();
    for(const auto& t : mThreads)
    {
        t->join();
    }
}


} // namespace lg