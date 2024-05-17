//
// Created by Lawrence Degoma on 5/17/24.
//

#include "HtmlParser.h"

HtmlParser::HtmlParser(const std::string& htmlContent) : htmlContent(htmlContent), currentPosition(0){}

HtmlElement* HtmlParser::parse(){
    return parseElement();
}

HtmlElement* HtmlParser::parseElement(){
    skipWhiteSpace();
    if (htmlContent[currentPosition] != '<'){
        return nullptr;
    }

    currentPosition++;
    std::string tagName = parseTagName();

    HtmlElement* element = new HtmlElement(tagName);

    skipWhiteSpace();
    if (htmlContent[currentPosition] == '>'){
        currentPosition++;
        element->setText(parseText());

        while (htmlContent[currentPosition] != '<' || htmlContent[currentPosition+1] != '/'){
            HtmlElement* child = parseElement();
            if (child){
                element->addChild(child);
            }
        }

        currentPosition += tagName.size() + 3;
    }
    
    return element;
}

std::string HtmlParser::parseTagName() {
    size_t start = currentPosition;
    while (std::isalnum(htmlContent[currentPosition])) {
        currentPosition++;
    }
    return htmlContent.substr(start, currentPosition - start);
}

std::string HtmlParser::parseText() {
    size_t start = currentPosition;
    while (htmlContent[currentPosition] != '<') {
        currentPosition++;
    }
    return htmlContent.substr(start, currentPosition - start);
}

void HtmlParser::skipWhiteSpace() {
    while (std::isspace(htmlContent[currentPosition])) {
        currentPosition++;
    }
}