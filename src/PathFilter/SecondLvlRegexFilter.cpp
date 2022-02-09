#include "PathFilter/SecondLvlRegexFilter.hpp"

#include <fstream>
#include <string>
#include <iostream>

namespace lg {


SecondLvlRegexFilter::SecondLvlRegexFilter(const std::regex &contentRegex, bool skipBinaries) : mContentRegex(contentRegex), mSkipBinaries(skipBinaries) {
	// TODO: Log a warning on suspicious regex
}




bool SecondLvlRegexFilter::check(const std::filesystem::path &path) const {

	std::ifstream filestream(path);
	if(!filestream.is_open()) {
		// TODO: log a warning

		return false;
	}


	// check if the file is binary and skip it in this case
	if(mSkipBinaries) {
		char buffer[256];
		filestream.read(buffer, 256);

		// gcount returns the number of bytes read
		if(isBinaryFile(buffer, filestream.gcount()))
			return false;

		// clear eofbit when necessary and jump to beginning of file
		filestream.clear();
		filestream.seekg(0, std::fstream::beg);

	}


	std::smatch match;
	std::string line;
	while(std::getline(filestream, line)) {
		if(std::regex_search(line, match, mContentRegex)) {
			printSearchResult(match);
			return true;
		}
	}

	return false;
}


bool SecondLvlRegexFilter::isBinaryFile(const char* pBuffer, int size) const {
	if(size > 256)
		size = 256;

	unsigned char numberOfUnprintableCharacters = 0;
	for(int i=0; i < size; ++i) {
		if(!isprint(pBuffer[i]) && !iscntrl(pBuffer[i]))
			++numberOfUnprintableCharacters;
	}

	return (numberOfUnprintableCharacters > 5);
}


void SecondLvlRegexFilter::printSearchResult(const std::smatch &match) const {
	std::cout << "\n";
	std::cout << "\033[90m" << match.prefix() << "\033[0m";
	for(size_t i=0; i<match.size(); ++i) {
		std::cout << "\033[1;31m" << match[i] << "\033[0m";
	}
	std::cout << "\033[90m" << match.suffix() << "\033[0m\n";
}




} // namespace lg
