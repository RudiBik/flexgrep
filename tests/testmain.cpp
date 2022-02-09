#include <gtest/gtest.h>

#include <Utilities/Options.hpp>

#include "PathFilter/FilenameMetaFilter.cpp"
#include "Wildcard.cpp"

using namespace lg;

int
main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
