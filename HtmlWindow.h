//
// Created by Lawrence Degoma on 5/17/24.
//

#ifndef HTML_WINDOW_H
#define HTML_WINDOW_H

#include "HtmlRenderer.h"
#include <string>
#include "HtmlDocument.h"
#include "HtmlParser.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class HtmlWindow {
private:
    HtmlRenderer& renderer;

public:
    HtmlWindow(HtmlRenderer& renderer);
    void run(const std::string& htmlFilePath);
};

#endif // HTML_WINDOW_H
