#include <Utilities.hpp>

#include <algorithm>
#include <string>
#include <vector>


namespace lg {

using namespace std::filesystem;
using namespace std;



bool pathContainsFile(const path &rootPath, const path &file) {
	string fileString = file.string();
	string pathFilenameString = rootPath.filename().string();

	std::vector<size_t> positions;
	size_t pos = fileString.find(pathFilenameString, 0);
	while(pos != string::npos) {
		positions.push_back(pos);
		pos = fileString.find(pathFilenameString, pos + 1);
	}

	for(const auto pos : positions) {
		path subPath(fileString.begin(), fileString.begin() + pos + pathFilenameString.size());

		if(exists(subPath) && equivalent(rootPath, subPath))
			return true;
	}


	return false;
}


} // namespace lg
