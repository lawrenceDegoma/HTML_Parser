//
// Created by Lawrence Degoma on 5/20/24.
//

#ifndef HTML_PARSER_CSSPARSER_H
#define HTML_PARSER_CSSPARSER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <cctype>
#include <sstream>

struct CSSRule {
    std::string selector;
    std::unordered_map<std::string, std::string> properties;
    // Additional properties for margin and padding
    std::string margin;
    std::string padding;
    std::string borderWidth;
    std::string borderStyle;
    std::string borderColor;
};

class CSSParser {
public:
    CSSParser(const std::string& cssContent);
    std::vector<CSSRule> parse();

private:
    std::string cssContent;
    size_t pos;
    void skipWhitespaceAndComments();
    void skipComment();
    std::string parseSelector();
    std::string parseIdentifier();
    std::string parsePropertyValue();
    CSSRule parseRule();
    bool startsWith(const std::string& prefix) const;
    std::vector<std::string> splitBySpaces(const std::string& str); // New helper function
};

#endif //HTML_PARSER_CSSPARSER_H
