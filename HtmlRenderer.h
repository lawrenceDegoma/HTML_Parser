//
// Created by Lawrence Degoma on 5/17/24.
//

#ifndef HTML_RENDERER_H
#define HTML_RENDERER_H

#include "HtmlElement.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "CssParser.h"

class HtmlRenderer {
public:
    HtmlRenderer();

    void render(sf::RenderWindow& window, HtmlElement* root, const std::vector<CSSRule>& cssRules);

private:
    sf::Font font;

    void applyStyles(HtmlElement* element, const std::vector<CSSRule>& cssRules);
    bool matchesSelector(HtmlElement* element, const std::string& selector);
    void renderElement(sf::RenderWindow& window, HtmlElement* element, float& x, float& y);
    void renderText(sf::RenderWindow& window, const std::string& text, float x, float y, unsigned int size, const sf::Color& color);
    sf::Color parseColor(const std::string& colorStr);
    unsigned int parseFontSize(const std::string& fontSizeStr);
};

#endif // HTML_RENDERER_H
