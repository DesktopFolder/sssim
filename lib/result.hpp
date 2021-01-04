#ifndef SSSIM_RESULT_HPP
#define SSSIM_RESULT_HPP

#include <optional>
#include <string>

namespace sssim
{
template <typename T>
static constexpr bool IsRef = false;
template <typename T>
static constexpr bool IsRef<T*> = true;

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
 *
 * Note - Please keep in mind that this file is really not
 * good C++. Seriously, it isn't.
 */
template <typename V, typename E = std::string>
class Result
{
    // Internal constructors
    template <typename T>
    Result(std::true_type state, T value)
    {
        value_ = value;
        state_ = true;
    }

    template <typename T>
    Result(std::false_type state, T value)
    {
        error_ = value;
        state_ = false;
    }

public:
    // Types
    using value_type = V;
    using error_type = E;

    // Constructors
    static constexpr Result<V, E> Ok(V value) { return Result<V, E>(std::true_type{}, value); }

    static constexpr Result<V, E> Err(E error) { return Result<V, E>(std::false_type{}, error); }

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
    template <typename F1, typename F2, std::enable_if_t<!IsRef<F1>, int> = 0>
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

    template <typename F1, typename F2, std::enable_if_t<IsRef<F1>, int> = 0>
    void match(F1 with_value, F2&& with_error)
    {
        if (state_)
        {
            *with_value = value_;
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

    std::optional<std::string> err()
    {
        if (!state_) return error_;
        return {};
    }

private:
    bool state_;

    union {
        V value_;
        E error_;
    };
};

template <>
class Result<void, std::string>
{
    // Internal constructors
    Result() { state_ = true; }

    Result(std::string err)
    {
        state_ = false;
        error_ = err;
    }

public:
    // Types
    using value_type = void;
    using error_type = std::string;

    // Constructors
    static const Result<void, std::string> Ok() { return Result<void, std::string>(); }

    static const Result<void, std::string> Err(std::string error)
    {
        return Result<void, std::string>(error);
    }

    // Destructor - Necessary for nontrivial cleanup
    ~Result() {}

    // Member functions
    operator bool() { return state_; }

    // Honestly, this will probably be clunky to use in C++.
    // Oh well. It's so functional though! Ha.
    template <typename F1, typename F2>
    void match(F1&& with_value, F2&& with_error)
    {
        if (state_)
        {
            with_value();
        }
        else
        {
            with_error(error_);
        }
    }

    bool ok()
    {
        // See, this is just much easier than using match.
        // It's hard to think of how to implement a nice
        // matcher without using copious templates and/or macros.
        return state_;
    }

    std::optional<std::string> err()
    {
        if (!state_) return error_;
        return {};
    }

private:
    bool state_;

    std::string error_;
};
}  // namespace sssim

#endif  // SSSIM_RESULT_HPP
