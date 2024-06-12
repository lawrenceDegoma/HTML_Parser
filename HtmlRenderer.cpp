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
    std::string align = element->getCssProperty("text-align");

    if (tagName == "h1") {
        renderText(window, element->getText(), x, y, fontSize ? fontSize : 30, color);
        y += 40;
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

        float childX = x + 10;
        float childY = y + 10;
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

sf::Color HtmlRenderer::parseColor(const std::string& colorStr) {
    if (colorStr.empty()) {
        return sf::Color::Black; // Default color
    }
    if (colorStr[0] == '#') {
        unsigned int r, g, b;
        sscanf(colorStr.c_str(), "#%02x%02x%02x", &r, &g, &b);
        return sf::Color(r, g, b);
    }
    return sf::Color::Black;
}

unsigned int HtmlRenderer::parseFontSize(const std::string& fontSizeStr) {
    if (fontSizeStr.empty()) {
        return 0; // Use default size
    }
    unsigned int size;
    std::stringstream(fontSizeStr) >> size;
    return size;
}

