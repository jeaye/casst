#pragma once

#include <casst/json/detail/array.hpp>

namespace casst
{
  namespace json
  {
    namespace detail
    {
      struct set_tag
      { };

      template <>
      char constexpr const* delim_begin<set_tag>()
      { return "{ "; }
      template <>
      char constexpr const* delim_end<set_tag>()
      { return " }"; }
    }

    using set = detail::array<detail::set_tag>;
  }
}
