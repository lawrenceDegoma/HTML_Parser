#include "HtmlRenderer.h"

HtmlRenderer::HtmlRenderer() {
    // Try multiple font paths
    bool fontLoaded = false;
    std::vector<std::string> fontPaths = {
        "arial.ttf",
        "../arial.ttf",
        "../../arial.ttf",
        "/System/Library/Fonts/Arial.ttf",  // macOS system font
        "/System/Library/Fonts/Helvetica.ttc" // macOS fallback
    };
    
    for (const std::string& path : fontPaths) {
        if (font.loadFromFile(path)) {
            std::cout << "Successfully loaded font: " << path << std::endl;
            fontLoaded = true;
            break;
        }
    }
    
    if (!fontLoaded) {
        std::cerr << "Could not load any font. Using default system font." << std::endl;
        // SFML will use a default font if no font is loaded
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
    if (selector.empty() || !element) return false;
    
    // Handle class selectors (.classname)
    if (selector[0] == '.') {
        std::string className = selector.substr(1);
        std::string elementClass = element->getAttribute("class");
        // Check if element has this class (could have multiple classes)
        return elementClass.find(className) != std::string::npos;
    }
    
    // Handle ID selectors (#idname)
    if (selector[0] == '#') {
        std::string idName = selector.substr(1);
        return element->getAttribute("id") == idName;
    }
    
    // Handle descendant selectors (e.g., ".option h2")
    if (selector.find(' ') != std::string::npos) {
        size_t spacePos = selector.find(' ');
        std::string parentSelector = selector.substr(0, spacePos);
        std::string childSelector = selector.substr(spacePos + 1);
        
        // Check if this element matches the child selector
        if (!matchesSelector(element, childSelector)) {
            return false;
        }
        
        // Check if any ancestor matches the parent selector
        HtmlElement* parent = element->getParent();
        while (parent) {
            if (matchesSelector(parent, parentSelector)) {
                return true;
            }
            parent = parent->getParent();
        }
        return false;
    }
    
    // Handle simple tag selectors
    return element->getTagName() == selector;
}

void HtmlRenderer::renderElement(sf::RenderWindow& window, HtmlElement* element, float& x, float& y) {
    if (!element) return;

    std::string tagName = element->getTagName();
    sf::Color textColor = parseColor(element->getCssProperty("color"));
    unsigned int fontSize = parseFontSize(element->getCssProperty("font-size"));
    
    // Parse layout properties
    std::string margin = element->getCssProperty("margin");
    std::string padding = element->getCssProperty("padding");
    std::string width = element->getCssProperty("width");
    std::string height = element->getCssProperty("height");
    std::string backgroundColor = element->getCssProperty("background-color");
    
    // Convert values to pixels
    float marginValue = parsePixelValue(margin);
    float paddingValue = parsePixelValue(padding);
    float elementWidth = parsePixelValue(width);
    float elementHeight = parsePixelValue(height);

    // Apply margin
    x += marginValue;
    y += marginValue;

    if (tagName == "h1") {
        renderText(window, element->getText(), x, y, fontSize ? fontSize : 30, textColor);
        y += 40 + marginValue;
    } else if (tagName == "h2") {
        renderText(window, element->getText(), x, y, fontSize ? fontSize : 24, textColor);
        y += 30 + marginValue;
    } else if (tagName == "p") {
        renderText(window, element->getText(), x, y, fontSize ? fontSize : 16, textColor);
        y += 25 + marginValue;
    } else if (tagName == "div") {
        float startX = x;
        float startY = y;
        
        // Calculate div size
        float divWidth = elementWidth > 0 ? elementWidth : 800;
        float divHeight = elementHeight > 0 ? elementHeight : 100;
        
        // Render background if specified
        if (!backgroundColor.empty()) {
            sf::RectangleShape rect;
            rect.setPosition(x, y);
            rect.setSize(sf::Vector2f(divWidth, divHeight));
            rect.setFillColor(parseColor(backgroundColor));
            window.draw(rect);
        }
        
        // Apply padding for children
        float childX = x + paddingValue;
        float childY = y + paddingValue;
        
        // Handle display: flex
        std::string display = element->getCssProperty("display");
        if (display == "flex") {
            std::string justifyContent = element->getCssProperty("justify-content");
            float childSpacing = 20.0f; // Default spacing
            
            if (justifyContent == "space-between") {
                float totalChildrenWidth = element->getChildren().size() * 200; // Estimate
                childSpacing = (divWidth - totalChildrenWidth) / (element->getChildren().size() - 1);
            }
            
            for (HtmlElement* child : element->getChildren()) {
                renderElement(window, child, childX, childY);
                childX += 250 + childSpacing; // Move to next position
            }
        } else {
            // Normal block layout
            for (HtmlElement* child : element->getChildren()) {
                renderElement(window, child, childX, childY);
                childY += 10; // Add some spacing between children
            }
        }
        
        y = std::max(y + divHeight + marginValue, childY + paddingValue);
    } else if (tagName == "button") {
        // Render button
        float buttonWidth = elementWidth > 0 ? elementWidth : 150.0f;
        float buttonHeight = elementHeight > 0 ? elementHeight : 50.0f;
        std::string buttonText = element->getText();
        
        Button button(x, y, buttonWidth, buttonHeight, font, buttonText);
        
        // Apply button styling
        sf::Color bgColor = parseColor(element->getCssProperty("background-color"));
        if (bgColor != sf::Color::Black) {
            // Set button background color
        }
        
        button.setOnClick([buttonText]() {
            std::string command;
            if (buttonText == "Click Me!") {
                command = "~/CLionProjects/LinkedListAnimation/build/LinkedListAnimation";
            } else if (buttonText == "No, Me!") {
                command = "~/CLionProjects/BinarySearchTreeSFML/Build/BinarySearchTreeSFML";
            } else if (buttonText == "Over Here!") {
                command = "~/CLionProjects/SortAnimation/Build/SortAnimation";
            }
            if (!command.empty()) {
                std::system(command.c_str());
            }
        });
        buttons.push_back(button);

        y += buttonHeight + marginValue;
    } else {
        // Default rendering for other elements
        if (!element->getText().empty()) {
            renderText(window, element->getText(), x, y, fontSize ? fontSize : 16, textColor);
            y += 20;
        }
        
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
    
    // Handle hex colors
    if (colorStr[0] == '#') {
        if (colorStr.size() == 7) {
            unsigned int color;
            std::istringstream iss(colorStr.substr(1));
            iss >> std::hex >> color;
            int r = (color >> 16) & 0xFF;
            int g = (color >> 8) & 0xFF;
            int b = color & 0xFF;
            return sf::Color(r, g, b);
        } else if (colorStr.size() == 4) {
            // Handle shorthand hex colors
            std::string rStr = colorStr.substr(1, 1);
            std::string gStr = colorStr.substr(2, 1);
            std::string bStr = colorStr.substr(3, 1);
            int r = std::stoi(rStr + rStr, nullptr, 16);
            int g = std::stoi(gStr + gStr, nullptr, 16);
            int b = std::stoi(bStr + bStr, nullptr, 16);
            return sf::Color(r, g, b);
        }
    }
    
    // Handle RGB colors
    if (colorStr.find("rgb(") == 0) {
        size_t start = colorStr.find('(') + 1;
        size_t end = colorStr.find(')', start);
        std::string rgbValues = colorStr.substr(start, end - start);
        
        std::istringstream iss(rgbValues);
        std::string token;
        int r = 0, g = 0, b = 0;
        int count = 0;
        
        while (std::getline(iss, token, ',') && count < 3) {
            token.erase(0, token.find_first_not_of(" \t"));
            token.erase(token.find_last_not_of(" \t") + 1);
            
            if (count == 0) r = std::stoi(token);
            else if (count == 1) g = std::stoi(token);
            else if (count == 2) b = std::stoi(token);
            count++;
        }
        return sf::Color(r, g, b);
    }
    
    // Handle named colors
    if (colorStr == "white") return sf::Color::White;
    if (colorStr == "black") return sf::Color::Black;
    if (colorStr == "red") return sf::Color::Red;
    if (colorStr == "green") return sf::Color::Green;
    if (colorStr == "blue") return sf::Color::Blue;
    if (colorStr == "yellow") return sf::Color::Yellow;
    if (colorStr == "magenta") return sf::Color::Magenta;
    if (colorStr == "cyan") return sf::Color::Cyan;
    
    return sf::Color::Black; // Default color
}

unsigned int HtmlRenderer::parseFontSize(const std::string& fontSizeStr) {
    if (fontSizeStr.empty()) {
        return 16; // Default font size
    }
    
    // Remove units and parse the number
    std::string numStr = fontSizeStr;
    if (numStr.find("px") != std::string::npos) {
        numStr = numStr.substr(0, numStr.find("px"));
    } else if (numStr.find("pt") != std::string::npos) {
        numStr = numStr.substr(0, numStr.find("pt"));
    } else if (numStr.find("em") != std::string::npos) {
        numStr = numStr.substr(0, numStr.find("em"));
        // Convert em to pixels (assuming 1em = 16px)
        float emValue = std::stof(numStr);
        return static_cast<unsigned int>(emValue * 16);
    }
    
    try {
        return static_cast<unsigned int>(std::stoi(numStr));
    } catch (const std::exception&) {
        return 16; // Default if parsing fails
    }
}

std::string HtmlRenderer::trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

float HtmlRenderer::parsePixelValue(const std::string& value) {
    if (value.empty()) {
        return 0.0f;
    }
    
    std::string trimmedValue = trim(value);
    
    // Remove px, em, rem, % units and parse the number
    std::string numStr = trimmedValue;
    if (numStr.find("px") != std::string::npos) {
        numStr = numStr.substr(0, numStr.find("px"));
    } else if (numStr.find("em") != std::string::npos) {
        numStr = numStr.substr(0, numStr.find("em"));
        // Convert em to pixels (assuming 1em = 16px)
        try {
            float emValue = std::stof(numStr);
            return emValue * 16.0f;
        } catch (const std::exception&) {
            return 0.0f;
        }
    } else if (numStr.find("%") != std::string::npos) {
        // For now, treat percentage as pixels (simplified)
        numStr = numStr.substr(0, numStr.find("%"));
    }
    
    try {
        return std::stof(numStr);
    } catch (const std::exception&) {
        return 0.0f;
    }
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