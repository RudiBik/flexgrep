#include "PathFilter/ContentRegexFilter.hpp"

#include <ICheckAndOutput.hpp>
#include <Utilities.hpp>

#include <fstream>
#include <strstream>
#include <string>
#include <iostream>

namespace lg {


ContentRegexFilter::ContentRegexFilter(const std::regex &contentRegex, bool skipBinaries) : mContentRegex(contentRegex), mSkipBinaries(skipBinaries) {
	// TODO: Log a warning on suspicious regex
}



bool ContentRegexFilter::check(const std::shared_ptr<File> pFile) const {


	// check if the file is binary and skip it in this case
	if(mSkipBinaries) {
		// gcount returns the number of bytes read
		if(isBinaryFile(&pFile->mData[0], pFile->mData.size()))
			return false;
	}

    std::stringstream reader(std::string(pFile->mData.begin(), pFile->mData.end()));
    
	std::smatch match;
	std::string line;
	while(std::getline(reader, line)) {
		if(std::regex_search(line, match, mContentRegex)) {
			printSearchResult(match);
			return true;
		}
	}

	return false;
}



void ContentRegexFilter::printSearchResult(const std::smatch &match) const {
	std::cout << "\n";
	std::cout << "\033[90m" << match.prefix() << "\033[0m";
	for(size_t i=0; i<match.size(); ++i) {
		std::cout << "\033[1;31m" << match[i] << "\033[0m";
	}
	std::cout << "\033[90m" << match.suffix() << "\033[0m\n";
}




} // namespace lg
