#pragma once

#include <string>
#include <sstream>

namespace casst
{
  namespace detail
  {
    template <typename T>
    struct renderer
    { T const &data; };
    
    template <typename T>
    auto render(T const &t)
    { return renderer<T>{ t }; }

    template <typename T>
    std::ostream& operator <<(std::ostream &os, renderer<T> const &t)
    { return os << t.data; }
    template <>
    std::ostream& operator << <std::string>(std::ostream &os, renderer<std::string> const &str)
    { return os << "'" << str.data << "'"; }
  }
}
