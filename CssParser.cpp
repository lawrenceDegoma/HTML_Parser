//
// Created by Lawrence Degoma on 5/20/24.
//

#include "CssParser.h"

CSSParser::CSSParser(const std::string& cssContent) : cssContent(cssContent), pos(0) {}

std::vector<CSSRule> CSSParser::parse() {
    std::vector<CSSRule> rules;
    while (pos < cssContent.size()) {
        skipWhitespace();
        if (pos < cssContent.size()) {
            rules.push_back(parseRule());
        }
    }
    return rules;
}

CSSRule CSSParser::parseRule() {
    CSSRule rule;
    rule.selector = parseIdentifier();
    skipWhitespace();
    if (cssContent[pos] == '{') {
        pos++;
        skipWhitespace();
        while (pos < cssContent.size() && cssContent[pos] != '}') {
            std::string property = parseIdentifier();
            skipWhitespace();
            if (cssContent[pos] == ':') {
                pos++;
                skipWhitespace();
                std::string value = parsePropertyValue();
                rule.properties[property] = value;
                skipWhitespace();
                if (cssContent[pos] == ';') {
                    pos++;
                    skipWhitespace();
                }
            }
        }
        if (cssContent[pos] == '}') {
            pos++;
        }
    }
    return rule;
}

void CSSParser::skipWhitespace() {
    while (pos < cssContent.size() && std::isspace(cssContent[pos])) {
        pos++;
    }
}

std::string CSSParser::parseIdentifier() {
    size_t start = pos;
    while (pos < cssContent.size() && (std::isalnum(cssContent[pos]) || cssContent[pos] == '-')) {
        pos++;
    }
    return cssContent.substr(start, pos - start);
}

std::string CSSParser::parsePropertyValue() {
    size_t start = pos;
    while (pos < cssContent.size() && cssContent[pos] != ';' && cssContent[pos] != '}') {
        pos++;
    }
    return cssContent.substr(start, pos - start);
}