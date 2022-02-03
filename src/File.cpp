#include <File.hpp>


namespace lg {



File::File(const std::filesystem::path& p) : mPath{p}
{
    std::ifstream filestream(p, std::ios::in | std::ios::binary);
    if(!filestream.is_open()) {
        // TODO: Throw an exception
        return;
    }

    filestream.seekg(0, std::ios::end);
    std::streampos fileSize = filestream.tellg();
    filestream.seekg(0, std::ios::beg);

    mData.resize(fileSize);
    filestream.read(&mData[0], fileSize);
}



} // namespace lg
