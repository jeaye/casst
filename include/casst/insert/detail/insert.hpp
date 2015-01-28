#pragma once

#include <casst/row_slice.hpp>
#include <casst/column.hpp>

#include <sstream>

namespace casst
{
  namespace detail
  {
    namespace insert
    {
      enum class step
      {
        base,
        values,
      };

      template <step S>
      class insert;

      template <>
      class insert<step::values>
      {
        public:
          insert() = delete;
          insert(ostringstream &&oss)
            : oss_{ std::move(oss) }
          { }

          insert& if_not_exists()
          {
            oss_ << "IF NOT EXISTS ";
            return *this;
          }

          template <typename... Args>
          insert& using_(Args &&...args)
          {
            oss_ << "USING ";
            int const _[]
            { (oss_ << args << " ", 0)... };
            static_cast<void>(_);
            return *this;
          }

          std::string to_string() const
          { return oss_.str(); }

        private:
          ostringstream oss_;
      };

      template <>
      class insert<step::base>
      {
        public:
          insert() = delete;

          template <typename T>
          insert(std::string const &tab, T const &cols)
          {
            oss_ << "INSERT INTO " << tab << " ";
            oss_ << cols << " ";
          }

          template <typename... Args>
          insert<step::values> values(Args &&...args)
          {
            oss_ << "VALUES "
                 << casst::row_slice(std::forward<Args>(args)...)
                 << " ";
            return { std::move(oss_) };
          }

        private:
          ostringstream oss_;
      };
    }
  }
}
