#pragma once

#include <casst/detail/render.hpp>

namespace casst
{
  /* TODO: Tests just for json objects. */
  namespace json
  {
    struct value
    {
      value() = delete;

      template <typename T>
      /* implicit */ value(T const &t)
        : data{ detail::to_rvalue(t) }
      { }

      std::string data;
    };
  }

  namespace detail
  {
    inline std::string to_lvalue(json::value const &value)
    { return value.data; }
    inline std::string to_rvalue(json::value const &value)
    { return value.data; }
  }
}
