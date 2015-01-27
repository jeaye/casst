#pragma once

#include <string>
#include <vector>
#include <utility>
#include <sstream>

#include <casst/detail/render.hpp>

namespace casst
{
  namespace detail
  {
    struct row
    {
      row() = delete;
      row(std::string const &name)
        : name_{ name }
      { }

      template <typename... Args>
      auto& in(Args &&...args)
      {
        int const _[]{ (in_.emplace_back(detail::to_rvalue(args)), 0)... };
        static_cast<void>(_);
        return *this;
      }

      std::string name_;
      std::vector<std::string> in_;
    };

    std::ostream& operator <<(std::ostream &os, row const &r)
    {
      os << r.name_ << " ";
      if(r.in_.size())
      {
        os << "IN ( ";
        for(auto const &in : r.in_)
        { os << in + ", "; }
        os.seekp(-2, std::ios_base::end);
        os << " ) ";
      }
      return os;
    }
  }

  inline auto row(std::string const &name)
  { return detail::row{ name }; }
}
