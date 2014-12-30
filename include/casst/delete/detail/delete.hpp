#pragma once

#include <casst/datatypes.hpp>
#include <casst/detail/types.hpp>
#include <casst/row.hpp>
#include <casst/equal.hpp>
#include <casst/and.hpp>

// DELETE col1, col2, col3 FROM Planeteers WHERE userID = 'Captain';
// casst::delete_().cols("col1", "col2", "col3").from("Planeteers").where(casst::equals("userID", "Captain"));
// DELETE FROM MastersOfTheUniverse WHERE mastersID IN ('Man-At-Arms', 'Teela');
// casst::delete_().from("MastersOfTheUniverse").where(casst::row("mastersID").in("Man-At-Arms", "Teela"));

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
          del(std::ostringstream &&oss)
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
            int const _[]{ (oss_ << args, 0)... };
            static_cast<void>(_);
            return *this;
          }

          std::string to_string() const
          { return oss_.str(); }

        private:
          std::ostringstream oss_;
      };

      template <>
      class del<steps::base>
      {
        public:
          del()
          { oss_ << "DELETE "; }

          template <typename... Args>
          auto& cols(Args &&...args)
          {
            if(sizeof...(args))
            {
              int const _[]{ (oss_ << args << ", ", 0)... };
              static_cast<void>(_);
              oss_.seekp(-2, std::ios_base::end); oss_ << " ";
            }
            return *this;
          }

          auto from(std::string const &table)
          {
            oss_ << "FROM " << table << " ";
            return del<steps::from>{ std::move(oss_) };
          }

        private:
          std::ostringstream oss_;
      };
    }
  }
}
