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
    }
}

void HtmlRenderer::applyStyles(HtmlElement* element, const std::vector<CSSRule>& cssRules) {
    // Iterate through CSS rules and apply styles to the element
    for (const auto& rule : cssRules) {
        // Check if the selector matches the element
        if (matchesSelector(element, rule.selector)) {
            // Apply styles from the CSS rule to the element
            for (const auto& [property, value] : rule.properties) {
                if (property == "color") {
                    element->setCssProperty("color", value); // Set the color property directly
                } else {
                    element->setCssProperty(property, value);
                }
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
    std::string align = element->getCssProperty("text-align");

    // Extract margin and padding properties
    std::string margin = element->getCssProperty("margin");
    std::string padding = element->getCssProperty("padding");

    // Convert margin and padding strings to float values
    float marginValue = margin.empty() ? 0.0f : std::stof(margin);
    float paddingValue = padding.empty() ? 0.0f : std::stof(padding);

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
        rect.setPosition(x, y);
        rect.setSize(sf::Vector2f(780, 100));
        rect.setFillColor(parseColor(element->getCssProperty("background-color")));
        rect.setOutlineColor(parseColor(element->getCssProperty("border-color")));
        rect.setOutlineThickness(1.0f);
        window.draw(rect);

        float childX = x + paddingValue;
        float childY = y + paddingValue;
        for (HtmlElement* child : element->getChildren()) {
            renderElement(window, child, childX, childY);
            childY += 10;
        }
        y = childY + paddingValue;
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
        iss >> std::hex >> r >> g >> b;
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
