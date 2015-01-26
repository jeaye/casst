#pragma once

#include <string>

namespace casst
{
  namespace trait
  {
    template <typename T>
    struct normalize
    { using type = T; };
    template <std::size_t N>
    struct normalize<char const [N]>
    { using type = std::string; };
    template <std::size_t N>
    struct normalize<char [N]>
    { using type = std::string; };

    template <typename T>
    using normalize_t = typename normalize<T>::type;
  }
}
