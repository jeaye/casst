#pragma once

#include <casst/row_slice.hpp>

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

    inline std::ostream& operator <<(std::ostream &os, column const &c)
    { return os << c.name; }
  }

  inline std::string to_rvalue(detail::column const &column)
  { return column.name; }

  inline std::string to_lvalue(detail::column const &column)
  { return column.name; }

  inline auto column(std::string const &name)
  { return detail::column{ name }; }

  template <typename... Args>
  auto columns(Args &&...args)
  { return row_slice(casst::column(detail::to_lvalue(std::forward<Args>(args)))...); }

  inline auto all()
  { return detail::column{ "*" }; }
}
