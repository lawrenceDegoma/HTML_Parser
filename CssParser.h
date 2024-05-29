//
// Created by Lawrence Degoma on 5/20/24.
//

#ifndef HTML_PARSER_CSSPARSER_H
#define HTML_PARSER_CSSPARSER_H

#include <string>
#include <unordered_map>
#include <iostream>
#include <cctype>
#include <sstream>
#include <vector>

struct CSSRule {
    std::string selector;
    std::unordered_map<std::string, std::string> properties;
};

class CSSParser {
public:
    CSSParser(const std::string& cssContent);
    std::vector<CSSRule> parse();

private:
    std::string cssContent;
    size_t pos;

    CSSRule parseRule();
    void skipWhitespace();
    std::string parseIdentifier();
    std::string parsePropertyValue();
};

#endif //HTML_PARSER_CSSPARSER_H
