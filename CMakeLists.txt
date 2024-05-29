cmake_minimum_required(VERSION 3.26)
project(HTML_Parser)

set(CMAKE_CXX_STANDARD 17)

add_executable(HTML_Parser main.cpp
        HtmlElement.cpp
        HtmlElement.h
        HtmlParser.cpp
        HtmlParser.h
        HtmlRenderer.cpp
        HtmlRenderer.h
        HtmlWindow.cpp
        HtmlWindow.h
        HtmlDocument.cpp
        HtmlDocument.h
        CssParser.cpp
        CssParser.h)
target_link_libraries(HTML_Parser sfml-graphics sfml-audio)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)