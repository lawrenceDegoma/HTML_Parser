#include "HtmlParser.h"

HtmlParser::HtmlParser(const std::string& htmlContent) : htmlContent(htmlContent), pos(0) {}

HtmlElement* HtmlParser::parse() {
    return parseElement();
}

HtmlElement* HtmlParser::parseElement() {
    skipWhitespace();

    if (pos >= htmlContent.size() || htmlContent[pos] != '<') {
        return nullptr;
    }
    pos++;

    std::string tagName = parseTagName();

    HtmlElement* element = new HtmlElement(tagName);

    while (pos < htmlContent.size() && htmlContent[pos] != '>') {
        pos++;
    }
    pos++; // Skip '>'

    std::string text = parseText();
    if (!text.empty()) {
        element->setText(text);
    }

    while (!startsWith("</" + tagName + ">") && pos < htmlContent.size()) {
        HtmlElement* child = parseElement();
        if (child) {
            element->addChild(child);
        } else {
            break;
        }
        skipWhitespace();
    }

    if (startsWith("</" + tagName + ">")) {
        pos += tagName.size() + 3; // Skip '</tagName>'
    } else {
        std::cerr << "Expected closing tag </" << tagName << ">" << std::endl;
    }

    return element;
}

std::string HtmlParser::parseTagName() {
    size_t start = pos;
    while (pos < htmlContent.size() && std::isalnum(htmlContent[pos])) {
        pos++;
    }
    return htmlContent.substr(start, pos - start);
}

std::string HtmlParser::parseText() {
    size_t start = pos;
    while (pos < htmlContent.size() && htmlContent[pos] != '<') {
        pos++;
    }
    return htmlContent.substr(start, pos - start);
}

void HtmlParser::skipWhitespace() {
    while (pos < htmlContent.size() && std::isspace(htmlContent[pos])) {
        pos++;
    }
}

bool HtmlParser::startsWith(const std::string& prefix) const {
    return htmlContent.compare(pos, prefix.size(), prefix) == 0;
}
