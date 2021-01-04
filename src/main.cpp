#include "io.hpp"
#include "shape.hpp"
#include "window.hpp"
#include "shaders.hpp"

int main()
{
    using namespace sssim;
    Window window;
    if (!window.init(Window::Options()).ok()) return -1;
    window.setColour(0.2f, 0.3f, 0.3f, 1.0f);
    int shader = -1;
    loadShader("basic.vert").match(&shader, [](std::string err) { sssim::log(err); });
    if (shader == -1) return -1;
    do
    {
        window.clear();

        if (window.keyDown(sssim::key::ESC)) window.close();

        sssim::Triangle triangle{{-0.5, -0.5}, {0, 0.5}, {0.5, -0.5}};
    } while (window.update());

    return 0;
}

