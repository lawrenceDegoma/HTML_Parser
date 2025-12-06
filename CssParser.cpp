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
    if (pos < cssContent.size() && cssContent[pos] == '{') {
        pos++;
        skipWhitespaceAndComments();
        while (pos < cssContent.size() && cssContent[pos] != '}') {
            std::string property = parseIdentifier();
            skipWhitespaceAndComments();
            if (pos < cssContent.size() && cssContent[pos] == ':') {
                pos++;
                skipWhitespaceAndComments();
                std::string value = trim(parsePropertyValue());
                rule.properties[property] = value;
                skipWhitespaceAndComments();
                if (pos < cssContent.size() && cssContent[pos] == ';') {
                    pos++;
                    skipWhitespaceAndComments();
                }
            }
        }
        if (pos < cssContent.size() && cssContent[pos] == '}') {
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
    while (pos < cssContent.size() && cssContent[pos] != '{') {
        pos++;
    }
    std::string selector = cssContent.substr(start, pos - start);
    return trim(selector);
}

std::string CSSParser::parseIdentifier() {
    size_t start = pos;
    while (pos < cssContent.size() && (std::isalnum(cssContent[pos]) || cssContent[pos] == '-' || cssContent[pos] == '#')) {
        pos++;
    }
    return cssContent.substr(start, pos - start);
}

std::string CSSParser::parsePropertyValue() {
    size_t start = pos;
    while (pos < cssContent.size() && cssContent[pos] != ';' && cssContent[pos] != '}') {
        if (cssContent[pos] == '"' || cssContent[pos] == '\'') {
            // Handle quoted strings
            char quote = cssContent[pos];
            pos++;
            while (pos < cssContent.size() && cssContent[pos] != quote) {
                pos++;
            }
            if (pos < cssContent.size() && cssContent[pos] == quote) {
                pos++; // Skip closing quote
            }
        } else {
            pos++;
        }
    }
    return cssContent.substr(start, pos - start);
}

bool CSSParser::startsWith(const std::string& prefix) const {
    return cssContent.compare(pos, prefix.size(), prefix) == 0;
}

std::vector<std::string> CSSParser::splitBySpaces(const std::string& str) {
    std::istringstream iss(str);
    std::vector<std::string> result;
    std::string word;
    while (iss >> word) {
        result.push_back(word);
    }
    return result;
}

std::string CSSParser::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}