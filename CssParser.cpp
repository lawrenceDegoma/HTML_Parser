//
// Created by Lawrence Degoma on 5/20/24.
//

#include "CssParser.h"

CSSParser::CSSParser(const std::string& cssContent) : cssContent(cssContent), pos(0) {}

std::vector<CSSRule> CSSParser::parse() {
    std::vector<CSSRule> rules;
    while (pos < cssContent.size()) {
        skipWhitespaceAndComments();
        if (pos < cssContent.size()) {
            rules.push_back(parseRule());
        }
    }
    return rules;
}

CSSRule CSSParser::parseRule() {
    CSSRule rule;
    rule.selector = parseSelector();
    skipWhitespaceAndComments();
    if (cssContent[pos] == '{') {
        pos++;
        skipWhitespaceAndComments();
        while (pos < cssContent.size() && cssContent[pos] != '}') {
            std::string property = parseIdentifier();
            skipWhitespaceAndComments();
            if (cssContent[pos] == ':') {
                pos++;
                skipWhitespaceAndComments();
                std::string value = parsePropertyValue();
                if (property == "margin" || property == "padding") {
                    // Handle margin and padding properties separately
                    rule.properties[property] = value;
                } else {
                    rule.properties[property] = value;
                }
                skipWhitespaceAndComments();
                if (cssContent[pos] == ';') {
                    pos++;
                    skipWhitespaceAndComments();
                }
            }
        }
        if (cssContent[pos] == '}') {
            pos++;
            skipWhitespaceAndComments();
        }
    }
    return rule;
}

void CSSParser::skipWhitespaceAndComments() {
    while (pos < cssContent.size()) {
        if (std::isspace(cssContent[pos])) {
            pos++;
        } else if (startsWith("/*")) {
            skipComment();
        } else {
            break;
        }
    }
}

void CSSParser::skipComment() {
    while (pos < cssContent.size() - 1) {
        if (startsWith("*/")) {
            pos += 2; // Skip '*/'
            break;
        }
        pos++;
    }
}

std::string CSSParser::parseSelector() {
    size_t start = pos;
    while (pos < cssContent.size() && cssContent[pos] != '{' && !std::isspace(cssContent[pos])) {
        // Keep parsing until reaching '{' or whitespace
        pos++;
    }
    std::string selector = cssContent.substr(start, pos - start);

    // Trim any leading or trailing whitespace
    size_t firstNonSpace = selector.find_first_not_of(" \t\n\r\f\v");
    size_t lastNonSpace = selector.find_last_not_of(" \t\n\r\f\v");
    if (firstNonSpace != std::string::npos && lastNonSpace != std::string::npos) {
        selector = selector.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
    }

    return selector;
}

std::string CSSParser::parseIdentifier() {
    size_t start = pos;
    while (pos < cssContent.size() && std::isalnum(cssContent[pos]) || cssContent[pos] == '-' || cssContent[pos] == '#') {
        pos++;
    }
    return cssContent.substr(start, pos - start);
}

std::string CSSParser::parsePropertyValue() {
    size_t start = pos;
    while (pos < cssContent.size() && cssContent[pos] != ';' && cssContent[pos] != '}') {
        if (cssContent[pos] == '"') {
            // Handle quoted strings
            pos++;
            while (pos < cssContent.size() && cssContent[pos] != '"') {
                pos++;
            }
            if (pos < cssContent.size() && cssContent[pos] == '"') {
                pos++; // Skip closing quote
            }
        }
        pos++;
    }
    return cssContent.substr(start, pos - start);
}

bool CSSParser::startsWith(const std::string& prefix) const {
    return cssContent.compare(pos, prefix.size(), prefix) == 0;
}