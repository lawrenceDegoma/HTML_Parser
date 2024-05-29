//
// Created by Lawrence Degoma on 5/17/24.
//

#include "HtmlWindow.h"

void applyCSS(HtmlElement* element, const std::vector<CSSRule>& cssRules) {
    for (const CSSRule& rule : cssRules) {
        if (rule.selector == element->getTagName()) {
            for (const auto& property : rule.properties) {
                element->setCssProperty(property.first, property.second);
                std::cout << "Applied CSS: " << property.first << " = " << property.second << " to " << element->getTagName() << std::endl;
            }
        }
    }

    for (HtmlElement* child : element->getChildren()) {
        applyCSS(child, cssRules);
    }
}

HtmlWindow::HtmlWindow(HtmlRenderer& renderer) : renderer(renderer) {}

std::string readFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return "";
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
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

    sf::RenderWindow window(sf::VideoMode(800, 600), "HTML Parser");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        renderer.render(window, root);
        window.display();
    }
}