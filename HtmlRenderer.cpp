//
// Created by Lawrence Degoma on 5/17/24.
//

#include "HtmlRenderer.h"

void HtmlRenderer::render(sf::RenderWindow& window, HtmlElement* root) {
    renderElement(window, root, 10.0f, 10.0f);
}

void HtmlRenderer::renderElement(sf::RenderWindow& window, HtmlElement* element, float x, float y) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return;
    }

    sf::Text text;
    text.setFont(font);

    if (element->getTagName() == "h1") {
        text.setString(element->getText());
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Black);
        text.setPosition(x, y);
        window.draw(text);
        y += 40;
    } else if (element->getTagName() == "p") {
        text.setString(element->getText());
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Black);
        text.setPosition(x, y);
        window.draw(text);
        y += 30;
    }

    float childX = x + 20;
    float childY = y;

    for (HtmlElement* child : element->getChildren()) {
        renderElement(window, child, childX, childY);
        childY += 40;
    }
}