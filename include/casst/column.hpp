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
    {
      column() = delete;
      column(std::string const &name)
        : name_{ name }
      { }

      std::string name_;
    };
  }

  inline auto column(std::string const &name)
  { return detail::column{ name }; }
}
