//
// Created by Lawrence Degoma on 5/17/24.
//

#include "HtmlElement.h"

HtmlElement::HtmlElement(const std::string& tagName) : tagName(tagName) {}

void HtmlElement::setTagName(const std::string& tagName) {
    this->tagName = tagName;
}

std::string HtmlElement::getTagName() const {
    return tagName;
}

void HtmlElement::setText(const std::string& text) {
    this->text = text;
}

std::string HtmlElement::getText() const {  // Ensure this matches the declaration
    return text;
}

void HtmlElement::addChild(HtmlElement* child) {
    children.push_back(child);
}

const std::vector<HtmlElement*>& HtmlElement::getChildren() const {
    return children;
}