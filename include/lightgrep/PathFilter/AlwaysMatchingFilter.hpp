#pragma once

#include <filesystem>

#include <PathFilter/IPathFilter.hpp>


namespace lg {


class AlwaysMatchingFilter : public IPathFilter {
public:
	AlwaysMatchingFilter() {}

public:
	virtual bool check(const std::filesystem::path &path) const {
		return true;
	}
};


} // namespace lg
