#include "shaders.hpp"

#include "graphics.hpp"
#include "io.hpp"

#include <algorithm>
#include <string_view>

namespace sssim
{
sssim::Result<int> shaderType(const std::string& name_s)
{
    using result    = sssim::Result<int>;
    const auto name = std::string_view(name_s);
    const auto end  = name.crend();
    const auto loc  = std::find(name.crbegin(), name.crend(), '.');
    if (loc == name.crend())
        return result::Err("shaderType: Could not detect the type of " + name_s +
                           " due to a lack of extension (.frag, .vert etc).");
    // const std::string_view ext(loc.base(), name.cend());
    const auto ext = std::string{loc.base(), name.cend()};
    if (ext == "frag") return result::Ok(GL_FRAGMENT_SHADER);
    if (ext == "vert") return result::Ok(GL_VERTEX_SHADER);
    return result::Err("shaderType: Cannot detect shader type from the extension: " + ext);
}
}  // namespace sssim

sssim::Result<int> sssim::loadShader(std::string name)
{
    sssim::log("loadShader: Attempting to load the path:", name);

    const auto shader_type = sssim::shaderType(name);
    if (const auto err_ = shader_type.err()) return sssim::Result<int>::Err(*err_);

    auto res = sssim::readFile(shaderPath(name));
    // Wow, so typesafe!
    if (auto err_ = res.err(); err_) return sssim::Result<int>::Err(*err_);
    std::string file = *res.ok();

    unsigned int shader_id;
    shader_id          = glCreateShader(*shader_type.ok());
    const char* file_c = file.c_str();
    glShaderSource(shader_id, 1, &file_c, NULL);
    glCompileShader(shader_id);

    // Check for compilation failure
    int success;
    char infoLog[512];
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
        return sssim::Result<int>::Err("Shader compilation failed:\n" + std::string(infoLog));
    }
    sssim::log("loadShader: Successfully loaded the path:", name);
    return sssim::Result<int>::Ok(shader_id);
}

sssim::Result<unsigned int> sssim::linkProgram(const std::vector<int>& shaders)
{
    using result = sssim::Result<unsigned int>;

    unsigned int shader_program;
    shader_program = glCreateProgram();
    for (const auto shader : shaders)
    {
        glAttachShader(shader_program, shader);
    }
    glLinkProgram(shader_program);

    // Once again we have a mediocre error check here.
    // It's possible we need to check for errors after each gl call above.
    int success;
    char infoLog[512];
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        return result::Err("Program linking failed:\n" + std::string(infoLog));
    }

    return result::Ok(shader_program);
}

sssim::Result<unsigned int> sssim::createShaderProgram(const std::vector<std::string>& shaders)
{
    using result = sssim::Result<unsigned int>;

    std::vector<int> shader_ids;
    for (const auto& shader : shaders)
    {
        const auto loaded_shader = loadShader(shader);
        if (const auto err_ = loaded_shader.err(); err_) return result::Err(*err_);
        shader_ids.push_back(*loaded_shader.ok());
    }

    const auto loaded_program = linkProgram(shader_ids);
    if (const auto err_ = loaded_program.err(); err_) return result::Err(*err_);

    for (const auto shader : shader_ids) glDeleteShader(shader);
    return result::Ok(*loaded_program.ok());
}
