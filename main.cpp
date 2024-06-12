#include "HtmlWindow.h"
#include "HtmlRenderer.h"

int main() {
    HtmlRenderer renderer;
    HtmlWindow window(renderer);

    window.run("index.html", "style.css");

    return 0;
}
