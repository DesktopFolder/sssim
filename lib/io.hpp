#ifndef SSSIM_IO_HPP
#define SSSIM_IO_HPP

#include <iostream>

#include "result.hpp"

namespace sssim
{
template <typename T>
void log(T t)
{
    std::cout << t << '\n';
}

template <typename T, typename... Ts>
void log(T t, Ts... ts)
{
    std::cout << t << ' ';
    print(ts...);
}

/*
template <typename V, typename E>
std::ostream& operator<<(std::ostream& os, const Result<V, E> err)
{
    err.match([&os](const V& v) { os << v; }, [&os](const E& e) { os << e; });
    return os;
}
*/

sssim::Result<std::string> readFile(std::string path);
}  // namespace sssim

#endif  // SSSIM_IO_HPP
