#include "HtmlRenderer.h"
#include <SFML/Graphics.hpp>
#include <iostream>

HtmlRenderer::HtmlRenderer() {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Could not load font" << std::endl;
    }
}

void HtmlRenderer::render(sf::RenderWindow& window, HtmlElement* root) {
    if (root) {
        float x = 10.0f;
        float y = 10.0f;
        renderElement(window, root, x, y);
    }
}

void HtmlRenderer::renderElement(sf::RenderWindow& window, HtmlElement* element, float& x, float& y) {
    if (!element) return;

    std::string tagName = element->getTagName();
    if (tagName == "h1") {
        renderText(window, element->getText(), x, y, 30, sf::Color::Black);
        y += 40;
    } else if (tagName == "p") {
        renderText(window, element->getText(), x, y, 20, sf::Color::Black);
        y += 30;
    } else if (tagName == "div") {
        float childX = x;
        float childY = y;
        for (HtmlElement* child : element->getChildren()) {
            renderElement(window, child, childX, childY);
            childY += 10;
        }
        y = childY + 10;
    } else {
        for (HtmlElement* child : element->getChildren()) {
            renderElement(window, child, x, y);
        }
    }
}

void HtmlRenderer::renderText(sf::RenderWindow& window, const std::string& text, float x, float y, unsigned int size, const sf::Color& color) {
    sf::Text sfText;
    sfText.setFont(font);
    sfText.setString(text);
    sfText.setCharacterSize(size);
    sfText.setFillColor(color);
    sfText.setPosition(x, y);
    window.draw(sfText);
}
