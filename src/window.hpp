#ifndef SSSIM_WINDOW_HPP
#define SSSIM_WINDOW_HPP

#include <optional>
#include <string>

#include "result.hpp"

class GLFWwindow;

namespace sssim
{
// TODO - Move this to a header, autogenerate options
// Or set up properly, not sure how I was initially planning this
struct key
{
    using type                = int;
    constexpr static type ESC = 256;
};

class Window
{
public:
    struct Options
    {
        Options() {}  // Clang really doesn't like defaulting here

        /**
         * Default option values.
         */

        // These could be long longs, etc.
        // But they aren't.
        // y2k incoming
        int gl_major_version_{3};
        int gl_minor_version_{3};

        std::string name_{""};

        int width_{800};
        int height_{600};

        /**
         * Builder pattern for constructing
         * window options. It's great. Trust me.
         */
        Options& name(std::string in);
        Options& major(int in);
        Options& minor(int in);
        Options& width(int in);
        Options& height(int in);
    };

public:
    [[nodiscard]] sssim::Result<void> init(Options opts = Options{});
    bool update();
    bool keyDown(const key::type& key);
    void close();
    void clear();
    void setColour(double r, double g, double b, double a);
    ~Window();

private:
    void startGLFW();
    void stopGLFW();
    bool init_          = false;
    GLFWwindow* window_ = nullptr;
};

}  // namespace sssim

#endif  // SSSIM_WINDOW_HPP
