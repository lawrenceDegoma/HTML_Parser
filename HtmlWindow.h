//
// Created by Lawrence Degoma on 5/17/24.
//

#ifndef HTML_PARSER_HTMLWINDOW_H
#define HTML_PARSER_HTMLWINDOW_H

#include "HtmlParser.h"
#include "HtmlRenderer.h"
#include "HtmlDocument.h"
#include <iostream>
#include <fstream>
#include <sstream>

class HtmlWindow {
private:
    HtmlRenderer& renderer;
public:
    HtmlWindow(HtmlRenderer& renderer);
    void run(const std::string& htmlFilePath);
};


#endif //HTML_PARSER_HTMLWINDOW_H
