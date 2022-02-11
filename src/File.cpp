#include <File.hpp>
#include <Utilities/Utilities.hpp>


namespace lg {

File::File(const std::filesystem::path& p)
{
    std::ifstream filestream(p, std::ios::in | std::ios::binary);
    if (!filestream.is_open()) {
        // TODO: Throw an exception
        return;
    }

    filestream.seekg(0, std::ios::end);
    std::streampos fileSize = filestream.tellg();
    filestream.seekg(0, std::ios::beg);

    mMetaData.filePath = p;
    mMetaData.fileSize = fileSize;
    mMetaData.binary   = false;

    const size_t bufferSize = std::min(mMetaData.fileSize, static_cast<size_t>(8192));
    if (bufferSize > 0) {
        std::vector<char> buffer(bufferSize);
        filestream.read(&buffer[0], bufferSize);
        mMetaData.binary =
          isBinaryFile(&buffer[0], bufferSize, fileSize);
    }
}

bool
File::loadContent()
{
    std::ifstream filestream(mMetaData.filePath,
                             std::ios::in | std::ios::binary);
    if (!filestream.is_open()) {
        return false;
    }

    mData.resize(mMetaData.fileSize);
    if (mMetaData.fileSize > 0) {
        filestream.read(&mData[0], mMetaData.fileSize);
    }

    return true;
}

void
File::unloadContent()
{
    mData.clear();
}

} // namespace lg
