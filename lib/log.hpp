#ifndef SSSIM_LOG_HPP
#define SSSIM_LOG_HPP

#include <iostream>

namespace sssim
{
template <typename T>
void log(T t)
{
    std::cout << t << std::endl;
}

template <typename T, typename... Ts>
void log(T t, Ts... ts)
{
    std::cout << t << ' ';
    ::sssim::log(ts...);
}
}  // namespace sssim

#endif  // SSSIM_LOG_HPP
