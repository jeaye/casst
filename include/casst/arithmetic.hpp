#pragma once

#include <casst/detail/render.hpp>
#include <casst/compare.hpp>

namespace casst
{
  namespace detail
  {
    char constexpr const* sum()
    { return " + "; }
    char constexpr const* diff()
    { return " - "; }
    char constexpr const* product()
    { return " * "; }
    char constexpr const* quotient()
    { return " / "; }
  }

  template <typename LHS, typename RHS>
  auto sum(LHS const &lhs, RHS const &rhs)
  { return detail::compare<&detail::sum, LHS, RHS>{ lhs, rhs }; }

  template <typename LHS, typename RHS>
  auto diff(LHS const &lhs, RHS const &rhs)
  { return detail::compare<&detail::diff, LHS, RHS>{ lhs, rhs }; }

  template <typename LHS, typename RHS>
  auto product(LHS const &lhs, RHS const &rhs)
  { return detail::compare<&detail::product, LHS, RHS>{ lhs, rhs }; }

  template <typename LHS, typename RHS>
  auto quotient(LHS const &lhs, RHS const &rhs)
  { return detail::compare<&detail::quotient, LHS, RHS>{ lhs, rhs }; }
}
