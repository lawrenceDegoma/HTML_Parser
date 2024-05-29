#include "HtmlWindow.h"
#include "HtmlRenderer.h"

int main() {
    HtmlRenderer renderer;
    HtmlWindow window(renderer);

    window.run("test.html", "styles.css");

    return 0;
}
