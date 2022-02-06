#include "Utilities/Options.hpp"

namespace lg {

using namespace std::filesystem;



Options::Options(const std::string &rootPath, const std::string &filenameWildcard, const std::string &regexContent, bool skipBinaries) {
	if(!exists(rootPath) || !is_directory(rootPath)) {
		// TOTO Output error message and quit
	}
	mRootPath = rootPath;

	// TOTO: check if filenameWildcard is valid
	if(!filenameWildcard.empty())
		mFilenameWildcard = std::make_unique<Wildcard>(filenameWildcard);
	else
		mFilenameWildcard = nullptr;


	// TODO: check if regexContent is valid
	mRegexContent = std::regex(regexContent);

    mSkipBinaries = skipBinaries;
}



} // namespace lg
