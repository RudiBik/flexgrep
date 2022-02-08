#include <File.hpp>

#include <Utilities/Utilities.hpp>


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

    const int bufferSize = std::min(static_cast<int>(fileSize), 1024);
    char buffer[bufferSize];
    filestream.read(buffer, bufferSize);
    mMetaData.binary = isBinaryFile(buffer, bufferSize);
    mMetaData.filePath = p;
    mMetaData.fileSize = fileSize;
}


bool File::loadContent()
{
    std::ifstream filestream(mMetaData.filePath, std::ios::in | std::ios::binary);
    if(!filestream.is_open()) {
        return false;
    }

    mData.resize(mMetaData.fileSize);
    filestream.read(&mData[0], mMetaData.fileSize);

    return true;
}

void File::unloadContent()
{
    mData.clear();
}


} // namespace lg
