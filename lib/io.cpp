#include "io.hpp"

#include <fstream>
#include <sstream>
#include <string>
// #include <format> // Doesn't exist yet. Fun.

sssim::Result<std::string> sssim::readFile(std::string path)
{
    std::ifstream fs;
    fs.open(path, std::ifstream::in);
    if (!fs.good())
    {
        return sssim::Result<std::string>::Err("Could not read from file: " + path);
    }

    // Won't lie, this is SO-code
    // Well, from an article. So that's better, right?
    std::string contents;
    fs.seekg(0, std::ios::end);
    contents.resize(fs.tellg());
    fs.seekg(0, std::ios::beg);
    fs.read(&contents[0], contents.size());
    fs.close();

    // TODO - Is this string being moved correctly?
    return sssim::Result<std::string>::Ok(std::move(contents));
}
