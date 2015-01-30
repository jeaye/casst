#pragma once

#include <casst/delete/detail/delete.hpp>

namespace casst
{
  template <typename... Args>
  auto delete_(Args &&...args)
  {
    return detail::delete_::del<detail::delete_::steps::base>
    { std::forward<Args>(args)... };
  }
}
