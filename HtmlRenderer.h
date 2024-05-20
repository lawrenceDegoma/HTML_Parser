//
// Created by Lawrence Degoma on 5/17/24.
//

#ifndef HTML_RENDERER_H
#define HTML_RENDERER_H

#include "HtmlElement.h"
#include <SFML/Graphics.hpp>

class HtmlRenderer {
public:
    HtmlRenderer();
    void render(sf::RenderWindow& window, HtmlElement* root);
private:
    sf::Font font;

    void renderElement(sf::RenderWindow& window, HtmlElement* element, float& x, float& y);
    void renderText(sf::RenderWindow& window, const std::string& text, float x, float y, unsigned int size, const sf::Color& color);
};

#endif // HTML_RENDERER_H
