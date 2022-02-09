#include <ContentProcessors/ParallelContentProcessor/SharedDataViews.hpp>

namespace lg {

WriterView::WriterView(SharedDataSPtr dataPtr)
  : mSharedData{ dataPtr }
{}

void
WriterView::push_back(FileSPtr filePtr)
{
    std::lock_guard<std::mutex> l{ mSharedData->structMutex };
    mSharedData->fileData.push_back(filePtr);
}

void
WriterView::setFinished()
{
    std::lock_guard<std::mutex> l{ mSharedData->structMutex };
    mSharedData->bFinished = true;
}

//!===============================================

BinaryReaderView::BinaryReaderView(SharedDataSPtr dataPtr,
                                   const int numThreads,
                                   const int startPos)
  : mSharedData{ dataPtr }
  , mNumAvailableFiles{ 0 }
  , mProcessingIndex{ startPos }
  , mNumOverallThreads{ numThreads }
{}

bool
BinaryReaderView::isWorkAvailable()
{
    std::lock_guard<std::mutex> l{ mSharedData->structMutex };

    mNumAvailableFiles = mSharedData->fileData.size();

    return !mSharedData->bFinished || (mProcessingIndex < mNumAvailableFiles);
}

FileSPtr
BinaryReaderView::getNext()
{
    if (mProcessingIndex < mNumAvailableFiles) {
        FileSPtr nextFile = mSharedData->fileData[mProcessingIndex];
        mProcessingIndex += mNumOverallThreads;

        return nextFile;
    } else {
        return {};
    }
}

} // namespace lg
