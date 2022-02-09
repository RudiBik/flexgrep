#include <gtest/gtest.h>
#include <PathFilter/FilenameFilter.hpp>
#include <Wildcard.hpp>
#include <Options.hpp>

#include <regex>

namespace lg {

using namespace std;



const string filenameWildcard = "*test1?3";


TEST(FilenameFilterTests, equalityTestTrue) {
	Wildcard wc(filenameWildcard);
	auto opt = make_shared<Options>("", filenameWildcard, "");
	FilenameFilter filter(*(opt->mFilenameWildcard));

	EXPECT_EQ(filter.check("test123"), wc.match("test123"));
	EXPECT_EQ(filter.check("***test123"), wc.match("***test123"));
	EXPECT_EQ(filter.check("*test1?3"), wc.match("*test1?3"));
}

TEST(FilenameFilterTests, inequalityTestFalse) {
	Wildcard wc(filenameWildcard);
	auto opt = make_shared<Options>("", filenameWildcard, "");
	FilenameFilter filter(*(opt->mFilenameWildcard));

	EXPECT_EQ(filter.check("test12"), wc.match("test12"));
	EXPECT_EQ(filter.check("***tst123"), wc.match("***tst123"));
	EXPECT_EQ(filter.check("*test13"), wc.match("*test13"));
	EXPECT_EQ(filter.check("*test134"), wc.match("*test134"));
}



} // namespace lg 
