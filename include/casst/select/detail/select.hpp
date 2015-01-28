#pragma once

#include <casst/datatypes.hpp>
#include <casst/json/map.hpp>
#include <casst/select/order_by.hpp>
#include <casst/detail/types.hpp>

#include <sstream>

namespace casst
{
  namespace detail
  {
    namespace select
    {
      enum class step
      {
        base,
        from
      };

      template <step S>
      class select;

      template <>
      class select<step::from>
      {
        public:
          select() = delete;

          select(ostringstream &&oss)
            : oss_{ std::move(oss) }
          { }

          template <typename... Args>
          select& where(Args &&...args)
          {
            oss_ << "WHERE ";
            int const _[]
            { (oss_ << args << " ", 0)... };
            static_cast<void>(_);

            return *this;
          }

          template <order_by O = order_by::asc>
          select& order_by(std::string const &col)
          {
            oss_ << "ORDER BY " << col << " "
                 << detail::order_by_string<O>() << " ";
            return *this;
          }

          select& limit(std::size_t const lim)
          {
            oss_ << "LIMIT " << lim << " ";
            return *this;
          }

          select& allow_filtering()
          {
            oss_ << "ALLOW FILTERING ";
            return *this;
          }

          std::string to_string() const
          { return oss_.str(); }

        private:
          ostringstream oss_;
      };

      template <>
      class select<step::base>
      {
        public:
          select() = delete;

          /* TODO: Support the rest of the functions. (blob, timeuuid, etc) */
          template <typename... Args>
          select(ostringstream &&oss, Args &&...args)
            : oss_{ std::move(oss) }
          {
            int const _[]
            { (oss_ << args << ", ", 0)... };
            static_cast<void>(_);

            oss_.seekp(-2, std::ios_base::end);
            oss_ << " ";
          }

          select<step::from> from(std::string const &table)
          {
            oss_ << "FROM " << table << " ";
            return { std::move(oss_) };
          }

        private:
          ostringstream oss_;
      };
    }
  }
}
