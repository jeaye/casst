#pragma once

#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>

#include <casst/json/value.hpp>
#include <casst/detail/render.hpp>

namespace casst
{
  namespace json
  {
    namespace detail
    {
      template <typename Tag>
      char constexpr const* delim_begin();
      template <typename Tag>
      char constexpr const* delim_end();

      template <typename Tag>
      class array
      {
        public:
          using value_type = value;
          using iterator = std::vector<std::string>::iterator;
          using const_iterator = std::vector<std::string>::const_iterator;

          array() = default;
          array(std::initializer_list<value_type> &&list)
          {
            std::transform(list.begin(), list.end(), std::back_inserter(data_),
                           [](auto const &v)
                           { return casst::detail::to_rvalue(v); });
          }

          auto begin()
          { return data_.begin(); }
          auto begin() const
          { return data_.begin(); }
          auto end()
          { return data_.end(); }
          auto end() const
          { return data_.end(); }

          void push_back(value_type const &v)
          { data_.push_back(casst::detail::to_rvalue(v)); }

          template <typename T>
          friend std::ostream& operator <<(std::ostream &os, array<T> const &m);

        private:
          std::vector<std::string> data_;
      };

      template <typename T>
      std::ostream& operator <<(std::ostream &os, array<T> const &m)
      {
        os << delim_begin<T>();

        for(auto const &v : m.data_)
        { os << v << ", "; }
        if(m.data_.size())
        { os.seekp(-2, std::ios_base::end); }

        return os << delim_end<T>();
      }
    }
  }
}
