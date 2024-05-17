//
// Created by Lawrence Degoma on 5/17/24.
//

#include "HtmlRenderer.h"

HtmlRenderer::HtmlRenderer() {}

void HtmlRenderer::render(sf::RenderWindow& window, HtmlElement* root) {
    renderElement(window, root, 10.0f, 10.0f);
}

void HtmlRenderer::renderElement(sf::RenderWindow& window, HtmlElement* element, float x, float y) {
    if (element->getTagName() == "h1") {
        sf::Text text;
        sf::Font font;
        font.loadFromFile("arial.ttf");
        text.setFont(font);
        text.setString(element->getText());
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Black);
        text.setPosition(x, y);
        window.draw(text);
    } else if (element->getTagName() == "p") {
        sf::Text text;
        sf::Font font;
        font.loadFromFile("arial.ttf");
        text.setFont(font);
        text.setString(element->getText());
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Black);
        text.setPosition(x, y + 40);
        window.draw(text);
    }

    float childX = x + 20;
    float childY = y + 60;

    for (HtmlElement* child : element->getChildren()) {
        renderElement(window, child, childX, childY);
        childY += 40;
    }
}