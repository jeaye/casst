#pragma once

#include <casst/delete/detail/delete.hpp>

namespace casst
{
  inline auto delete_()
  { return detail::delete_::del<detail::delete_::steps::base>{}; }
}
