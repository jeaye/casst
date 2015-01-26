#pragma once

#include <casst/detail/render.hpp>
#include <casst/trait/normalize.hpp>

namespace casst
{
  namespace detail
  {
    template <typename T>
    struct token
    { trait::normalize_t<T> data; };

    template <typename T>
    std::ostream& operator <<(std::ostream &os, token<T> const &t)
    { return os << "TOKEN ( " << detail::to_rvalue(t.data) << " )"; }
  }
  template <typename T>
  inline auto token(T const &tok)
  { return detail::token<T>{ tok }; }
}
