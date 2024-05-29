//
// Created by Lawrence Degoma on 5/17/24.
//

#include "HtmlElement.h"

HtmlElement::HtmlElement(const std::string& tagName) : tagName(tagName) {}

const std::string& HtmlElement::getTagName() const {
    return tagName;
}

void HtmlElement::setText(const std::string& text) {
    this->text = text;
}

const std::string& HtmlElement::getText() const {
    return text;
}

void HtmlElement::addChild(HtmlElement* child) {
    children.push_back(child);
}

const std::vector<HtmlElement*>& HtmlElement::getChildren() const {
    return children;
}

void HtmlElement::setAttribute(const std::string& name, const std::string& value) {
    attributes[name] = value;
}

std::string HtmlElement::getAttribute(const std::string& name) const {
    auto it = attributes.find(name);
    return it != attributes.end() ? it->second : "";
}

void HtmlElement::setCssProperty(const std::string& property, const std::string& value) {
    cssProperties[property] = value;
}

std::string HtmlElement::getCssProperty(const std::string& property) const {
    auto it = cssProperties.find(property);
    return it != cssProperties.end() ? it->second : "";
}