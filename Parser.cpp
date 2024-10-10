#include "Parser.h"

// https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
std::vector<std::string> Parser::Parse(const std::string& InString, const std::string& InSeparator) const
{
    std::string str(InString);
    std::string separator(InSeparator);
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = str.find(separator)) != std::string::npos)
    {
        token = str.substr(0, pos);
        tokens.push_back(token);
        str.erase(0, pos + separator.length());
    }
    tokens.push_back(str);

    return tokens;
}