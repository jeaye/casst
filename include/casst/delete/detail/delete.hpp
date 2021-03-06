#pragma once

#include <casst/datatypes.hpp>
#include <casst/detail/types.hpp>
#include <casst/row.hpp>
#include <casst/row_slice.hpp>
#include <casst/compare.hpp>

#include <sstream>

namespace casst
{
  namespace detail
  {
    namespace delete_
    {
      enum class steps
      {
        base,
        from
      };

      template <steps S>
      class del;

      template <>
      class del<steps::from>
      {
        public:
          del(ostringstream &&oss)
            : oss_{ std::move(oss) }
          { }

          auto& using_timestamp(timestamp_t const time)
          {
            oss_ << "USING TIMESTAMP " << time << " ";
            return *this;
          }

          template <typename... Args>
          auto& where(Args &&...args)
          {
            oss_ << "WHERE ";
            int const _[]{ (oss_ << args << " ", 0)... };
            static_cast<void>(_);
            return *this;
          }

          template <typename... Args>
          auto& if_(Args &&...args)
          {
            oss_ << "IF ";
            int const _[]{ (oss_ << args << " ", 0)... };
            static_cast<void>(_);
            return *this;
          }
          auto& if_exists()
          {
            oss_ << "IF EXISTS ";
            return *this;
          }

          std::string to_string() const
          { return oss_.str(); }

        private:
          ostringstream oss_;
      };

      template <>
      class del<steps::base>
      {
        public:
          del()
          { oss_ << "DELETE "; }

          template <typename... Args>
          del(Args &&...args)
          {
            oss_ << "DELETE ";
            cols(std::forward<Args>(args)...);
          }

          auto from(std::string const &table)
          {
            oss_ << "FROM " << table << " ";
            return del<steps::from>{ std::move(oss_) };
          }

        private:
          void cols()
          { }

          template <typename... Args>
          void cols(Args &&...args)
          {
            int const _[]{ (oss_ << args << ", ", 0)... };
            static_cast<void>(_);
            oss_.seekp(-2, std::ios_base::end); oss_ << " ";
          }

          ostringstream oss_;
      };
    }
  }
}
