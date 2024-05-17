//
// Created by Lawrence Degoma on 5/17/24.
//

#include "HtmlDocument.h"

std::string HtmlDocument::readHtmlFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filePath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}