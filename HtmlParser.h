//
// Created by Lawrence Degoma on 5/17/24.
//

#ifndef HTML_PARSER_H
#define HTML_PARSER_H

#include "HtmlElement.h"
#include <regex>
#include <string>

class HtmlParser {
private:
    std::string htmlContent;

public:
    HtmlParser(const std::string& content);
    HtmlElement* parse();
};

#endif // HTML_PARSER_H
