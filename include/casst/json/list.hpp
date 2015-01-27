#pragma once

#include <casst/json/detail/array.hpp>

namespace casst
{
  namespace json
  {
    namespace detail
    {
      struct list_tag
      { };

      template <>
      char constexpr const* delim_begin<list_tag>()
      { return "[ "; }
      template <>
      char constexpr const* delim_end<list_tag>()
      { return " ]"; }
    }

    using list = detail::array<detail::list_tag>;
  }
}
