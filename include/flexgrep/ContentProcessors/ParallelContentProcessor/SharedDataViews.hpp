#pragma once

#include <File.hpp>
#include <iostream>
#include <memory>
#include <mutex>

namespace lg {

struct SharedData
{
    bool bFinished{ false };
    std::vector<FileSPtr> fileData;

    std::mutex structMutex;
};
using SharedDataSPtr = std::shared_ptr<SharedData>;

//!===============================================
//! \brief A view on the SharedData structure only permitting pushing new
//!        elements to the container while locking the mutex
//!-----------------------------------------------
class WriterView
{
  public:
    WriterView(SharedDataSPtr dataPtr);

    void push_back(FileSPtr filePtr);
    void setFinished();

  private:
    SharedDataSPtr mSharedData;
};

//!===============================================
//! \brief A view on the SharedData structure only reading already pushed data
//!        from the container. It will query the number of available unprocessed
//!        data blocks locking the mutex and then start processing them without
//!        blocking
//!
//! If will only process every X'th element where X is the number of threads
//! started. Each thread doing the same and starting at different positions
//!-----------------------------------------------
class BinaryReaderView
{
  public:
    BinaryReaderView(SharedDataSPtr dataPtr,
                     const int numThreads,
                     const int startPos);

    bool isWorkAvailable();
    FileSPtr getNext();

  private:
    SharedDataSPtr mSharedData;

    int mNumAvailableFiles;
    int mProcessingIndex;

    const int mNumOverallThreads;
};

} // namespace lg
