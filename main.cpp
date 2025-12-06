#include "HtmlWindow.h"
#include "HtmlRenderer.h"
#include <iostream>
#include <fstream>
#include <vector>

int main() {
    HtmlRenderer renderer;
    HtmlWindow window(renderer);

    // Try multiple paths for HTML and CSS files
    std::vector<std::string> htmlPaths = {"index.html", "../index.html", "../../index.html"};
    std::vector<std::string> cssPaths = {"styles.css", "../styles.css", "../../styles.css"};
    
    std::string htmlFile, cssFile;
    
    // Find HTML file
    for (const std::string& path : htmlPaths) {
        std::ifstream file(path);
        if (file.good()) {
            htmlFile = path;
            break;
        }
    }
    
    // Find CSS file
    for (const std::string& path : cssPaths) {
        std::ifstream file(path);
        if (file.good()) {
            cssFile = path;
            break;
        }
    }
    
    if (htmlFile.empty()) {
        std::cerr << "Could not find index.html" << std::endl;
        return 1;
    }
    
    if (cssFile.empty()) {
        std::cerr << "Could not find style.css" << std::endl;
        return 1;
    }
    
    std::cout << "Using HTML file: " << htmlFile << std::endl;
    std::cout << "Using CSS file: " << cssFile << std::endl;
    
    window.run(htmlFile, cssFile);

    return 0;
}
