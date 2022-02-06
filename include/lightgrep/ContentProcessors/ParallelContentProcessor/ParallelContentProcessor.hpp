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

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    readerView->print();
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

    std::unique_ptr<std::thread> mThread;
    std::unique_ptr<std::thread> mThread2;
};


template <typename OutputIterator>
ParallelContentProcessor<OutputIterator>::ParallelContentProcessor(OutputIterator oiter, std::shared_ptr<IContentFilter> contentFilter)
{
    SharedDataSPtr sharedDataPtr = std::make_shared<SharedData>();
    mSharedDataWriter = std::make_unique<WriterView>(sharedDataPtr);

    mThread = std::make_unique<std::thread>(&threadWorker<OutputIterator>, oiter, contentFilter, std::make_unique<BinaryReaderView>(sharedDataPtr, 0));
    mThread2 = std::make_unique<std::thread>(&threadWorker<OutputIterator>, oiter, contentFilter, std::make_unique<BinaryReaderView>(sharedDataPtr, 1));
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
    mThread->join();
    mThread2->join();
}


} // namespace lg
