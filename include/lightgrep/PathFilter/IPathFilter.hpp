#pragma once

#include <Options.hpp>

#include <filesystem>
#include <memory>
#include <regex>
#include <vector>


namespace lg {


class IPathFilter {
public:
	typedef std::unique_ptr<IPathFilter> IPathFilterPtr;

public:
	virtual ~IPathFilter() {}

public:
	virtual bool check(const std::filesystem::path &path) const=0;

public:
	static std::vector<IPathFilterPtr> createFirstLevelFilter(const Options *options);
};


} // namespace lg
