//
// Created by Lawrence Degoma on 5/17/24.
//

#include "HtmlWindow.h"

HtmlWindow::HtmlWindow(HtmlRenderer& renderer) : renderer(renderer) {}

void HtmlWindow::applyCSS(HtmlElement* element, const std::vector<CSSRule>& cssRules) {
    // Apply styles to this element
    for (const CSSRule& rule : cssRules) {
        // Use the renderer's selector matching logic
        HtmlRenderer tempRenderer;
        if (matchesCSSSelector(element, rule.selector)) {
            for (const auto& property : rule.properties) {
                element->setCssProperty(property.first, property.second);
                std::cout << "Applied CSS: " << property.first << " = " << property.second << " to " << element->getTagName() << std::endl;
            }
        }
    }

    // Recursively apply to children
    for (HtmlElement* child : element->getChildren()) {
        applyCSS(child, cssRules);
    }
}

bool HtmlWindow::matchesCSSSelector(HtmlElement* element, const std::string& selector) {
    if (selector.empty() || !element) return false;
    
    // Handle class selectors (.classname)
    if (selector[0] == '.') {
        std::string className = selector.substr(1);
        std::string elementClass = element->getAttribute("class");
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
        if (!matchesCSSSelector(element, childSelector)) {
            return false;
        }
        
        // Check if any ancestor matches the parent selector
        HtmlElement* parent = element->getParent();
        while (parent) {
            if (matchesCSSSelector(parent, parentSelector)) {
                return true;
            }
            parent = parent->getParent();
        }
        return false;
    }
    
    // Handle simple tag selectors
    return element->getTagName() == selector;
}

void HtmlWindow::run(const std::string& htmlFilePath, const std::string& cssFilePath) {
    std::string htmlContent = readFile(htmlFilePath);

    if (htmlContent.empty()) {
        std::cerr << "Failed to read HTML file: " << htmlFilePath << std::endl;
        return;
    }

    HtmlParser parser(htmlContent);
    HtmlElement* root = parser.parse();

    if (!root) {
        std::cerr << "Failed to parse HTML content." << std::endl;
        return;
    }

    std::string cssContent = readFile(cssFilePath);
    if (cssContent.empty()) {
        std::cerr << "Failed to read CSS file: " << cssFilePath << std::endl;
        return;
    }

    CSSParser cssParser(cssContent);
    std::vector<CSSRule> cssRules = cssParser.parse();

    applyCSS(root, cssRules);

    sf::RenderWindow window(sf::VideoMode(1280, 720), "HTML Parser");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        renderer.render(window, root, cssRules);
        window.display();
    }
}

std::string HtmlWindow::readFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return "";
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
}