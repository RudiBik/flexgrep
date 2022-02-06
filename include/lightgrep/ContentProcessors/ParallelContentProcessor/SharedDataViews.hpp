#pragma once

#include <File.hpp>

#include <memory>
#include <mutex>

#include <iostream>

namespace lg {

struct SharedData
{
    bool bFinished{false};
    std::vector<FileSPtr> fileData;

    std::mutex structMutex;
};
using SharedDataSPtr = std::shared_ptr<SharedData>;


class WriterView
{
public:
    WriterView(SharedDataSPtr dataPtr) : mSharedData{dataPtr} {}

    void push_back(FileSPtr filePtr)
    {
        std::lock_guard<std::mutex> l{mSharedData->structMutex};
        mSharedData->fileData.push_back(filePtr);
    }

    void setFinished()
    {
        std::lock_guard<std::mutex> l{mSharedData->structMutex};
        mSharedData->bFinished = true;
    }

private:
    SharedDataSPtr mSharedData;
};



class BinaryReaderView
{
public:
    BinaryReaderView(SharedDataSPtr dataPtr, const int startPos) : mSharedData{dataPtr}, mNumAvailableFiles{0}, mProcessingIndex{startPos} {}

    bool isWorkAvailable()
    {
        std::lock_guard<std::mutex> l{mSharedData->structMutex};

        mNumAvailableFiles = mSharedData->fileData.size();

        return !mSharedData->bFinished || (mProcessingIndex < mNumAvailableFiles);
    }

    FileSPtr getNext()
    {
        if(mProcessingIndex < mNumAvailableFiles)
        {
            FileSPtr nextFile = mSharedData->fileData[mProcessingIndex];
            mProcessingIndex += 2;

            return nextFile;
        }
        else
        {
            return {};
        }
    }

    void print()
    {
        std::cout << mProcessingIndex << ", " << mNumAvailableFiles << std::endl;
    }

private:
    SharedDataSPtr mSharedData;

    int mNumAvailableFiles;
    int mProcessingIndex;
};


} // namespace lg
