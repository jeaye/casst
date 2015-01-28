#pragma once

namespace casst
{
  enum class order_by
  {
    asc,
    desc
  };

  namespace detail
  {
    template <order_by O>
    char constexpr const* order_by_string()
    { return "ASC"; }
    template <>
    char constexpr const* order_by_string<order_by::desc>()
    { return "DESC"; }
  }
}
