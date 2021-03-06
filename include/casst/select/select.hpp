#pragma once

#include <casst/datatypes.hpp>
#include <casst/select/detail/select.hpp>
#include <casst/select/expression.hpp>
#include <casst/select/token.hpp>

namespace casst
{
  namespace detail
  {
    template <typename... Args>
    auto select_impl(ostringstream &&oss, Args &&...args)
    {
      return select::select<select::step::base>
      { std::move(oss), std::forward<Args>(args)... };
    }
  }

  template <typename... Args>
  auto select(Args &&...args)
  {
    ostringstream oss; oss << "SELECT ";
    return detail::select_impl(std::move(oss),
                               std::forward<Args>(args)...);
  }

  template <typename... Args>
  auto select_distinct(Args &&...args)
  {
    ostringstream oss; oss << "SELECT DISTINCT ";
    return detail::select_impl(std::move(oss),
                               std::forward<Args>(args)...);
  }

  template <typename... Args>
  auto select_count(Args &&...args)
  {
    ostringstream oss; oss << "SELECT COUNT ( * ) ";
    return detail::select_impl(std::move(oss),
                               std::forward<Args>(args)...);
  }
}
