#pragma once

#include <string>
#include <sstream>
#include <array>

namespace casst
{
  namespace detail
  {
    template <std::size_t N>
    void assert_size()
    { static_assert(N, "row_slices may not be empty"); }

    template <std::size_t N>
    struct row_slice
    { std::array<std::string, N> names; };

    template <std::size_t N>
    std::ostream& operator <<(std::ostream &os, row_slice<N> const &r)
    {
      assert_size<N>();

      os << "( ";
      for(auto const &in : r.names)
      { os << "'" << in << "', "; }
      os.seekp(-2, std::ios_base::end);
      return os << " ) ";
    }
  }

  template <typename... Args>
  auto row_slice(Args &&...args)
  {
    detail::assert_size<sizeof...(args)>();
    return detail::row_slice<sizeof...(args)>{ { std::forward<Args>(args)... } };
  }
}
