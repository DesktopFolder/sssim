// Header file include
#include "window.hpp"

#include "graphics.hpp"
#include "io.hpp"
#include "result.hpp"

sssim::Window::Options& sssim::Window::Options::name(std::string in)
{
    name_ = in;
    return *this;
}
sssim::Window::Options& sssim::Window::Options::major(int in)
{
    gl_major_version_ = in;
    return *this;
}
sssim::Window::Options& sssim::Window::Options::minor(int in)
{
    gl_minor_version_ = in;
    return *this;
}
sssim::Window::Options& sssim::Window::Options::width(int in)
{
    width_ = in;
    return *this;
}
sssim::Window::Options& sssim::Window::Options::height(int in)
{
    height_ = in;
    return *this;
}

void ResizeWindowCallback(GLFWwindow*, int width, int height) { glViewport(0, 0, width, height); }
void ErrorCallback(int, const char* message) { sssim::log(message); }

sssim::Window::~Window() { stopGLFW(); }

// This should return Result probably
sssim::Result<void> sssim::Window::init(Window::Options opts)
{
    startGLFW();
    glfwSetErrorCallback(ErrorCallback);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, opts.gl_major_version_);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, opts.gl_minor_version_);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // macOS

    window_ = glfwCreateWindow(opts.width_, opts.height_, opts.name_.c_str(), NULL, NULL);
    if (window_ == nullptr)
    {
        stopGLFW();
        return sssim::Result<void>::Err("Could not create a window with GLFW.");
    }

    glfwMakeContextCurrent(window_);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return sssim::Result<void>::Err("Could not initialize GLAD.");
    }

    glViewport(0, 0, opts.width_, opts.height_);

    glfwSetWindowSizeCallback(window_, ResizeWindowCallback);
    return sssim::Result<void>::Ok();
}

bool sssim::Window::update()
{
    glfwPollEvents();
    glfwSwapBuffers(window_);
    return init_ && !glfwWindowShouldClose(window_);
}

bool sssim::Window::keyDown(const key::type& key)
{
    return glfwGetKey(window_, key) == GLFW_PRESS;
}

void sssim::Window::close() { glfwSetWindowShouldClose(window_, true); }

void sssim::Window::clear() { glClear(GL_COLOR_BUFFER_BIT); }

void sssim::Window::setColour(double r, double g, double b, double a) { glClearColor(r, g, b, a); }

void sssim::Window::startGLFW()
{
    if (!init_)
    {
        init_ = true;
        glfwInit();
    }
}

void sssim::Window::stopGLFW()
{
    if (init_)
    {
        init_ = false;
        glfwTerminate();
    }
}

