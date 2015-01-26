#pragma once

#include <string>
#include <iostream>

#include <casst/detail/render.hpp>
#include <casst/trait/is_comparable.hpp>
#include <casst/trait/normalize.hpp>

namespace casst
{
  namespace detail
  {
    using sigil = char const* (*)();

    char constexpr const* equal()
    { return " = "; }
    char constexpr const* not_equal()
    { return " <> "; }
    char constexpr const* less()
    { return " < "; }
    char constexpr const* less_equal()
    { return " <= "; }
    char constexpr const* greater()
    { return " > "; }
    char constexpr const* greater_equal()
    { return " >= "; }

    template <sigil Sigil, typename LHS, typename RHS>
    struct compare
    {
      using normal_lhs = trait::normalize_t<LHS>;
      using normal_rhs = trait::normalize_t<RHS>;

      static_assert(trait::is_comparable<normal_lhs, normal_rhs>(),
                    "LHS and RHS are not comparable");

      normal_lhs lhs{};
      normal_rhs rhs{};
    };

    template <sigil Sigil, typename LHS, typename RHS>
    std::ostream& operator <<(std::ostream &os, compare<Sigil, LHS, RHS> const &e)
    {
      return os << e.lhs << Sigil()
                << std::boolalpha << detail::render(e.rhs) << " ";
    }
  }

  template <typename LHS, typename RHS>
  auto equal(LHS const &lhs, RHS const &rhs)
  { return detail::compare<&detail::equal, LHS, RHS>{ lhs, rhs }; }

  template <typename LHS, typename RHS>
  auto not_equal(LHS const &lhs, RHS const &rhs)
  { return detail::compare<&detail::not_equal, LHS, RHS>{ lhs, rhs }; }

  template <typename LHS, typename RHS>
  auto less(LHS const &lhs, RHS const &rhs)
  { return detail::compare<&detail::less, LHS, RHS>{ lhs, rhs }; }

  template <typename LHS, typename RHS>
  auto less_equal(LHS const &lhs, RHS const &rhs)
  { return detail::compare<&detail::less_equal, LHS, RHS>{ lhs, rhs }; }

  template <typename LHS, typename RHS>
  auto greater(LHS const &lhs, RHS const &rhs)
  { return detail::compare<&detail::greater, LHS, RHS>{ lhs, rhs }; }

  template <typename LHS, typename RHS>
  auto greater_equal(LHS const &lhs, RHS const &rhs)
  { return detail::compare<&detail::greater_equal, LHS, RHS>{ lhs, rhs }; }
}
