#include <gtest/gtest.h>
#include <Utilities/Wildcard.hpp>

namespace lg {



TEST(WildcardTests, emptyConstructorAlwaysNotMatching) {
	Wildcard wc{};

	EXPECT_FALSE(wc.match(""));
	EXPECT_FALSE(wc.match("123"));
	EXPECT_FALSE(wc.match("*?abc123"));
}

TEST(WildcardTests, emptyStringConstructor) {
	EXPECT_THROW(Wildcard wc(""), std::invalid_argument);
}

TEST(WildcardTests, multipleStarsInConstructor) {
	EXPECT_THROW(Wildcard wc("**"), std::invalid_argument);
	EXPECT_THROW(Wildcard wc("**abcd"), std::invalid_argument);
	EXPECT_THROW(Wildcard wc("abcd**"), std::invalid_argument);
	EXPECT_THROW(Wildcard wc("ab******cd"), std::invalid_argument);
}

// BASIC TESTS
TEST(WildcardTests, basicStringMatches) {
	Wildcard wc("aasfj34r28ffhFHEJE");
	EXPECT_TRUE(wc.match("aasfj34r28ffhFHEJE"));
}

TEST(WildcardTests, basicStringNoMatch) {
	Wildcard wc("aasfj34r28ffhFHEJE");
	EXPECT_FALSE(wc.match("Aaasfj34r28ffhFHEJE"));
	EXPECT_FALSE(wc.match("aasfj34r28ffhFHEJEE"));
	EXPECT_FALSE(wc.match("aasfj34r28fffhFHEJE"));
	EXPECT_FALSE(wc.match("aasfj34r288ffhFHEJE"));
}

TEST(WildcardTests, questionmarkMatchesOneCharacter) {
	Wildcard wc("?");

	EXPECT_TRUE(wc.match("1"));
	EXPECT_TRUE(wc.match("f"));
	EXPECT_TRUE(wc.match("*"));
	EXPECT_TRUE(wc.match("."));
	EXPECT_TRUE(wc.match("?"));
}

TEST(WildcardTests, questionmarkFails) {
	Wildcard wc("?");

	EXPECT_FALSE(wc.match("11"));
	EXPECT_FALSE(wc.match("1*"));
	EXPECT_FALSE(wc.match("1fsdafasdl"));
	EXPECT_FALSE(wc.match(""));
}


TEST(WildcardTests, questionmarkMatch) {
	Wildcard wc("?aa?bb?cc");

	EXPECT_TRUE(wc.match("aaabbbccc"));
	EXPECT_TRUE(wc.match("caaabbacc"));
	EXPECT_TRUE(wc.match("xaa?bb*cc"));
}



TEST(WildcardTests, starMatchesEveryhing) {
	Wildcard wc("*");

	EXPECT_TRUE(wc.match(""));
	EXPECT_TRUE(wc.match("123w&/$§abcd"));
	EXPECT_TRUE(wc.match("*..234sjfl&/$§abcd"));
}

TEST(WildcardTests, basicStarMatchingAfter) {
	Wildcard wc("coca*");

	EXPECT_TRUE(wc.match("coca"));
	EXPECT_TRUE(wc.match("cocacola"));
	EXPECT_TRUE(wc.match("coca**??fsdkf1453"));
	EXPECT_FALSE(wc.match("fcocacola"));
}

TEST(WildcardTests, basicStarMatchingBefore) {
	Wildcard wc("*coca");

	EXPECT_TRUE(wc.match("coca"));
	EXPECT_TRUE(wc.match("colacoca"));
	EXPECT_TRUE(wc.match("**??11fsdkf1453coca"));
	EXPECT_FALSE(wc.match("cocacola"));
	EXPECT_FALSE(wc.match("***cocaa"));
}

TEST(WildcardTests, starMatchingMultiple) {
	Wildcard wc("*coca*fanta*sprite");

	EXPECT_TRUE(wc.match("cocafantasprite"));
	EXPECT_TRUE(wc.match("colacocafantasprite"));
	EXPECT_TRUE(wc.match("cocacolafantasprite"));
	EXPECT_TRUE(wc.match("*?1coca**colafantafskdf32?*sprite"));
}
TEST(WildcardTests, specialCaseStarQuestionmark) {
	Wildcard wc("*?cola");

	EXPECT_TRUE(wc.match("?cola"));
	EXPECT_TRUE(wc.match("****?cola"));
}

TEST(WildcardTests, specialCaseQuestionmarkStar) {
	Wildcard wc("?*cola");

	EXPECT_TRUE(wc.match("?cola"));
	EXPECT_TRUE(wc.match("?*****cola"));
	EXPECT_TRUE(wc.match("?*cola"));
}

TEST(WildcardTests, specialCaseManyQuestionmarks) {
	Wildcard wc("?????*col?a??");

	EXPECT_TRUE(wc.match("?????col?a??"));
	EXPECT_TRUE(wc.match("?????****col?a??"));
}

TEST(WildcardTests, specialCaseManyMixedStarQuestionmark) {
	Wildcard wc("*?*?*???*???*");

	EXPECT_TRUE(wc.match("????????"));
	EXPECT_TRUE(wc.match("**?*?***???*??*?"));
}


// TEST FIXTURE
class WildcardComplexFixture : public ::testing::Test {
public:
	WildcardComplexFixture() : wc("*abcd?fg*12345*xyz") {}
	virtual ~WildcardComplexFixture() {}

