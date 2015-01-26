#pragma once

#include <string>
#include <sstream>

#include <casst/column.hpp>

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
    inline std::ostream& operator <<<std::string>(std::ostream &os,
                                                  renderer<std::string> const &str)
    { return os << "'" << str.data << "'"; }

    template <typename T>
    std::string to_string(T const &t)
    { return std::to_string(t); }
    inline std::string to_string(std::string const &str)
    { return "'" + str + "'"; }
    inline std::string to_string(char const * const str)
    { return to_string(std::string{ str }); }

    inline std::string to_string(detail::column const &column)
    { return column.name_; }
  }
}
