#pragma once

#include <string>

namespace lg {

//!===============================================
//! \brief A Wildcard is used to find a pattern in text.
//! 	   The pattern can contain normal text and the following tokens:
//!
//! '*': matches zero or more characters
//! '?': matches exactly one character
//!-----------------------------------------------
class Wildcard
{
  public:
    //!===============================================
    //! \brief Constructs a basic Wildcard which returns false on all text
    //!-----------------------------------------------
    Wildcard();

    //!===============================================
    //! \brief Constructs a Wildcard with the specified pattern.
    //!        Throws std::invalid_argument on invalid patterns
    //!
    //! \param[in] pattern  throws on empty pattern and patterns containing
    //! multiple *
    //!-----------------------------------------------
    Wildcard(const std::string& pattern);

    Wildcard(const Wildcard& rhs) = default;
    Wildcard& operator=(const Wildcard& rhs) = default;

  public:
    //!===============================================
    //! \brief Returns true if the text matches the pattern
    //!
    //! \param[in] text  string that is compared
    //! \return true if the text matches the internal pattern
    //!-----------------------------------------------
    bool match(const std::string& text) const;

  private:
    typedef std::string::const_iterator StringIterator;
    bool subMatch(StringIterator sp,
                  StringIterator ep,
                  StringIterator st,
                  StringIterator et) const;
    bool subMatchStar(StringIterator sp,
                      StringIterator ep,
                      StringIterator st,
                      StringIterator et) const;

    std::string mPattern;

    static const std::string TOKENS; // * and ?
};

} // namespace lg
