#pragma once

#include <string>
#include <vector>
#include <utility>
#include <sstream>

namespace casst
{
  namespace detail
  {
    struct column
    { std::string name; };

    std::ostream& operator <<(std::ostream &os, column const &c)
    { return os << c.name; }
  }

  inline auto column(std::string const &name)
  { return detail::column{ name }; }

  inline auto all()
  { return detail::column{ "*" }; }
}
