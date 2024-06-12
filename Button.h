//
// Created by Lawrence Degoma on 6/12/24.
//

#ifndef HTML_PARSER_BUTTON_H
#define HTML_PARSER_BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>

class Button {
public:
    Button(float x, float y, float width, float height, sf::Font& font, std::string text);
    void draw(sf::RenderWindow& window);
    bool isClicked(sf::RenderWindow& window);
    void setOnClick(std::function<void()> onClick);
    std::function<void()> onClickCallback;
    std::string getText() const;

private:
    sf::RectangleShape button;
    sf::Text buttonText;

};


#endif //HTML_PARSER_BUTTON_H
