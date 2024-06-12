//
// Created by Lawrence Degoma on 5/17/24.
//

#ifndef HTML_WINDOW_H
#define HTML_WINDOW_H

#include "HtmlRenderer.h"
#include "HtmlDocument.h"
#include "HtmlParser.h"
#include "CssParser.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>

class HtmlWindow {
public:
    HtmlWindow(HtmlRenderer& renderer);
    void run(const std::string& htmlFilePath, const std::string& cssFilePath);

private:
    HtmlRenderer& renderer;

    std::string readFile(const std::string& filePath);
    void applyCSS(HtmlElement* element, const std::vector<CSSRule>& cssRules);
};

#endif // HTML_WINDOW_H
