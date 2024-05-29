#ifndef HTML_PARSER_HTMLPARSER_H
#define HTML_PARSER_HTMLPARSER_H

#include <string>
#include <cctype>
#include <iostream>
#include "HtmlElement.h"


class HtmlParser {
public:
    HtmlParser(const std::string& htmlContent);
    HtmlElement* parse();

private:
    std::string htmlContent;
    size_t pos;

    HtmlElement* parseElement();
    std::string parseTagName();
    std::string parseText();
    void skipWhitespace();
    bool startsWith(const std::string& prefix) const;
    void skipDoctype();
    void skipComment();
    void parseAttribute(HtmlElement* element);
};

#endif // HTML_PARSER_HTMLPARSER_H
