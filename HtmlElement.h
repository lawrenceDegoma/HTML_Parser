//
// Created by Lawrence Degoma on 5/17/24.
//

#ifndef HTML_ELEMENT_H
#define HTML_ELEMENT_H

#include <string>
#include <vector>

class HtmlElement {
private:
    std::string tagName;
    std::string text;
    std::vector<HtmlElement*> children;

public:
    HtmlElement(const std::string& tagName);

    void setTagName(const std::string& tagName);
    std::string getTagName() const;

    void setText(const std::string& text);
    std::string getText() const;  // Ensure this declaration matches the implementation

    void addChild(HtmlElement* child);
    const std::vector<HtmlElement*>& getChildren() const;
};

#endif // HTML_ELEMENT_H
