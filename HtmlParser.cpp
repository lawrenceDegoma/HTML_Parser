#include "HtmlParser.h"

HtmlParser::HtmlParser(const std::string& htmlContent) : htmlContent(htmlContent), pos(0) {}

HtmlElement* HtmlParser::parse() {
    // Skip the DOCTYPE declaration
    skipDoctype();

    HtmlElement* root = parseElement();
    if (root) {
        std::cout << "Successfully parsed root element: " << root->getTagName() << std::endl;
    } else {
        std::cerr << "Failed to parse HTML content." << std::endl;
    }
    return root;
}

HtmlElement* HtmlParser::parseElement() {
    skipWhitespace();

    if (pos >= htmlContent.size() || htmlContent[pos] != '<') {
        return nullptr;
    }
    pos++;

    // Skip comments
    if (htmlContent[pos] == '!' && startsWith("--")) {
        skipComment();
        skipWhitespace();
        return parseElement();
    }

    std::string tagName = parseTagName();
    if (tagName.empty()) {
        std::cerr << "Failed to parse tag name at position " << pos << std::endl;
        return nullptr;
    }

    HtmlElement* element = new HtmlElement(tagName);

    // Parse attributes
    while (pos < htmlContent.size() && htmlContent[pos] != '>' && htmlContent[pos] != '/') {
        skipWhitespace();
        parseAttribute(element);
    }

    if (pos < htmlContent.size() && htmlContent[pos] == '/') {
        // Self-closing tag
        pos++; // Skip '/'
        if (pos < htmlContent.size() && htmlContent[pos] == '>') {
            pos++; // Skip '>'
            std::cout << "Parsed self-closing tag: " << tagName << std::endl;
            return element;
        } else {
            std::cerr << "Expected '>' for self-closing tag at position " << pos << std::endl;
            return nullptr;
        }
    }

    if (pos < htmlContent.size() && htmlContent[pos] == '>') {
        pos++; // Skip '>'

        while (true) {
            skipWhitespace();
            if (startsWith("</" + tagName + ">")) {
                pos += tagName.size() + 3; // Skip '</tagName>'
                std::cout << "Parsed closing tag: " << tagName << std::endl;
                break;
            }
            if (pos >= htmlContent.size()) {
                std::cerr << "Unexpected end of file while parsing " << tagName << std::endl;
                break;
            }

            HtmlElement* child = parseElement();
            if (child) {
                element->addChild(child);
            } else {
                std::string text = parseText();
                if (!text.empty()) {
                    element->setText(text);
                }
            }
        }
    } else {
        std::cerr << "Expected '>' after tag name at position " << pos << std::endl;
    }

    return element;
}

std::string HtmlParser::parseTagName() {
    size_t start = pos;
    while (pos < htmlContent.size() && (std::isalnum(htmlContent[pos]) || htmlContent[pos] == '-')) {
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

void HtmlParser::skipDoctype() {
    if (startsWith("<!DOCTYPE")) {
        while (pos < htmlContent.size() && htmlContent[pos] != '>') {
            pos++;
        }
        if (pos < htmlContent.size() && htmlContent[pos] == '>') {
            pos++;
        }
    }
}

void HtmlParser::skipComment() {
    if (startsWith("<!--")) {
        pos += 4; // Skip '<!--'
        while (pos < htmlContent.size() && !startsWith("-->")) {
            pos++;
        }
        if (startsWith("-->")) {
            pos += 3; // Skip '-->'
        }
    }
}

void HtmlParser::parseAttribute(HtmlElement* element) {
    skipWhitespace();

    std::string name = parseTagName();
    if (name.empty()) {
        return;
    }

    skipWhitespace();

    if (pos < htmlContent.size() && htmlContent[pos] == '=') {
        pos++;
        skipWhitespace();

        std::string value;
        if (pos < htmlContent.size() && (htmlContent[pos] == '"' || htmlContent[pos] == '\'')) {
            char quote = htmlContent[pos];
            pos++;
            size_t start = pos;
            while (pos < htmlContent.size() && htmlContent[pos] != quote) {
                pos++;
            }
            value = htmlContent.substr(start, pos - start);
            if (pos < htmlContent.size() && htmlContent[pos] == quote) {
                pos++;
            }
        } else {
            size_t start = pos;
            while (pos < htmlContent.size() && !std::isspace(htmlContent[pos]) && htmlContent[pos] != '>' && htmlContent[pos] != '/') {
                pos++;
            }
            value = htmlContent.substr(start, pos - start);
        }

        element->setAttribute(name, value);
    } else {
        element->setAttribute(name, "");
    }
}