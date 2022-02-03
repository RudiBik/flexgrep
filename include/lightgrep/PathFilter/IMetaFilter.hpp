#pragma once

#include <File.hpp>
#include <Options.hpp>

#include <filesystem>
#include <memory>
#include <regex>
#include <vector>


namespace lg {


class IMetaFilter {
public:
	typedef std::unique_ptr<IMetaFilter> IMetaFilterPtr;

public:
	virtual ~IMetaFilter() {}

public:
	virtual bool check(const File::Meta& metaData) const=0;

public:
	static std::vector<IMetaFilterPtr> createMetaFilters(const Options *options);
};


} // namespace lg
