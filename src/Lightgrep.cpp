#include <Lightgrep.hpp>
#include <Utilities.hpp>

#include <filesystem>
#include <iostream>

namespace lg {

using namespace std;
using namespace std::filesystem;


void Lightgrep::searchAndOutput() {
	processDirectory(mOptions->mRootPath);

	mCheckAndOutput->join();
}


void Lightgrep::processDirectory(const path &p) {
	// TODO: check if it is excluded
	


	for(const auto &p : directory_iterator(p)) {
	
		if(p.is_symlink()) {
			processSymlink(p);

		} else if(p.is_directory()) {
			// when following a symlink, don't enter the root directory reccursively
			if(mCurrentSymlink && equivalent(p, mOptions->mRootPath))
				continue;

			processDirectory(p);

		} else if(p.is_regular_file()) {
			processRegular(p);
			
		} else {
			// TODO: Throw an error
		}
	}
}


void Lightgrep::processRegular(const path &p) {
	if(passedFirstLvlFilter(p)) {
		mCheckAndOutput->process(p);
	}
}


void Lightgrep::processSymlink(const path &p) {
	path linkedFile = read_symlink(p);
	
	if(exists(linkedFile)) {
		// dont't follow symlinks that point to a file under the root search directory
		if(pathContainsFile(mOptions->mRootPath, linkedFile)) {
			// TODO: Log that this file is skipped
			return;
		}

		

		if(is_regular_file(linkedFile)) {
			processRegular(linkedFile);

		} else if(is_directory(linkedFile)) {

			// follow symbolic links only once
			if(mCurrentSymlink)
				return;

			mCurrentSymlink = p;
			processDirectory(linkedFile);
			mCurrentSymlink = std::nullopt;
		}
	}
}


bool Lightgrep::passedFirstLvlFilter(const path &p) const {
	for(const auto &filter : mFirstLvlFilters) {
		if(!filter->check(p))
			return false;
	}

	return true;
}

} // namespace lg
