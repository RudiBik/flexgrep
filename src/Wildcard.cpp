#include <Utilities/Wildcard.hpp>

#include <algorithm>
#include <stdexcept>


namespace lg {

using namespace std;


const string Wildcard::TOKENS("*?");


Wildcard::Wildcard() : mPattern("") {}


Wildcard::Wildcard(const string &pattern) : mPattern(pattern) {
	if(mPattern.empty())
		throw invalid_argument("Empty pattern is not valid");

	auto pos = pattern.find("**");
	if(pos != string::npos)
		throw invalid_argument("Multiple adjacent stars are not allowed in pattern: " + mPattern);
}


bool Wildcard::match(const string &text) const {
	if(mPattern.empty())
		return false;

	auto sp = mPattern.begin();
	auto ep = mPattern.end();
	auto st = text.begin();
	auto et = text.end();

	return subMatch(sp, ep, st, et);
}


bool Wildcard::subMatch(StringIterator sp, StringIterator ep, StringIterator st, StringIterator et) const {
	// find first occurance of * or ?
	auto tokenPos = find_first_of(sp, ep, TOKENS.begin(), TOKENS.end());
	int tokenDistance = tokenPos - sp;

	// no token found
	if(tokenPos == ep)
		return equal(sp, ep, st, et);
	
	// the pattern before the token has to match
	if(!equal(sp, tokenPos, st, st + tokenDistance))
		return false;



	// skip the token and everything before in the pattern and text
	sp = tokenPos + 1;
	st = st + tokenDistance;

	// skip the ? in the text and repeat everything
	if((*tokenPos) == '?') {

		return subMatch(sp, ep, st + 1, et);

	// subMatchStar handles all cases where a star before the upcoming pattern is present
	} else if((*tokenPos) == '*') {

		return subMatchStar(sp, ep, st, et);

	} else {
		throw logic_error("The following token isn't handled by Wildcard::subMatch: " + to_string((*tokenPos)));
	}



	return false;
}


bool Wildcard::subMatchStar(StringIterator sp, StringIterator ep, StringIterator st, StringIterator et) const {
	// find next occurance of * or ?
	auto tokenPos = find_first_of(sp, ep, TOKENS.begin(), TOKENS.end());
	int tokenDistance = tokenPos - sp;

	string text(st, et);
	string pattern_before(sp, tokenPos);

	// nothing is coming after * 	-> always a match
	if(tokenPos == ep && pattern_before.empty())
		return true;

	
	// the pattern before the new token has to exist in the text	
	auto posPatternBeforeInText = text.find(pattern_before);
	if(posPatternBeforeInText == string::npos)
		return false;
	


	// skip the token and everything before in the pattern and text
	sp = tokenPos + 1;
	st = st + posPatternBeforeInText + pattern_before.size();

	
	// no more tokens
	if(tokenPos == ep) {
		// only return true if the pattern is at the end of the text
		if(st == et)
			return true;
		else
			return false;
	} else if((*tokenPos) == '?') {
		// special case: *?
		if(pattern_before.empty()) {
			return subMatchStar(sp, ep, st + 1, et);
		}

		// +1 to jump over the character which represents the ?
		return subMatch(sp, ep, st + 1, et);

	} else if((*tokenPos) == '*') {

		return subMatchStar(sp, ep, st, et);

	} else {
		throw logic_error("The following token isn't handled by Wildcard::subMatchStar: " + to_string((*tokenPos)));
	}



	return false;
}


} // namespace lg
