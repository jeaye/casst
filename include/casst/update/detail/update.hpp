#pragma once

#include <casst/datatypes.hpp>

#include <sstream>

namespace casst
{
  namespace detail
  {
    namespace update
    {
      enum class step
      {
        base
      };

      template <step S>
      class update;

      template <>
      class update<step::base>
      {
        public:
          update() = delete;
          update(std::string const &tab)
          { oss_ << "UPDATE " << tab << " "; }

          template <typename... Args>
          update& using_(Args &&...args)
          {
            oss_ << "USING ";
            int const _[]
            { (oss_ << args << " ", 0)... };
            static_cast<void>(_);
            return *this;
          }

          template <typename... Args>
          update& set(Args &&...args)
          {
            oss_ << "SET ";
            int const _[]
            { (oss_ << args << ", ", 0)... };
            static_cast<void>(_);
            oss_.seekp(-2, std::ios_base::end); oss_ << " ";
            return *this;
          }

          std::string to_string() const
          { return oss_.str(); }

        private:
          std::ostringstream oss_;
      };
    }
  }
}
