//
// Created by Lawrence Degoma on 5/17/24.
//

#ifndef HTML_RENDERER_H
#define HTML_RENDERER_H

#include "HtmlElement.h"
#include <SFML/Graphics.hpp>

class HtmlRenderer {
public:
    void render(sf::RenderWindow& window, HtmlElement* root);
    void renderElement(sf::RenderWindow& window, HtmlElement* element, float x, float y);
};

#endif // HTML_RENDERER_H
