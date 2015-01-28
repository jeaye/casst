#pragma once

#include <casst/datatypes.hpp>
#include <casst/insert/detail/insert.hpp>

namespace casst
{
  template <typename... Args>
  auto insert(std::string const &tab, Args &&...args)
  {
    return detail::insert::insert<detail::insert::step::base>
    { tab, std::forward<Args>(args)... };
  }
}
