#include "io.hpp"
#include "shaders.hpp"
#include "shape.hpp"
#include "window.hpp"
#include "graphics.hpp"

int main()
{
    using namespace sssim;
    Window window;
    if (!window.init(Window::Options()).ok()) return -1;
    window.setColour(0.2f, 0.3f, 0.3f, 1.0f);
    auto shader_program = createShaderProgram({"basic.vert", "basic.frag"});
    if (const auto err_ = shader_program.err(); err_) {
        log(*err_);
        return -1;
    }
    glUseProgram(*shader_program.ok());

    sssim::log("SSSim: Starting main render loop.");
    do
    {
        window.clear();

        if (window.keyDown(sssim::key::ESC)) window.close();

        sssim::Triangle triangle{{-0.5, -0.5}, {0, 0.5}, {0.5, -0.5}};
    } while (window.update());

    return 0;
}

