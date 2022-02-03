#include <File.hpp>

#include <Utilities.hpp>


namespace lg {



File::File(const std::filesystem::path& p)
{
    std::ifstream filestream(p, std::ios::in | std::ios::binary);
    if(!filestream.is_open()) {
        // TODO: Throw an exception
        return;
    }


    filestream.seekg(0, std::ios::end);
    std::streampos fileSize = filestream.tellg();
    filestream.seekg(0, std::ios::beg);

    char buffer[1024];
    filestream.read(buffer, 1024);
    mMetaData.binary = isBinaryFile(buffer, 1024);
    mMetaData.filePath = p;
    mMetaData.fileSize = fileSize;
}


bool File::loadContent()
{
    std::ifstream filestream(mMetaData.filePath, std::ios::in | std::ios::binary);
    if(!filestream.is_open()) {
        // TODO: Throw an exception
        return false;
    }

    mData.resize(mMetaData.fileSize);
    filestream.read(&mData[0], mMetaData.fileSize);

    return true;
}


} // namespace lg
