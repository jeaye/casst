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
          select(std::string const &name)
            : name_{ name }
          { }

        private:
          std::string const name_;
      };
    }
  }
}
