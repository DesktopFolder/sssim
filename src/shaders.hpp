#ifndef SSSIM_SHADERS_HPP
#define SSSIM_SHADERS_HPP

#include "io.hpp"

namespace sssim {
    inline std::string shaderPath(std::string shader) {
        return "../shaders/" + shader;
    }

    sssim::Result<int> loadShader(std::string name);
}

#endif // SSSIM_SHADERS_HPP