	void SetUp() {}
	void TearDown() {}
public:
	Wildcard wc;
};



TEST_F(WildcardComplexFixture, exactMatch) {
	EXPECT_TRUE(wc.match("abcdefg12345xyz"));
}

TEST_F(WildcardComplexFixture, repeatingSequenceInStar) {
	EXPECT_TRUE(wc.match("abcabcdefgfgfgfg1234512345xyz"));
}

TEST_F(WildcardComplexFixture, varyingFirstStar) {
	EXPECT_TRUE(wc.match("******abcdefg12345xyz"));
	EXPECT_TRUE(wc.match("sdlk54FDKCJjweiowabcdefg12345xyz"));
	EXPECT_TRUE(wc.match("mkdfj()4543jfFJabcdefg12345xyz"));
}

TEST_F(WildcardComplexFixture, varyingSecondStar) {
	EXPECT_TRUE(wc.match("abcdefg*****12345xyz"));
	EXPECT_TRUE(wc.match("abcdefgggggg12345xyz"));
	EXPECT_TRUE(wc.match("abcdefgFDske43353FL12345xyz"));
	EXPECT_TRUE(wc.match("abcdefgsdlf(fsdf)!!.,mn12345xyz"));
}


TEST_F(WildcardComplexFixture, varyingThirdStar) {
	EXPECT_TRUE(wc.match("abcdefg12345*****xyz"));
	EXPECT_TRUE(wc.match("abcdefg12345xxxxxyz"));
	EXPECT_TRUE(wc.match("abcdefg12345sdkfs32245FHxyz"));
	EXPECT_TRUE(wc.match("abcdefg12345jfd(5ff)-.fhgkxyz"));
}

TEST_F(WildcardComplexFixture, varyingAllThree) {
	EXPECT_TRUE(wc.match("****abcdefg*****12345*****xyz"));
	EXPECT_TRUE(wc.match("sf(f)s.abcdefg111(222)ll12345sfdhgh(frrere)xyz"));
}

TEST_F(WildcardComplexFixture, varyingQuestionMark) {
	EXPECT_TRUE(wc.match("abcdEfg12345xyz"));
	EXPECT_TRUE(wc.match("abcd!fg12345xyz"));
	EXPECT_TRUE(wc.match("abcd2fg12345xyz"));
	EXPECT_TRUE(wc.match("abcd.fg12345xyz"));
}




// CASES IN WHICH TESTS HAVE TO FAIL
TEST_F(WildcardComplexFixture, requiredCharacterMissing) {
	EXPECT_FALSE(wc.match("bcdefg12345xyz"));
	EXPECT_FALSE(wc.match("abcdefg1245xyz"));
	EXPECT_FALSE(wc.match("abcdefg12345"));
}

TEST_F(WildcardComplexFixture, questionmarkNotUsed) {
	EXPECT_FALSE(wc.match("abcdfg12345xyz"));
}




} // namespace lg
