#pragma once
#include <emscripten.h>
#ifdef _WIN32
#define _FILE_DEFINED
#endif
#include <utility>
#include <memory>
#include <cstdint>
#include <string_view>
#include <cassert>

namespace xx {
    /***************************************************************************************/

    template<typename T, typename = void>
    struct IsLiteral : std::false_type {
    };
    template<size_t L>
    struct IsLiteral<char[L], void> : std::true_type {
        static const size_t len = L;
    };
    template<size_t L>
    struct IsLiteral<char const [L], void> : std::true_type {
        static const size_t len = L;
    };
    template<size_t L>
    struct IsLiteral<char const (&)[L], void> : std::true_type {
        static const size_t len = L;
    };
    template<typename T>
    constexpr bool IsLiteral_v = IsLiteral<T>::value;
    template<typename T>
    constexpr size_t LiteralLen = IsLiteral<T>::len;
}
