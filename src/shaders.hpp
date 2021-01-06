#ifndef SSSIM_SHADERS_HPP
#define SSSIM_SHADERS_HPP

#include "log.hpp"
#include "result.hpp"

#include <vector>

namespace sssim
{
inline std::string shaderPath(std::string shader) { return "../shaders/" + shader; }

/**
 * Takes the shader filename as input.
 *
 * Automatically detects the type of shader based on extension.
 */
sssim::Result<int> loadShader(std::string name);

sssim::Result<unsigned int> linkProgram(const std::vector<int>& shaders);
sssim::Result<unsigned int> createShaderProgram(const std::vector<std::string>& shaders);
}  // namespace sssim

#endif  // SSSIM_SHADERS_HPP
