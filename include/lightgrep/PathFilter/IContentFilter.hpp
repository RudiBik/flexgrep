#pragma once

#include <File.hpp>

#include <memory>
#include <regex>


namespace lg {

class File;

class IContentFilter {
public:
	typedef std::unique_ptr<IContentFilter> IContentFilterPtr;

public:
	virtual ~IContentFilter() {}

public:
	virtual bool check(const std::shared_ptr<File> pFile) const=0;

public:
	static std::unique_ptr<IContentFilter> createContentFilter(const std::regex &contentRegex);
};


} // namespace lg
