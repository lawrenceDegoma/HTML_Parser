#include "HtmlRenderer.h"

HtmlRenderer::HtmlRenderer() {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Could not load font" << std::endl;
    }
}

void HtmlRenderer::render(sf::RenderWindow& window, HtmlElement* root, const std::vector<CSSRule>& cssRules) {
    if (root) {
        // Apply CSS styles to the HTML elements
        applyStyles(root, cssRules);

        float x = 10.0f;
        float y = 10.0f;
        renderElement(window, root, x, y);

        // Draw buttons
        for (auto& button : buttons) {
            button.draw(window);
        }

        // Handle button clicks
        handleButtonClicks(window);
    }
}

void HtmlRenderer::applyStyles(HtmlElement* element, const std::vector<CSSRule>& cssRules) {
    // Iterate through CSS rules and apply styles to the element
    for (const auto& rule : cssRules) {
        // Check if the selector matches the element
        if (matchesSelector(element, rule.selector)) {
            // Apply styles from the CSS rule to the element
            for (const auto& [property, value] : rule.properties) {
                element->setCssProperty(property, value);
            }
        }
    }
}

bool HtmlRenderer::matchesSelector(HtmlElement* element, const std::string& selector) {
    // Implement selector matching logic here
    // For simplicity, you can match based on element tag name only
    return element->getTagName() == selector;
}

void HtmlRenderer::renderElement(sf::RenderWindow& window, HtmlElement* element, float& x, float& y) {
    if (!element) return;

    std::string tagName = element->getTagName();
    sf::Color color = parseColor(element->getCssProperty("color"));
    unsigned int fontSize = parseFontSize(element->getCssProperty("font-size"));

    // Extract margin, padding, and border properties
    std::string margin = element->getCssProperty("margin");
    std::string padding = element->getCssProperty("padding");
    std::string borderWidthStr = element->getCssProperty("border-width");
    std::string borderStyle = element->getCssProperty("border-style");
    std::string borderColor = element->getCssProperty("border-color");

    // Convert margin, padding, and border strings to float values
    float marginValue = margin.empty() ? 0.0f : std::stof(margin);
    float paddingValue = padding.empty() ? 0.0f : std::stof(padding);
    float borderWidth = borderWidthStr.empty() ? 0.0f : std::stof(borderWidthStr);

    // Apply margin to x and y coordinates
    x += marginValue;
    y += marginValue;

    // Apply padding to x and y coordinates
    x += paddingValue;
    y += paddingValue;

    if (tagName == "h1") {
        renderText(window, element->getText(), x, y, fontSize ? fontSize : 30, color);
        y += 40;
    } else if (tagName == "h2") {
        renderText(window, element->getText(), x, y, fontSize ? fontSize : 24, color);
        y += 30;
    } else if (tagName == "p") {
        renderText(window, element->getText(), x, y, fontSize ? fontSize : 20, color);
        y += 30;
    } else if (tagName == "div") {
        sf::RectangleShape rect;
        rect.setPosition(x, y); // Position already adjusted with margin and padding
        float rectWidth = 780 - (2 * paddingValue); // Consider padding for width
        float rectHeight = 100 - (2 * paddingValue); // Consider padding for height
        rect.setSize(sf::Vector2f(rectWidth, rectHeight));
        rect.setFillColor(parseColor(element->getCssProperty("background-color")));

        // Set border properties
        if (borderStyle == "solid") { // Only apply if border style is solid
            rect.setOutlineColor(parseColor(borderColor));
            rect.setOutlineThickness(borderWidth); // Set border width
        }

        window.draw(rect);

        float childX = x + paddingValue; // Adjust child position with padding
        float childY = y + paddingValue; // Adjust child position with padding
        for (HtmlElement* child : element->getChildren()) {
            renderElement(window, child, childX, childY);
            childY += 10;
        }
        y = childY + paddingValue; // Adjust y position with padding
    } else if (tagName == "button") {
        // Render button
        float buttonWidth = 150.0f; // Default button width
        float buttonHeight = 50.0f; // Default button height
        std::string buttonText = element->getText();
        Button button(x, y, buttonWidth, buttonHeight, font, buttonText);
        button.setOnClick([buttonText]() {
            // Replace "program.exe" with the actual program you want to execute
            // You might want to pass arguments based on buttonText
            std::string command;
            if (buttonText == "Binary Search Tree") {
                command = "~/CLionProjects/BinarySearchTreeSFML/Build/BinarySearchTreeAnimation";
            } else if (buttonText == "Linked List") {
                command = "~/CLionProjects/LinkedListAnimation/build/LinkedListAnimation";
            } // Add more conditions as necessary
            std::system(command.c_str());
        });
        buttons.push_back(button);

        y += buttonHeight + marginValue; // Adjust y position for next element
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

sf::Color HtmlRenderer::parseColor(const std::string& colorStr) {
    if (colorStr.empty()) {
        return sf::Color::White; // Default color
    }
    if (colorStr[0] == '#') {
        std::istringstream iss(colorStr.substr(1));
        int r, g, b;
        if (colorStr.size() == 7) {
            unsigned int color;
            iss >> std::hex >> color;
            r = (color >> 16) & 0xFF;
            g = (color >> 8) & 0xFF;
            b = color & 0xFF;
        } else {
            // Handle shorthand hex colors
            std::string rStr = colorStr.substr(1, 1);
            std::string gStr = colorStr.substr(2, 1);
            std::string bStr = colorStr.substr(3, 1);
            r = std::stoi(rStr + rStr, nullptr, 16);
            g = std::stoi(gStr + gStr, nullptr, 16);
            b = std::stoi(bStr + bStr, nullptr, 16);
        }
        return sf::Color(r, g, b);
    }
    return sf::Color::White;
}

unsigned int HtmlRenderer::parseFontSize(const std::string& fontSizeStr) {
    if (fontSizeStr.empty()) {
        return 0; // Use default size
    }
    unsigned int size;
    std::stringstream(fontSizeStr) >> size;
    return size;
}

std::string HtmlRenderer::trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

void HtmlRenderer::handleButtonClicks(sf::RenderWindow& window) {
    for (auto& button : buttons) {
        if (button.isClicked(window)) {
            // If the button is clicked, execute its onClick callback
            button.onClickCallback();

            // If the button text is "Linked List", execute the linked list animation
            if (button.getText() == "Click Me!") {
                std::string command = "~/CLionProjects/LinkedListAnimation/build/LinkedListAnimation";
                std::system(command.c_str());
            }
            else if (button.getText() == "No, Me!") {
                std::string command = "~/CLionProjects/BinarySearchTreeSFML/Build/BinarySearchTreeSFML";
                std::system(command.c_str());
            }
            else if (button.getText() == "Over Here!") {
                std::string command = "~/CLionProjects/SortAnimation/Build/SortAnimation";
                std::system(command.c_str());
            }
        }
    }
}