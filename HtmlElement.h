//
// Created by Lawrence Degoma on 5/17/24.
//

#ifndef HTML_ELEMENT_H
#define HTML_ELEMENT_H

#include <string>
#include <vector>
#include <unordered_map>

class HtmlElement {
public:
    HtmlElement(const std::string& tagName);
    const std::string& getTagName() const;
    void setText(const std::string& text);
    const std::string& getText() const;
    void addChild(HtmlElement* child);
    const std::vector<HtmlElement*>& getChildren() const;
    void setAttribute(const std::string& name, const std::string& value);
    std::string getAttribute(const std::string& name) const;
    void setCssProperty(const std::string& property, const std::string& value);
    std::string getCssProperty(const std::string& property) const;

private:
    std::string tagName;
    std::string text;
    std::vector<HtmlElement*> children;
    std::unordered_map<std::string, std::string> attributes;
    std::unordered_map<std::string, std::string> cssProperties;
};

#endif // HTML_ELEMENT_H
