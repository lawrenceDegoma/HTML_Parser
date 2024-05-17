//
// Created by Lawrence Degoma on 5/17/24.
//

#ifndef HTML_PARSER_HTMLRENDERER_H
#define HTML_PARSER_HTMLRENDERER_H

#include <SFML/Graphics.hpp>
#include "HtmlElement.h"

class HtmlRenderer {
private:
    void renderElement(sf::RenderWindow& window, HtmlElement* element, float x, float y);
public:
    HtmlRenderer();
    void render(sf::RenderWindow& window, HtmlElement* root);
};


#endif //HTML_PARSER_HTMLRENDERER_H
