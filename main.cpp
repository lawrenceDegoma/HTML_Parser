#include "HtmlWindow.h"

int main() {
    HtmlRenderer renderer;
    HtmlWindow window(renderer);
    window.run("test.html");

    return 0;
}
