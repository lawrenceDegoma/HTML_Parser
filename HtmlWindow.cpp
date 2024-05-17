//
// Created by Lawrence Degoma on 5/17/24.
//

#include "HtmlWindow.h"

HtmlWindow::HtmlWindow(HtmlRenderer& renderer) : renderer(renderer) {}

void HtmlWindow::run(const std::string& htmlFilePath) {
    std::string htmlContent = HtmlDocument::readHtmlFile(htmlFilePath);

    if (htmlContent.empty()) {
        std::cerr << "Failed to read HTML file: " << htmlFilePath << std::endl;
        return;
    }

    HtmlParser parser(htmlContent);
    HtmlElement* root = parser.parse();

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