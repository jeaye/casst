#pragma once

#include <casst/datatypes.hpp>
#include <casst/json/map.hpp>

#include <sstream>

namespace casst
{
  namespace detail
  {
    namespace select
    {
      enum class steps
      {
        base
      };

      template <steps S>
      class select;

      template <>
      class select<steps::base>
      {
        public:
          select() = delete;

          template <typename... Args>
          select(std::ostringstream &&oss, Args &&...args)
            : oss_{ std::move(oss) }
          {
            int const _[]
            { (oss_ << args << ", ", 0)... };
            static_cast<void>(_);

            oss_.seekp(-2, std::ios_base::end);
            oss_ << " ";
          }

          std::string to_string()
          { return oss_.str(); }

        private:
          std::ostringstream oss_;
      };
    }
  }
}
