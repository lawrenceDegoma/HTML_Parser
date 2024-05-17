//
// Created by Lawrence Degoma on 5/17/24.
//

#ifndef HTML_PARSER_HTMLPARSER_H
#define HTML_PARSER_HTMLPARSER_H

#include <string>
#include <cctype>
#include <iostream>
#include "HtmlElement.h"

class HtmlParser {
private:
    std::string htmlContent;
    size_t currentPosition;

    HtmlElement* parseElement();
    std::string parseTagName();
    std::string parseText();
    void skipWhiteSpace();
public:
    HtmlParser(const std::string& htmlContent);
    HtmlElement* parse();
};


#endif //HTML_PARSER_HTMLPARSER_H
