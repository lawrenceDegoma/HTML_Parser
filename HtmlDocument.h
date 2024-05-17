//
// Created by Lawrence Degoma on 5/17/24.
//

#ifndef HTML_PARSER_HTMLDOCUMENT_H
#define HTML_PARSER_HTMLDOCUMENT_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class HtmlDocument {
public:
    static std::string readHtmlFile(const std::string& filePath);
};


#endif //HTML_PARSER_HTMLDOCUMENT_H
