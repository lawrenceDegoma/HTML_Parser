//
// Created by Lawrence Degoma on 6/12/24.
//

#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font& font, std::string text) {
    button.setPosition(sf::Vector2f(x, y));
    button.setSize(sf::Vector2f(width, height));
    button.setFillColor(sf::Color::White);

    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(20);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setPosition(
            x + (width / 2.f) - (buttonText.getLocalBounds().width / 2.f),
            y + (height / 2.f) - (buttonText.getLocalBounds().height / 2.f)
    );
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(button);
    window.draw(buttonText);
}

bool Button::isClicked(sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            std::cout << "Button clicked!" << std::endl; // Debug statement
            if (onClickCallback) {
                onClickCallback();
            }
            return true;
        }
    }
    return false;
}

void Button::setOnClick(std::function<void()> onClick) {
    onClickCallback = onClick;
}

std::string Button::getText() const {
    return buttonText.getString();
}