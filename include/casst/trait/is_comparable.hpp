#pragma once

#include <casst/row_slice.hpp>

namespace casst
{
  namespace trait
  {
    template <typename LHS, typename RHS>
    struct is_comparable_t
    { static bool constexpr value{ true }; };

    template <std::size_t LHS_N, typename RHS>
    struct is_comparable_t<detail::row_slice<LHS_N>, RHS>
    { static bool constexpr value{ false }; };

    template <std::size_t LHS_N, std::size_t RHS_N>
    struct is_comparable_t<detail::row_slice<LHS_N>, detail::row_slice<RHS_N>>
    { static bool constexpr value{ LHS_N == RHS_N }; };
    
    template <typename LHS, typename RHS>
    bool constexpr is_comparable()
    { return is_comparable_t<LHS, RHS>::value; }
  }
}
