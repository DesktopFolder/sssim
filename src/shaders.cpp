#include "shaders.hpp"

#include "graphics.hpp"

sssim::Result<int> sssim::loadShader(std::string name)
{
    auto res = sssim::readFile(shaderPath(name));
    std::string file;
    std::optional<std::string> error;
    res.match([&](std::string s) { file = std::move(s); },
              [&](std::string e) { error = std::move(e); });
    if (error) return sssim::Result<int>::Err(*error);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* file_c = file.c_str();
    glShaderSource(vertexShader, 1, &file_c, NULL);
    glCompileShader(vertexShader);

    // Check for compilation failure
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        return sssim::Result<int>::Err("Shader compilation failed:\n" + std::string(infoLog));
    }
    return sssim::Result<int>::Ok(vertexShader);
}
