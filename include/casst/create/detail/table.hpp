#pragma once

#include <casst/datatypes.hpp>

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

      /* TODO: table properties. */
      enum class steps
      {
        base,
        columns,
        primary_key
      };

      template <steps S>
      class table;

      template <>
      class table<steps::primary_key>
      {
        public:
          template <typename... Args>
          table(std::ostringstream &&oss, std::string const &first, Args &&...args)
            : oss_{ std::move(oss) }
          {
            oss_ << "PRIMARY KEY ( " << first << ", ";
            write(std::forward<Args>(args)...);
          }

          template <std::size_t N, typename... Args>
          table(std::ostringstream &&oss, composite<N> const &comp, Args &&...args)
            : oss_{ std::move(oss) }
          {
            oss_ << "PRIMARY KEY ( ( ";
            for(std::size_t i{}; i < N; ++i)
            { oss_ << comp.names[i] << ", "; }

            oss_.seekp(-2, std::ios_base::end);
            oss_ << " )";

            if(sizeof...(Args))
            { oss_ << ", "; }
            write(std::forward<Args>(args)...);
          }

          std::string to_string() const
          { return oss_.str(); }

        private:
          template <typename... Args>
          void write(Args &&...args)
          {
            int const _[]{ (oss_ << args << ", ", 0)... };
            static_cast<void>(_);

            oss_.seekp(-2, std::ios_base::end);
            oss_ << " ) )";
          }

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
          table<steps::primary_key> primary_key(Args &&...args)
          { return { std::move(oss_), std::forward<Args>(args)... }; }
          template <std::size_t N, typename... Args>
          table<steps::primary_key> primary_key(composite<N> const &comp, Args &&...args)
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
            oss << "CREATE TABLE " << policy_ << name_ << " ( ";
            return { std::move(oss), std::forward<Args>(args)... };
          }

        private:
          std::string name_, policy_;
      };
    }
  }
}
