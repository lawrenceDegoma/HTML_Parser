#include "HtmlParser.h"

HtmlParser::HtmlParser(const std::string& content) : htmlContent(content) {}

HtmlElement* HtmlParser::parse() {
    // For simplicity, let's create a basic parser using regex
    HtmlElement* root = new HtmlElement("html");

    std::regex elementRegex(R"(<(\w+)[^>]*>(.*?)<\/\1>)");
    auto elementsBegin = std::sregex_iterator(htmlContent.begin(), htmlContent.end(), elementRegex);
    auto elementsEnd = std::sregex_iterator();

    for (std::sregex_iterator i = elementsBegin; i != elementsEnd; ++i) {
        std::smatch match = *i;
        std::string tagName = match[1].str();
        std::string innerText = match[2].str();

        HtmlElement* element = new HtmlElement(tagName);
        element->setText(innerText);
        root->addChild(element);
    }

    return root;
}