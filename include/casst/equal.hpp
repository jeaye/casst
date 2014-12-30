#pragma once

#include <string>
#include <iostream>

namespace casst
{
  namespace detail
  {
    template <typename T>
    struct equal
    {
      std::string name;
      T value{};
    };

    template <typename T>
    std::ostream& operator <<(std::ostream &os, equal<T> const &e)
    { return os << e.name << " = " << std::boolalpha << e.value << " "; }
    template <>
    std::ostream& operator <<(std::ostream &os, equal<std::string> const &e)
    { return os << e.name << " = '" << e.value << "' "; }
  }

  template <typename T>
  auto equal(std::string const &name, T const &value)
  { return detail::equal<T>{ name, value }; }
  auto equal(std::string const &name, char const * const value)
  { return detail::equal<std::string>{ name, value }; }
}
