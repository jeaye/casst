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
      template <std::size_t N>
      struct composite
      { std::string names[N]; };

      enum class steps
      {
        base,
        columns,
        primary
      };

      template <steps S>
      class table;

      template <>
      class table<steps::primary>
      {
        public:
          template <typename... Args>
          table(std::ostringstream &&oss, std::string const &first, Args &&...args)
            : oss_{ std::move(oss) }
          {
            oss_ << "PRIMARY KEY ( " << first << ", ";
            int const _[]{ (oss_ << args << ", ", 0)... };
            static_cast<void>(_);

            /* Overwrite that last, pesky comma. */
            oss_.seekp(-2, std::ios_base::end);
            oss_ << " ) )";
          }

          template <std::size_t N, typename... Args>
          table(std::ostringstream &&oss, composite<N> const &comp, Args &&...args)
            : oss_{ std::move(oss) }
          {
            oss_ << "PRIMARY KEY ( ( ";
            for(std::size_t i{}; i < N; ++i)
            { oss_ << comp.names[i] << ", "; }

            /* Overwrite that last, pesky comma. */
            oss_.seekp(-2, std::ios_base::end);
            oss_ << " ) ";

            int const _[]{ (oss_ << args << ", ", 0)... };
            static_cast<void>(_);

            /* Overwrite that last, pesky comma. */
            oss_.seekp(-2, std::ios_base::end);
            oss_ << ") )";
          }

          std::string to_string() const
          { return oss_.str(); }

        private:
          std::ostringstream oss_;
      };

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
          }

          template <typename... Args>
          table<steps::primary> primary(Args &&...args)
          { return { std::move(oss_), std::forward<Args>(args)... }; }
          template <std::size_t N, typename... Args>
          table<steps::primary> primary(composite<N> const &comp, Args &&...args)
          { return { std::move(oss_), comp, std::forward<Args>(args)... }; }

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
