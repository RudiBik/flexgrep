#include <gtest/gtest.h>

#include <PathFilter/FilenameMetaFilter.hpp>
#include <Utilities/Options.hpp>
#include <Utilities/Wildcard.hpp>
#include <regex>

namespace lg {

using namespace std;

const string filenameWildcard = "*test1?3";

TEST(FilenameMetaFilterTests, equalityTestTrue)
{
    Wildcard wc(filenameWildcard);
    auto opt = make_shared<Options>("", filenameWildcard, "", true, true);
    FilenameMetaFilter filter(*(opt->mFilenameWildcard));

    EXPECT_EQ(filter.check(File::Meta{ "test123", 0 }), wc.match("test123"));
    EXPECT_EQ(filter.check(File::Meta{ "***test123", 0 }),
              wc.match("***test123"));
    EXPECT_EQ(filter.check(File::Meta{ "*test1?3", 0 }), wc.match("*test1?3"));
}

TEST(FilenameMetaFilterTests, inequalityTestFalse)
{
    Wildcard wc(filenameWildcard);
    auto opt = make_shared<Options>("", filenameWildcard, "", true, true);
    FilenameMetaFilter filter(*(opt->mFilenameWildcard));

    EXPECT_EQ(filter.check(File::Meta{ "test12", 0 }), wc.match("test12"));
    EXPECT_EQ(filter.check(File::Meta{ "***tst123", 0 }),
              wc.match("***tst123"));
    EXPECT_EQ(filter.check(File::Meta{ "*test13", 0 }), wc.match("*test13"));
    EXPECT_EQ(filter.check(File::Meta{ "*test134", 0 }), wc.match("*test134"));
}

} // namespace lg
