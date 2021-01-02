#ifndef SSSIM_RESULT_HPP
#define SSSIM_RESULT_HPP

#include <optional>

namespace sssim
{
/**
 * Lightly styled after Rust's Result<...> struct.
 *
 * As C++ does not have the same support for enums,
 * we fully implement this as its own class. Although
 * we could implement our own enum similar to Rust's,
 * it's likely not necessary as std::optional and this
 * error type take care of most use cases, and we lack
 * pattern matching regardless.
 *
 * TODO - Use concepts to generate better errors for
 * the templated types here.
 *
 * TODO - This should just be a variant wrapper, perhaps.
 * There are certain downsides to that, e.g. same-y types.
 */
template <typename V, typename E = std::string>
class Result
{
    // Internal constructors
    template <typename T>
    Result(bool state, T value)
    {
        if (state) value_ = value;
        if (!state) error_ = value;
        state_ = state;
    }

public:
    // Types
    using value_type = V;
    using error_type = E;

    // Constructors
    static constexpr Result<V, E> Ok(V value) { return Result<V, E>(true, value); }

    static constexpr Result<V, E> Err(E error) { return Result<V, E>(false, error); }

    // Destructor - Necessary for nontrivial cleanup
    ~Result()
    {
        if (state_)
            value_.~V();
        else
            error_.~E();
    }

    // Member functions
    operator bool() { return state_; }

    // Honestly, this will probably be clunky to use in C++.
    // Oh well. It's so functional though! Ha.
    template <typename F1, typename F2>
    void match(F1&& with_value, F2&& with_error)
    {
        if (state_)
        {
            with_value(value_);
        }
        else
        {
            with_error(error_);
        }
    }

    std::optional<V> ok()
    {
        // See, this is just much easier than using match.
        // It's hard to think of how to implement a nice
        // matcher without using copious templates and/or macros.
        if (state_)
            return value_;
        else
            return {};
    }

private:
    bool state_;

    union {
        V value_;
        E error_;
    };
};
}  // namespace sssim

#endif  // SSSIM_RESULT_HPP
