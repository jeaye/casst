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
        base,
        set
      };

      template <step S>
      class update;

      template <>
      class update<step::set>
      {
        public:
          update() = delete;
          update(std::ostringstream &&oss)
            : oss_{ std::move(oss) }
          { }

          template <typename... Args>
          update& where(Args &&...args)
          {
            oss_ << "WHERE ";
            return if_where(std::forward<Args>(args)...);
          }

          template <typename... Args>
          update& if_(Args &&...args)
          {
            oss_ << "IF ";
            return if_where(std::forward<Args>(args)...);
          }

          std::string to_string() const
          { return oss_.str(); }

        private:
          template <typename... Args>
          update& if_where(Args &&...args)
          {
            int const _[]
            { (oss_ << args << " ", 0)... };
            static_cast<void>(_);

            return *this;
          }

          std::ostringstream oss_;
      };

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
          update<step::set> set(Args &&...args)
          {
            oss_ << "SET ";
            int const _[]
            { (oss_ << args << ", ", 0)... };
            static_cast<void>(_);
            oss_.seekp(-2, std::ios_base::end); oss_ << " ";

            return { std::move(oss_) };
          }

          std::string to_string() const
          { return oss_.str(); }

        private:
          std::ostringstream oss_;
      };
    }
  }
}
