#pragma once

#include <vector>
#include <string>

class Parser
{
public:
	std::vector<std::string> Parse(const std::string& InString, const std::string& InSeparator) const;
};