#include <gtest/gtest.h>

#include <Options.hpp>
#include "Wildcard.cpp"
#include "PathFilter/FilenameMetaFilter.cpp"

using namespace lg;


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
