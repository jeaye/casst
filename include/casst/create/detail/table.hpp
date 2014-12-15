#pragma once

#include <jeayeson/jeayeson.hpp>
#include <casst/types.hpp>

#include <sstream>

namespace casst
{
  namespace create
  {
    namespace detail
    {
      enum class steps
      {
        base,
        columns
      };

      template <steps S>
      class table;

      template <>
      class table<steps::columns>
      {
        public:
          template <typename... Args>
          table(std::ostringstream &&oss, Args &&...args)
            : oss_{ std::move(oss) }
          {
            int const _[]{ (oss_ << args.first << " " << args.second << ", ", 0)... };
            static_cast<void>(_);
            
            /* Overwrite that last, pesky comma. */
            oss_.seekp(-2, std::ios_base::end);
            oss_ << " ) ";
          }

          std::string to_string() const
          { return oss_.str(); }

        private:
          std::ostringstream oss_;
      };

      template <>
      class table<steps::base>
      {
        public:
          template <typename Policy>
          table(std::string const &name, Policy)
            : name_{ name }
            , policy_{ Policy::value }
          { }

          template <typename... Args>
          table<steps::columns> columns(Args &&...args)
          {
            std::ostringstream oss;
            oss << "CREATE TABLE " << name_ << " ( ";
            return { std::move(oss), std::forward<Args>(args)... };
          }

        private:
          std::string name_, policy_;
      };
    }
  }
}
